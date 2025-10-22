// src/backup/BackupMatcher.cpp

#include "../../include/backup/BackupMatcher.h"
#include <algorithm>
#include <sstream>

BackupMatcher::BackupMatcher(std::vector<Player>& playerList)
    : players(playerList), n(static_cast<int>(playerList.size())) {}

std::vector<int> BackupMatcher::sortPlayersBySeeding() const {
    std::vector<int> indices(n);
    for (int i = 0; i < n; ++i) {
        indices[i] = i;
    }
    std::sort(indices.begin(), indices.end(), [this](int a, int b) {
        return players[a].getSeedingRank() < players[b].getSeedingRank();
    });
    return indices;
}

void BackupMatcher::adjustSameRacePairs(std::vector<std::pair<int, int>>& pairs) {
    for (size_t i = 0; i < pairs.size(); ++i) {
        int p1 = pairs[i].first;
        int p2 = pairs[i].second;

        if (players[p1].getRace() == Race::RANDOM || players[p2].getRace() == Race::RANDOM) {
            continue;
        }

        if (players[p1].getRace() != players[p2].getRace()) {
            continue;
        }

        if (i + 1 >= pairs.size()) {
            continue;
        }

        int nextP1 = pairs[i + 1].first;
        int nextP2 = pairs[i + 1].second;
        std::swap(pairs[i].second, pairs[i + 1].first);

        log += "Adjusted same-race pair (" + std::to_string(p1) + "," + std::to_string(p2) + 
               ") with next pair to (" + std::to_string(p1) + "," + std::to_string(nextP1) + 
               ") and (" + std::to_string(p2) + "," + std::to_string(nextP2) + ")\n";
    }
}

int BackupMatcher::calculateSeedingDiffSum(const std::vector<std::pair<int, int>>& pairs) const {
    int sum = 0;
    for (const auto& p : pairs) {
        sum += std::abs(players[p.first].getSeedingRank() - players[p.second].getSeedingRank());
    }
    return sum;
}

MatchData BackupMatcher::match() {
    log.clear();
    log += "Backup Matcher: Started\n";

    auto sortedIndices = sortPlayersBySeeding();
    std::vector<std::pair<int, int>> pairs;

    for (int i = 0; i < n; i += 2) {
        pairs.emplace_back(sortedIndices[i], sortedIndices[i + 1]);
    }

    log += "Initial adjacent pairs (Seeding order):\n";
    for (const auto& p : pairs) {
        log += "(" + std::to_string(p.first) + "," + std::to_string(p.second) + ")\n";
    }

    adjustSameRacePairs(pairs);
    int diffSum = calculateSeedingDiffSum(pairs);
    log += "Final backup pairs (Seeding diff sum: " + std::to_string(diffSum) + "):\n";

    PairResult result;
    for (const auto& p : pairs) {
        std::string id1 = players[p.first].getPlayerId();
        std::string id2 = players[p.second].getPlayerId();
        result[id1] = id2;
        result[id2] = id1;
        log += "(" + id1 + "," + id2 + ")\n";
    }

    return MatchData(MatchType::BACKUP_MATCH, result, log);
}