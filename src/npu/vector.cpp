#include "vector.h"
#include <stdexcept>

VectorOperations::Vector VectorOperations::add(const Vector& vec1, const Vector& vec2) {
    if (vec1.size() != vec2.size()) {
        throw std::invalid_argument("Vectors must be of the same size for addition.");
    }

    Vector result(vec1.size(), 0.0);
    for (size_t i = 0; i < vec1.size(); ++i) {
        result[i] = vec1[i] + vec2[i];
    }

    return result;
}
