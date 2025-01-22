#include "sharememory.h"

void SharedMemory::process() {
    while (true) {
        wait();  // 等待时钟
        if (write.read()) {
            std::cout << "[SharedMemory] Storing data: " << data_in.read() << " at " << sc_time_stamp() << std::endl;
        }
        if (read.read()) {
            data_out.write(data_in.read());
            std::cout << "[SharedMemory] Sending data: " << data_out.read() << " at " << sc_time_stamp() << std::endl;
        }
    }
}
