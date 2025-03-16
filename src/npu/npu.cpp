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
    // 假设 feature map 是一个 3x3 矩阵，使用 2x2 滑动窗口进行卷积
    static MatrixOperations::Matrix featureMap(3, std::vector<double>(3, 0.0));
    
    // 读取新的输入数据并更新 feature map
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            featureMap[i][j] = data_in.read(); // 模拟数据流入
        }
    }

    // 卷积核固定
    static const MatrixOperations::Matrix kernel = {
        {1.0, 0.5},
        {0.5, 1.0}
    };

    // 计算滑动窗口的卷积
    MatrixOperations::Matrix outputMatrix(2, std::vector<double>(2, 0.0));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            double sum = 0.0;
            for (int ki = 0; ki < 2; ++ki) {
                for (int kj = 0; kj < 2; ++kj) {
                    sum += featureMap[i + ki][j + kj] * kernel[ki][kj];
                }
            }
            outputMatrix[i][j] = sum;
        }
    }

    // 使用向量处理模块
    MatrixOperations::Vector inputVector = {1.0, 2.0};
    MatrixOperations::Vector vectorResult = MatrixOperations::multiply(outputMatrix, inputVector);
    VectorOperations::Vector finalResult = VectorOperations::add(vectorResult, inputVector);

    // 结果取第一个值
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
