#include "ddr.h"

void DDR::process() {
    while (true) {
        wait();  // 等待时钟
        if (write.read()) {
            std::cout << "[DDR] Writing data: " << data_in.read() << " at " << sc_time_stamp() << std::endl;
        }
        if (read.read()) {
            data_out.write(data_in.read());
            std::cout << "[DDR] Sending data: " << data_out.read() << " at " << sc_time_stamp() << std::endl;
        }
    }
}

