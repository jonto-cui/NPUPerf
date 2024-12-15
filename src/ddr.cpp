#include "ddr.h"

void DDR::process() {
    while (true) {
        wait();  // 等待敏感信号

        if (write.read()) { // 写操作
            int row = row_addr.read();
            int col = col_addr.read();
            if (row >= 0 && row < memory.size() && col >= 0 && col < memory[row].size()) {
                memory[row][col] = data_in.read(); // 写入指定位置
                std::cout << "[DDR] Writing data to memory[" << row << "][" << col << "]: " 
                          << memory[row][col] << " at " << sc_time_stamp() << std::endl;
            } else {
                std::cerr << "[DDR] Write out of bounds at " << sc_time_stamp() << std::endl;
            }
        }

        if (read.read()) { // 读操作
            int row = row_addr.read();
            int col = col_addr.read();
            if (row >= 0 && row < memory.size() && col >= 0 && col < memory[row].size()) {
                data_out.write(memory[row][col]); // 从指定位置读取
                std::cout << "[DDR] Sending data from memory[" << row << "][" << col << "]: " 
                          << memory[row][col] << " at " << sc_time_stamp() << std::endl;
            } else {
                std::cerr << "[DDR] Read out of bounds at " << sc_time_stamp() << std::endl;
            }
        }
    }
}
