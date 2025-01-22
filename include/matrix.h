#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class MatrixOperations {
public:
    using Matrix = std::vector<std::vector<double>>;
    using Vector = std::vector<double>;

    // 矩阵乘法
    static Matrix multiply(const Matrix& mat1, const Matrix& mat2);

    // 矩阵向量乘法
    static Vector multiply(const Matrix& mat, const Vector& vec);
};

#endif // MATRIX_OPERATIONS_H
