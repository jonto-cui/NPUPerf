#include "npu.h"
#include "matrix.h"
#include "vector.h"

void NPU::control_logic() {
    while (true) {
        wait(); // 等待时钟
        if (req.read()) {
            // 启动卷积操作
            if (conv_start.read()) {
                conv(); // 调用卷积操作
            }

            ack.write(true);
        } else {
            ack.write(false);
        }
    }
}

void NPU::conv() {
    // 获取输入数据并转换为矩阵和向量
    MatrixOperations::Matrix inputMatrix = {{data_in.read(), 2.0}, {3.0, 4.0}};
    MatrixOperations::Vector inputVector = {1.0, 2.0};

    // 调用矩阵和向量模块
    MatrixOperations::Matrix matrixResult = MatrixOperations::multiply(inputMatrix, inputMatrix);
    MatrixOperations::Vector vectorResult = MatrixOperations::multiply(matrixResult, inputVector);

    // 使用向量加法模块对结果进行进一步处理
    VectorOperations::Vector finalResult = VectorOperations::add(vectorResult, inputVector);

    // 模拟处理逻辑，结果取向量第一个值（根据具体需求可以调整）
    process_result = finalResult[0];

    // 将结果写入输出
    mul_result_internal = process_result;
}

void NPU::update_signals() {
    while (true) {
        wait(); // 等待时钟

        // 更新 `data_out` 信号
        if (req.read()) {
            data_out.write(process_result);
        } else {
            data_out.write(10); // 默认值
        }

        // 更新 `mul_result` 信号
        mul_result.write(mul_result_internal);
    }
}
