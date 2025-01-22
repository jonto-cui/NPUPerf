#ifndef LOAD_H
#define LOAD_H

#include <systemc.h>
#include <vector>

SC_MODULE(Load) {
    sc_in<bool> clk;                  // 时钟信号
    sc_out<int> row_addr;             // 行地址输出
    sc_out<int> col_addr;             // 列地址输出
    sc_in<double> data_in;            // 从内存读取的数据
    sc_out<bool> read;                // 读请求信号

    std::vector<std::vector<double>> window; // 内部2x2滑窗矩阵
    int rows, cols;                   // 内存的总行列数
    int current_row, current_col;     // 当前滑窗的起始地址

    void process();                   // 核心逻辑

    SC_CTOR(Load) : rows(4), cols(4), current_row(0), current_col(0), window(2, std::vector<double>(2, 0)) {
        SC_THREAD(process);
        sensitive << clk.pos();       // 在时钟的上升沿触发
    }
};

#endif // LOAD_H
