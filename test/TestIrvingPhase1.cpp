// test/TestIrvingPhase1.cpp

#include <gtest/gtest.h>
#include "../include/model/Player.h"
#include "../include/solver/IrvingSolver.h"

TEST(IrvingPhase1Test, FourPlayerNoSolution) {
    std::vector<Player> players = {
        Player("P1", 1, Race::PROTOSS, 4500.0),
        Player("P2", 2, Race::TERRAN, 4400.0),
        Player("P3", 3, Race::ZERG, 4300.0),
        Player("P4", 4, Race::RANDOM, 4200.0)
    };

    std::vector<std::vector<int>> preference = {
        {1, 2, 3},
        {2, 0, 3},
        {0, 1, 3},
        {0, 1, 2}
    };

    std::vector<std::vector<int>> ranking = {
        {0, 1, 2, 3},
        {3, 1, 0, 2},
        {2, 3, 1, 0},
        {1, 2, 3, 0}
    };

    IrvingSolver solver(players, preference, ranking);
    EXPECT_FALSE(solver.phase1());
}

TEST(IrvingPhase1Test, SixPlayerSuccess) {
    std::vector<Player> players(6, Player("P", 1, Race::PROTOSS, 4000.0));
    std::vector<std::vector<int>> preference = {
        {3, 5, 1, 2, 4},
        {5, 3, 0, 4, 2},
        {4, 0, 5, 1, 3},
        {1, 4, 0, 5, 2},
        {2, 3, 1, 0, 5},
        {0, 2, 4, 3, 1}
    };

    std::vector<std::vector<int>> ranking(6, std::vector<int>(6, 0));
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 5; ++j) {
            ranking[i][preference[i][j]] = j + 1;
        }
    }

    IrvingSolver solver(players, preference, ranking);
    EXPECT_TRUE(solver.phase1());
}