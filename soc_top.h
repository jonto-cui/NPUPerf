#ifndef SOC_TOP_H
#define SOC_TOP_H

#include <systemc.h>
#include "cpu.h"
#include "npu.h"
#include "ddr.h"
#include "share_mem.h"

SC_MODULE(Top) {
public:  // 所有信号设为public以便Testbench访问
    // 新增的信号
    sc_signal<bool> npu_conv_start;
    sc_signal<double> npu_mul_result;

    // 信号定义
    sc_signal<bool> clk;
    sc_signal<double> cpu_data_out, npu_data_in, npu_data_out, ddr_data_in, ddr_data_out;
    sc_signal<double> shared_mem_data_out;
    sc_signal<bool> cpu_req, cpu_ack, npu_req, npu_ack, ddr_read, ddr_write, shared_mem_read, shared_mem_write;

    // DDR地址信号
    sc_signal<int> ddr_row_addr, ddr_col_addr;
    sc_signal<int> shared_mem_row_addr, shared_mem_col_addr;

    // 子模块实例
    CPU cpu;
    NPU npu;
    DDR ddr;
    SharedMemory share_mem;

    SC_CTOR(Top);
};

#endif // TOP_H