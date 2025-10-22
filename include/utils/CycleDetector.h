// include/utils/CycleDetector.h

#ifndef CYCLEDETECTOR_H
#define CYCLEDETECTOR_H

#include <vector>

class CycleDetector {
private:
    const std::vector<std::vector<int>>& preference;
    const std::vector<int>& leftmost;
    const std::vector<int>& rightmost;
    int n;

    std::vector<int> generatePSequence(int startPlayer) const;

public:
    CycleDetector(const std::vector<std::vector<int>>& pref, 
                  const std::vector<int>& lm, 
                  const std::vector<int>& rm);

    std::vector<int> detectCycle();
};

#endif