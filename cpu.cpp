#include "cpu.h"

void CPU::process() {
    while (true) {
        wait();  // 等待时钟
        if (req.read() && !ack.read()) {
            std::cout << "[CPU] Sending data: " << data_out.read() << " at " << sc_time_stamp() << std::endl;
            ack.write(true);
        } else {
            ack.write(false);
        }
    }
}

