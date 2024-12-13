#include "npu.h"

void NPU::process() {
    while (true) {
        wait();  // 等待时钟
        if (req.read() && !ack.read()) {
            int processed_data = data_in.read() * 2;  // 简单示例处理
            data_out.write(processed_data);
            std::cout << "[NPU] Received data: " << data_in.read()
                      << ", Processed data: " << processed_data << " at " << sc_time_stamp() << std::endl;
            ack.write(true);
        } else {
            ack.write(false);
        }
    }
}
