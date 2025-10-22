// src/utils/MatrixUtils.cpp

#include "../../include/utils/MatrixUtils.h"
#include <sstream>
#include <stdexcept>

std::vector<std::vector<int>> MatrixUtils::createMatrix(int n, int m, int defaultValue) {
    return std::vector<std::vector<int>>(n, std::vector<int>(m, defaultValue));
}

std::string MatrixUtils::printMatrix(const std::vector<std::vector<int>>& matrix, const std::string& name) {
    std::stringstream ss;
    ss << name << ":\n";
    for (size_t i = 0; i < matrix.size(); ++i) {
        ss << "Row " << i << ": ";
        for (int val : matrix[i]) {
            ss << val << " ";
        }
        ss << "\n";
    }
    return ss.str();
}

int MatrixUtils::findIndex(const std::vector<int>& list, int value) {
    for (size_t i = 0; i < list.size(); ++i) {
        if (list[i] == value) {
            return static_cast<int>(i);
        }
    }
    throw std::runtime_error("Value not found in list");
}