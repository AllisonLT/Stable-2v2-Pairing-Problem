// include/backup/BackupMatcher.h

#ifndef BACKUPMATCHER_H
#define BACKUPMATCHER_H

#include <vector>
#include <utility>
#include "../model/Player.h"
#include "../model/MatchData.h"

class BackupMatcher {
private:
    std::vector<Player>& players;
    int n;
    std::string log;

    std::vector<int> sortPlayersBySeeding() const;
    void adjustSameRacePairs(std::vector<std::pair<int, int>>& pairs);
    int calculateSeedingDiffSum(const std::vector<std::pair<int, int>>& pairs) const;

public:
    BackupMatcher(std::vector<Player>& playerList);

    MatchData match();
};

#endif