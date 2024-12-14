#ifndef DDR_H
#define DDR_H

#include <systemc.h>

SC_MODULE(DDR) {
    sc_in<int> data_in;     // 写入的数据
    sc_out<int> data_out;   // 读取的数据
    sc_in<bool> read;       // 读请求信号
    sc_in<bool> write;      // 写请求信号

    int memory;             // 模拟的内存存储

    void process();

    SC_CTOR(DDR) : memory(5) {
        SC_THREAD(process);
    }
};

#endif  // DDR_H
 