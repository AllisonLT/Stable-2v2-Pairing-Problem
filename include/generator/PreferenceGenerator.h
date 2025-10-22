// include/generator/PreferenceGenerator.h

#ifndef PREFERENCEGENERATOR_H
#define PREFERENCEGENERATOR_H

#include <vector>
#include "../model/Player.h"

class PreferenceGenerator {
private:
    std::vector<Player>& players;
    std::vector<std::vector<int>> preference;
    std::vector<std::vector<int>> ranking;
    int n;

    bool isSameRace(const Player& p1, const Player& p2) const;
    std::vector<int> sortPlayersBySeeding() const;

public:
    PreferenceGenerator(std::vector<Player>& playerList);

    void generate();

    const std::vector<std::vector<int>>& getPreference() const;
    const std::vector<std::vector<int>>& getRanking() const;
};

#endif