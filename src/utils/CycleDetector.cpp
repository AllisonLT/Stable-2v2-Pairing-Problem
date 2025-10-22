// src/utils/CycleDetector.cpp

#include "../../include/utils/CycleDetector.h"
#include "../../include/utils/MatrixUtils.h"
#include <unordered_map>
#include <stdexcept>

CycleDetector::CycleDetector(const std::vector<std::vector<int>>& pref, 
                             const std::vector<int>& lm, 
                             const std::vector<int>& rm)
    : preference(pref), leftmost(lm), rightmost(rm), n(static_cast<int>(pref.size())) {}

std::vector<int> CycleDetector::generatePSequence(int startPlayer) const {
    std::vector<int> pSeq;
    std::unordered_map<int, int> posMap;
    int current = startPlayer;

    while (true) {
        if (posMap.find(current) != posMap.end()) {
            int cycleStart = posMap[current];
            return std::vector<int>(pSeq.begin() + cycleStart, pSeq.end());
        }

        posMap[current] = static_cast<int>(pSeq.size());
        pSeq.push_back(current);

        if (leftmost[current] >= rightmost[current]) {
            throw std::runtime_error("Empty list found during cycle detection");
        }

        int secondPos = leftmost[current] + 1;
        if (secondPos > rightmost[current]) {
            throw std::runtime_error("Invalid second position in preference list");
        }

        int q = preference[current][secondPos - 1];
        int qFirstPos = leftmost[q];
        if (qFirstPos > rightmost[q]) {
            throw std::runtime_error("Invalid first position for q in cycle detection");
        }

        current = preference[q][qFirstPos - 1];
    }
}

std::vector<int> CycleDetector::detectCycle() {
    for (int i = 0; i < n; ++i) {
        if (leftmost[i] < rightmost[i]) {
            try {
                return generatePSequence(i);
            }
            catch (...) {
                continue;
            }
        }
    }
    return {};
}