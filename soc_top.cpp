#include <systemc.h>
#include "cpu.h"
#include "npu.h"
#include "ddr.h"
#include "sharememory.h"

SC_MODULE(Top) {
    // 新增的信号
    sc_signal<bool> npu_mul_start;
    sc_signal<int> npu_mul_result;

    // 信号定义
    sc_signal<bool> clk;
    sc_signal<int> cpu_data_out, npu_data_in, npu_data_out, ddr_data_in, ddr_data_out;
    sc_signal<int> shared_mem_data_out;
    sc_signal<bool> cpu_req, cpu_ack, npu_req, npu_ack, ddr_read, ddr_write, shared_mem_read, shared_mem_write;

    // 模块实例化
    CPU cpu;
    NPU npu;
    DDR ddr;
    SharedMemory shared_mem;

    // 时钟生成
    void clock_gen() {
        while (true) {
            clk.write(true);
            wait(10, SC_NS);
            clk.write(false);
            wait(10, SC_NS);
        }
    }

    // 系统流程
    void system_process() {
        // 初始状态
        cpu_req.write(false);
        npu_req.write(false);
        ddr_read.write(false);
        ddr_write.write(false);
        shared_mem_read.write(false);
        shared_mem_write.write(false);
        npu_mul_start.write(false);
        wait(20, SC_NS);

        // CPU -> NPU 数据传输
        std::cout << "[System] CPU starts sending data to NPU at " << sc_time_stamp() << std::endl;
        cpu_req.write(true);
        wait(cpu_ack.posedge_event());
        cpu_req.write(false);
        std::cout << "[System] CPU data transfer to NPU complete at " << sc_time_stamp() << std::endl;

        // NPU 进行乘法操作
        std::cout << "[System] NPU starts multiplication at " << sc_time_stamp() << std::endl;
        npu_mul_start.write(true);
        wait(10, SC_NS);
        npu_mul_start.write(false);
        wait(10, SC_NS);
        std::cout << "[System] NPU multiplication result: " << npu_mul_result.read() << " at " << sc_time_stamp() << std::endl;

        // NPU -> DDR 数据存储
        std::cout << "[System] NPU starts transferring data to DDR at " << sc_time_stamp() << std::endl;
        npu_req.write(true);
        wait(npu_ack.posedge_event());
        ddr_data_in.write(npu_data_out.read()); // 数据传输到 DDR
        ddr_write.write(true);
        wait(20, SC_NS);
        ddr_write.write(false);
        npu_req.write(false);
        std::cout << "[System] Data transfer from NPU to DDR complete at " << sc_time_stamp() << std::endl;

        // DDR -> SharedMemory 数据存储
        std::cout << "[System] DDR starts transferring data to SharedMemory at " << sc_time_stamp() << std::endl;
        ddr_read.write(true);
        wait(20, SC_NS);
        ddr_read.write(false);

        shared_mem_write.write(true);
        wait(20, SC_NS);
        shared_mem_write.write(false);
        std::cout << "[System] Data transfer from DDR to SharedMemory complete at " << sc_time_stamp() << std::endl;

        // SharedMemory -> CPU 数据读取
        std::cout << "[System] CPU starts reading data from SharedMemory at " << sc_time_stamp() << std::endl;
        shared_mem_read.write(true);
        wait(20, SC_NS);
        shared_mem_read.write(false);
        std::cout << "[System] CPU finished reading data from SharedMemory at " << sc_time_stamp() << std::endl;

        sc_stop(); // 停止仿真
    }

    // 构造函数
    SC_CTOR(Top)
        : cpu("CPU"), npu("NPU"), ddr("DDR"), shared_mem("SharedMemory") {
        // 信号连接
        cpu.clk(clk);
        cpu.data_out(cpu_data_out);
        cpu.data_in(shared_mem_data_out);
        cpu.req(cpu_req);
        cpu.ack(cpu_ack);

        npu.clk(clk);
        npu.data_in(cpu_data_out);
        npu.data_out(npu_data_out);
        npu.req(npu_req);
        npu.ack(npu_ack);
        npu.mul_start(npu_mul_start);
        npu.mul_result(npu_mul_result);

        ddr.data_in(ddr_data_in);
        ddr.data_out(ddr_data_out);
        ddr.read(ddr_read);
        ddr.write(ddr_write);

        shared_mem.data_in(ddr_data_out);
        shared_mem.data_out(shared_mem_data_out);
        shared_mem.read(shared_mem_read);
        shared_mem.write(shared_mem_write);

        // 线程定义
        SC_THREAD(clock_gen);       // 时钟生成
        SC_THREAD(system_process); // 系统流程
    }
};

// 主函数
int sc_main(int argc, char* argv[]) {
    Top top("Top");       // 实例化顶层模块
    sc_start();           // 开始仿真
    std::cout << "----------SoC Test Finished!----------" << std::endl;
    return 0;
}
