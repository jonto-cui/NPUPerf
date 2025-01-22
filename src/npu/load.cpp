//需要有一个滑窗来暂存rem当中的数据

//输入是rem的data_out

//输出是一个Matrix


#include "load.h"

void Load::process() {
    while (true) {
        wait(); // 等待时钟

        // 发出读请求
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                int target_row = (current_row + i) % rows;
                int target_col = (current_col + j) % cols;

                row_addr.write(target_row); // 设置行地址
                col_addr.write(target_col); // 设置列地址
                read.write(true);           // 发出读请求
                wait();                     // 等待一个时钟周期读取数据
                window[i][j] = data_in.read(); // 保存数据到滑窗矩阵
                read.write(false);
            }
        }

        // 打印滑窗内容
        std::cout << "[Load] Window Data:" << std::endl;
        for (const auto &row : window) {
            for (const auto &val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }

        // 更新滑窗起始地址
        current_col += 2;
        if (current_col >= cols) {
            current_col = 0;
            current_row += 2;
        }
        if (current_row >= rows) {
            current_row = 0; // 遍历结束后从头开始
        }
    }
}
