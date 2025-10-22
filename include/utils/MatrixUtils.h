// include/utils/MatrixUtils.h

#ifndef MATRIXUTILS_H
#define MATRIXUTILS_H

#include <vector>
#include <string>

namespace MatrixUtils {
    std::vector<std::vector<int>> createMatrix(int n, int m, int defaultValue = 0);
    std::string printMatrix(const std::vector<std::vector<int>>& matrix, const std::string& name);
    int findIndex(const std::vector<int>& list, int value);
}

#endif