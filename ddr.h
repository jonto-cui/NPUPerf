#ifndef DDR_H
#define DDR_H

#include <systemc.h>

SC_MODULE(DDR) {
    sc_in<int> data_in;     // 写入的数据
    sc_out<int> data_out;   // 读取的数据
    sc_in<bool> read;       // 读请求信号
    sc_in<bool> write;      // 写请求信号

    int memory;             // 模拟的内存存储

    void process();         // 处理读写请求

    SC_CTOR(DDR) : memory(5) {  // 初始化 `memory` 为 5
        SC_THREAD(process);
        sensitive << read << write;
    }
};

#endif  // DDR_H
