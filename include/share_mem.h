#ifndef SHAREDMEMORY_H
#define SHAREDMEMORY_H

#include <systemc.h>

SC_MODULE(SharedMemory) {
    sc_in<double> data_in;     // 写入的数据
    sc_out<double> data_out;   // 读取的数据
    sc_in<bool> read;       // 读请求信号
    sc_in<bool> write;      // 写请求信号

    int memory;             // 模拟的共享内存存储

    void process();

    SC_CTOR(SharedMemory) : memory(0) {
        SC_THREAD(process);
    }
};

#endif  // SHAREDMEMORY_H
