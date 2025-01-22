#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

class VectorOperations {
public:
    using Vector = std::vector<double>;

    // 向量加法
    static Vector add(const Vector& vec1, const Vector& vec2);
};

#endif // VECTOR_OPERATIONS_H
