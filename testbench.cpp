#include <systemc.h>
#include "soc_top.h"

class Testbench : public sc_module {
public:
    Top top;  // 实例化被测系统（Top）

    // 时钟生成
    void clock_gen() {
        while (true) {
            top.clk.write(true);
            wait(10, SC_NS);
            top.clk.write(false);
            wait(10, SC_NS);
        }
    }

    // 系统流程激励
    void system_process() {
        // 初始化所有控制信号
        top.cpu_req.write(false);
        top.npu_req.write(false);
        top.ddr_read.write(false);
        top.ddr_write.write(false);
        top.shared_mem_read.write(false);
        top.shared_mem_write.write(false);
        top.npu_conv_start.write(false);
        wait(20, SC_NS);

        // CPU -> NPU 数据传输
        std::cout << "[System] CPU starts sending data to NPU at " << sc_time_stamp() << std::endl;
        top.cpu_req.write(true);
        wait(top.cpu_ack.posedge_event());
        top.cpu_req.write(false);
        std::cout << "[System] CPU data transfer to NPU complete at " << sc_time_stamp() << std::endl;

        // NPU 进行卷积操作
        std::cout << "[System] NPU starts convolution at " << sc_time_stamp() << std::endl;
        top.npu_conv_start.write(true);
        wait(10, SC_NS);
        top.npu_conv_start.write(false);
        wait(10, SC_NS);
        std::cout << "[System] NPU convolution result: " << top.npu_mul_result.read() << " at " << sc_time_stamp() << std::endl;

        // NPU -> DDR 数据存储
        std::cout << "[System] NPU starts transferring data to DDR at " << sc_time_stamp() << std::endl;
        top.npu_req.write(true);
        wait(top.npu_ack.posedge_event());
        top.ddr_row_addr.write(1); // 设置DDR目标地址
        top.ddr_col_addr.write(2);
        top.ddr_data_in.write(top.npu_data_out.read());
        top.ddr_write.write(true);
        wait(20, SC_NS);
        top.ddr_write.write(false);
        top.npu_req.write(false);
        std::cout << "[System] Data transfer from NPU to DDR complete at " << sc_time_stamp() << std::endl;

        // DDR -> SharedMemory 数据存储
        std::cout << "[System] DDR starts transferring data to SharedMemory at " << sc_time_stamp() << std::endl;
        top.ddr_row_addr.write(1);
        top.ddr_col_addr.write(2);
        top.ddr_read.write(true);
        wait(20, SC_NS);
        top.ddr_read.write(false);

        top.shared_mem_write.write(true);
        wait(20, SC_NS);
        top.shared_mem_write.write(false);
        std::cout << "[System] Data transfer from DDR to SharedMemory complete at " << sc_time_stamp() << std::endl;

        // SharedMemory -> CPU 数据读取
        std::cout << "[System] CPU starts reading data from SharedMemory at " << sc_time_stamp() << std::endl;
        top.shared_mem_read.write(true);
        wait(20, SC_NS);
        top.shared_mem_read.write(false);
        std::cout << "[System] CPU finished reading data from SharedMemory at " << sc_time_stamp() << std::endl;

        sc_stop(); // 结束仿真
    }

    SC_CTOR(Testbench) : top("top") {
        SC_THREAD(clock_gen);
        SC_THREAD(system_process);
    }
};

int sc_main(int argc, char* argv[]) {
    Testbench tb("tb");
    sc_start();
    std::cout << "----------SoC Test Finished!----------" << std::endl;
    return 0;
}