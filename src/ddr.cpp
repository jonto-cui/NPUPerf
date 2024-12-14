#include "ddr.h"

void DDR::process() {
    while (true) {
        wait();  // 等待敏感信号

        if (write.read()) { // 写操作
            memory = data_in.read(); // 写入内存
            std::cout << "[DDR] Writing data to memory: " << memory << " at " << sc_time_stamp() << std::endl;
        }

        if (read.read()) { // 读操作
            data_out.write(memory); // 从内存读取
            std::cout << "[DDR] Sending data from memory: " << memory << " at " << sc_time_stamp() << std::endl;
        }
    }
}
