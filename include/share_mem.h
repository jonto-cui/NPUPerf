#ifndef SHAREDMEMORY_H
#define SHAREDMEMORY_H

#include <systemc.h>
#include <vector>

SC_MODULE(SharedMemory) {
    sc_in<int> row_addr;      // 行地址
    sc_in<int> col_addr;      // 列地址
    sc_in<double> data_in;    // 写入的数据
    sc_out<double> data_out;  // 读取的数据
    sc_in<bool> read;         // 读请求信号
    sc_in<bool> write;        // 写请求信号

    std::vector<std::vector<int>> memory; // 模拟的二维矩阵存储

    void process();           // 处理读写请求

    SC_CTOR(SharedMemory) : memory(4, std::vector<int>(4, 0)) { // 初始化4x4矩阵，初值为0
        SC_THREAD(process);
        sensitive << read << write;
    }
};

#endif  // SHAREDMEMORY_H
