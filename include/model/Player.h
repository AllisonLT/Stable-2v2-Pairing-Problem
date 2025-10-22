// include/model/Player.h

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

enum class Race {
    PROTOSS,
    TERRAN,
    ZERG,
    RANDOM
};

class Player {
private:
    std::string playerId;
    int seedingRank;
    Race race;
    double mmr;
    std::vector<int> prefList;

public:
    Player(std::string id, int rank, Race r, double m);

    std::string getPlayerId() const;
    int getSeedingRank() const;
    Race getRace() const;
    double getMMR() const;
    const std::vector<int>& getPrefList() const;

    void setPrefList(std::vector<int> list);
};

#endif