// src/generator/PreferenceGenerator.cpp

#include "../../include/generator/PreferenceGenerator.h"
#include "../../include/utils/MatrixUtils.h"
#include <stdexcept>
#include <algorithm>

PreferenceGenerator::PreferenceGenerator(std::vector<Player>& playerList)
    : players(playerList), n(static_cast<int>(playerList.size())) {
    if (n % 2 != 0) {
        throw std::runtime_error("Player count must be even");
    }
    preference = MatrixUtils::createMatrix(n, n - 1, 0);
    ranking = MatrixUtils::createMatrix(n, n, 0);
}

bool PreferenceGenerator::isSameRace(const Player& p1, const Player& p2) const {
    if (p1.getRace() == Race::RANDOM || p2.getRace() == Race::RANDOM) {
        return false;
    }
    return p1.getRace() == p2.getRace();
}

std::vector<int> PreferenceGenerator::sortPlayersBySeeding() const {
    std::vector<int> indices(n);
    for (int i = 0; i < n; ++i) {
        indices[i] = i;
    }
    std::sort(indices.begin(), indices.end(), [this](int a, int b) {
        return players[a].getSeedingRank() < players[b].getSeedingRank();
    });
    return indices;
}

void PreferenceGenerator::generate() {
    auto sortedIndices = sortPlayersBySeeding();

    for (int i = 0; i < n; ++i) {
        std::vector<int> pref;
        int currentRank = players[i].getSeedingRank();

        for (int idx : sortedIndices) {
            if (idx == i) continue;
            Player& candidate = players[idx];
            if (candidate.getSeedingRank() < currentRank && !isSameRace(players[i], candidate)) {
                pref.push_back(idx);
            }
        }

        for (int idx : sortedIndices) {
            if (idx == i) continue;
            Player& candidate = players[idx];
            if (candidate.getSeedingRank() < currentRank && isSameRace(players[i], candidate)) {
                pref.push_back(idx);
            }
        }

        for (int idx : sortedIndices) {
            if (idx == i) continue;
            Player& candidate = players[idx];
            if (candidate.getSeedingRank() >= currentRank) {
                pref.push_back(idx);
            }
        }

        preference[i] = pref;
        players[i].setPrefList(pref);

        for (int k = 0; k < n - 1; ++k) {
            int j = pref[k];
            ranking[i][j] = k + 1;
        }
    }
}

const std::vector<std::vector<int>>& PreferenceGenerator::getPreference() const {
    return preference;
}

const std::vector<std::vector<int>>& PreferenceGenerator::getRanking() const {
    return ranking;
}