// src/solver/IrvingSolver.cpp

#include "../../include/solver/IrvingSolver.h"
#include "../../include/utils/MatrixUtils.h"
#include <sstream>
#include <stdexcept>
#include <algorithm>

IrvingSolver::IrvingSolver(std::vector<Player>& playerList, 
                           const std::vector<std::vector<int>>& pref, 
                           const std::vector<std::vector<int>>& rank)
    : players(playerList), preference(pref), ranking(rank), n(static_cast<int>(playerList.size())) {
    leftmost.resize(n, 1);
    rightmost.resize(n, n - 1);
    second.resize(n, 2);
}

void IrvingSolver::addLog(const std::string& msg) {
    log += msg + "\n";
}

bool IrvingSolver::isAllListLengthOne() const {
    for (int i = 0; i < n; ++i) {
        if (leftmost[i] != rightmost[i]) {
            return false;
        }
    }
    return true;
}

bool IrvingSolver::hasEmptyList() const {
    for (int i = 0; i < n; ++i) {
        if (leftmost[i] > rightmost[i]) {
            return true;
        }
    }
    return false;
}

bool IrvingSolver::phase1() {
    std::unordered_set<int> setProposedTo;
    if (n == 0) return false;

    int firstPlayer = 0;
    setProposedTo.insert(firstPlayer);
    addLog("Phase 1: Started with initial proposed set containing player " + std::to_string(firstPlayer));

    for (int person = 0; person < n; ++person) {
        int proposer = person;
        bool proposed = false;

        while (!proposed) {
            if (leftmost[proposer] > rightmost[proposer]) {
                addLog("Phase 1: Player " + std::to_string(proposer) + " rejected by all, phase failed");
                return false;
            }

            int nextChoice = preference[proposer][leftmost[proposer] - 1];
            if (setProposedTo.find(nextChoice) == setProposedTo.end()) {
                setProposedTo.insert(nextChoice);
                rightmost[nextChoice] = ranking[nextChoice][proposer];
                addLog("Phase 1: Player " + std::to_string(proposer) + " proposed to " + std::to_string(nextChoice) + " (new in set)");
                proposed = true;
                continue;
            }

            int current = preference[nextChoice][rightmost[nextChoice] - 1];
            if (ranking[nextChoice][proposer] < ranking[nextChoice][current]) {
                addLog("Phase 1: Player " + std::to_string(nextChoice) + " accepts " + std::to_string(proposer) + ", rejects " + std::to_string(current));
                rightmost[nextChoice] = ranking[nextChoice][proposer];
                proposer = current;
            }
            else {
                addLog("Phase 1: Player " + std::to_string(nextChoice) + " rejects " + std::to_string(proposer));
                leftmost[proposer]++;
            }
        }
    }

    if (setProposedTo.size() == n) {
        addLog("Phase 1: Completed successfully - all players in proposed set");
        return true;
    }
    else {
        addLog("Phase 1: Failed - incomplete proposed set");
        return false;
    }
}

bool IrvingSolver::phase2() {
    addLog("Phase 2: Started");

    while (!isAllListLengthOne() && !hasEmptyList()) {
        CycleDetector detector(preference, leftmost, rightmost);
        std::vector<int> detectedCycle = detector.detectCycle();

        if (cycle.empty()) {
            addLog("Phase 2: No cycle detected - phase failed");
            return false;
        }

        addLog("Phase 2: Detected cycle of length " + std::to_string(cycle.size()) + ": " + [&]() {
            std::string s;
            for (size_t i = 0; i < cycle.size(); ++i) {
                s += std::to_string(cycle[i]);
                if (i < cycle.size() - 1) s += " -> ";
            }
            return s;
        }());

        for (int a : cycle) {
            if (leftmost[a] >= rightmost[a]) {
                addLog("Phase 2: Empty list found during cycle processing");
                return false;
            }

            leftmost[a] = second[a];
            second[a]++;
            int nextChoice = preference[a][leftmost[a] - 1];
            rightmost[nextChoice] = ranking[nextChoice][a];
            addLog("Phase 2: Player " + std::to_string(a) + " moves to next choice " + std::to_string(nextChoice));
        }
    }

    if (hasEmptyList()) {
        addLog("Phase 2: Failed - empty list detected");
        return false;
    }
    else {
        addLog("Phase 2: Completed successfully - all lists length 1");
        return true;
    }
}

std::optional<MatchData> IrvingSolver::solve() {
    log.clear();
    addLog("Irving Solver: Started");

    if (!phase1()) {
        addLog("Irving Solver: Phase 1 failed - no stable match possible");
        return std::nullopt;
    }

    if (!phase2()) {
        addLog("Irving Solver: Phase 2 failed - no stable match possible");
        return std::nullopt;
    }

    PairResult result;
    for (int i = 0; i < n; ++i) {
        int partnerIdx = preference[i][leftmost[i] - 1];
        result[players[i].getPlayerId()] = players[partnerIdx].getPlayerId();
        result[players[partnerIdx].getPlayerId()] = players[i].getPlayerId();
    }

    addLog("Irving Solver: Successfully found stable match");
    return MatchData(MatchType::STABLE_MATCH, result, log);
}