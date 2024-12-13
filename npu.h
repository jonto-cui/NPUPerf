#ifndef NPU_H
#define NPU_H

#include <systemc.h>

SC_MODULE(NPU) {
    sc_in<bool> clk;
    sc_in<int> data_in;     // 从CPU接收数据
    sc_out<int> data_out;   // 向DDR或共享内存发送数据
    sc_in<bool> req;        // 请求信号
    sc_out<bool> ack;       // 应答信号

    void process();

    SC_CTOR(NPU) {
        SC_THREAD(process);
        sensitive << clk.pos();
    }
};

#endif  // NPU_H
