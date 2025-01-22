#include "matrix.h"
#include <stdexcept>

MatrixOperations::Matrix MatrixOperations::multiply(const Matrix& mat1, const Matrix& mat2) {
    size_t rows1 = mat1.size();
    size_t cols1 = mat1[0].size();
    size_t rows2 = mat2.size();
    size_t cols2 = mat2[0].size();

    if (cols1 != rows2) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication.");
    }

    Matrix result(rows1, std::vector<double>(cols2, 0.0));

    for (size_t i = 0; i < rows1; ++i) {
        for (size_t j = 0; j < cols2; ++j) {
            for (size_t k = 0; k < cols1; ++k) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    return result;
}

MatrixOperations::Vector MatrixOperations::multiply(const Matrix& mat, const Vector& vec) {
    size_t rows = mat.size();
    size_t cols = mat[0].size();

    if (cols != vec.size()) {
        throw std::invalid_argument("Matrix and vector dimensions do not match for multiplication.");
    }

    Vector result(rows, 0.0);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[i] += mat[i][j] * vec[j];
        }
    }

    return result;
}
