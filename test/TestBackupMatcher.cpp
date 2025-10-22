// test/TestBackupMatcher.cpp

#include <gtest/gtest.h>
#include "../include/model/Player.h"
#include "../include/backup/BackupMatcher.h"

TEST(BackupMatcherTest, FourPlayerAdjacentPairing) {
    std::vector<Player> players = {
        Player("P1", 1, Race::PROTOSS, 4500.0),
        Player("P2", 2, Race::PROTOSS, 4400.0),
        Player("P3", 3, Race::TERRAN, 4300.0),
        Player("P4", 4, Race::ZERG, 4200.0)
    };

    BackupMatcher matcher(players);
    MatchData result = matcher.match();
    auto& pairs = result.getPairResult();

    EXPECT_EQ(pairs["P1"], "P3");
    EXPECT_EQ(pairs["P3"], "P1");
    EXPECT_EQ(pairs["P2"], "P4");
    EXPECT_EQ(pairs["P4"], "P2");
}

TEST(BackupMatcherTest, SixPlayerSeedingDiff) {
    std::vector<Player> players = {
        Player("P1", 1, Race::PROTOSS, 4500.0),
        Player("P2", 2, Race::TERRAN, 4400.0),
        Player("P3", 3, Race::ZERG, 4300.0),
        Player("P4", 4, Race::RANDOM, 4200.0),
        Player("P5", 5, Race::PROTOSS, 4100.0),
        Player("P6", 6, Race::TERRAN, 4000.0)
    };

    BackupMatcher matcher(players);
    MatchData result = matcher.match();
    auto& pairs = result.getPairResult();

    EXPECT_EQ(pairs["P1"], "P2");
    EXPECT_EQ(pairs["P3"], "P4");
    EXPECT_EQ(pairs["P5"], "P6");
}