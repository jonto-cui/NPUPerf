#include "npu.h"

// 原有控制逻辑
void NPU::control_logic() {
    while (true) {
        wait(); // 等待时钟
        if (req.read()) {
            process_result = data_in.read() * 2; // 模拟处理逻辑
            ack.write(true);
        } else {
            ack.write(false);
        }
    }
}

// 数据处理逻辑（简单处理）
void NPU::process_data() {
    process_result = data_in.read() + 1; // 简单数据处理逻辑
}

// 乘法逻辑
void NPU::perform_multiplication() {
    if (mul_start.read()) {
        mul_result_internal = data_in.read() * 2; // 简单的乘法计算
    }
}

void NPU::conv(){} 

// 统一信号更新
void NPU::update_signals() {
    while (true) {
        wait(); // 等待时钟

        // 更新 `data_out` 信号
        if (req.read()) {
            data_out.write(process_result);
        } else {
            data_out.write(0); // 默认值
        }

        // 更新 `mul_result` 信号
        mul_result.write(mul_result_internal);
    }
}
