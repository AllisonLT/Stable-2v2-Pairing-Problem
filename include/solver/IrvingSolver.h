// include/solver/IrvingSolver.h

#ifndef IRVINGSOLVER_H
#define IRVINGSOLVER_H

#include <vector>
#include <unordered_set>
#include <optional>
#include "../model/Player.h"
#include "../model/MatchData.h"
#include "../utils/CycleDetector.h"

class IrvingSolver {
private:
    std::vector<Player>& players;
    const std::vector<std::vector<int>>& preference;
    const std::vector<std::vector<int>>& ranking;
    int n;
    std::vector<int> leftmost;
    std::vector<int> rightmost;
    std::vector<int> second;
    std::vector<int> cycle;
    std::string log;

    void addLog(const std::string& msg);
    bool isAllListLengthOne() const;
    bool hasEmptyList() const;

public:
    IrvingSolver(std::vector<Player>& playerList, 
                 const std::vector<std::vector<int>>& pref, 
                 const std::vector<std::vector<int>>& rank);

    bool phase1();
    bool phase2();
    std::optional<MatchData> solve();
};

#endif