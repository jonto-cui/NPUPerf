#include "soc_top.h"

Top::Top(sc_module_name name)
    : sc_module(name),
      cpu("CPU"),
      npu("NPU"),
      ddr("DDR"),
      share_mem("SharedMemory") {

    // 连接CPU
    cpu.clk(clk);
    cpu.data_out(cpu_data_out);
    cpu.data_in(shared_mem_data_out);
    cpu.req(cpu_req);
    cpu.ack(cpu_ack);

    // 连接NPU
    npu.clk(clk);
    npu.data_in(cpu_data_out);
    npu.data_out(npu_data_out);
    npu.req(npu_req);
    npu.ack(npu_ack);
    npu.conv_start(npu_conv_start);
    npu.mul_result(npu_mul_result);

    // 连接DDR
    ddr.data_in(ddr_data_in);
    ddr.data_out(ddr_data_out);
    ddr.read(ddr_read);
    ddr.write(ddr_write);
    ddr.row_addr(ddr_row_addr);
    ddr.col_addr(ddr_col_addr);

    // 连接SharedMemory
    share_mem.data_in(ddr_data_out);
    share_mem.data_out(shared_mem_data_out);
    share_mem.read(shared_mem_read);
    share_mem.write(shared_mem_write);
    share_mem.row_addr(shared_mem_row_addr);
    share_mem.col_addr(shared_mem_col_addr);
}