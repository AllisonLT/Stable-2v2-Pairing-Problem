// test/TestPreferenceGenerator.cpp

#include <gtest/gtest.h>
#include "../include/model/Player.h"
#include "../include/generator/PreferenceGenerator.h"

TEST(PreferenceGeneratorTest, EvenPlayerCount) {
    std::vector<Player> players = {
        Player("P1", 1, Race::PROTOSS, 4500.0),
        Player("P2", 2, Race::TERRAN, 4400.0),
        Player("P3", 3, Race::PROTOSS, 4300.0),
        Player("P4", 4, Race::ZERG, 4200.0)
    };

    EXPECT_NO_THROW(PreferenceGenerator gen(players));
}

TEST(PreferenceGeneratorTest, OddPlayerCount) {
    std::vector<Player> players = {
        Player("P1", 1, Race::PROTOSS, 4500.0),
        Player("P2", 2, Race::TERRAN, 4400.0),
        Player("P3", 3, Race::PROTOSS, 4300.0)
    };

    EXPECT_THROW(PreferenceGenerator gen(players), std::runtime_error);
}

TEST(PreferenceGeneratorTest, PreferenceListCompleteness) {
    std::vector<Player> players = {
        Player("P1", 1, Race::PROTOSS, 4500.0),
        Player("P2", 2, Race::TERRAN, 4400.0),
        Player("P3", 3, Race::ZERG, 4300.0),
        Player("P4", 4, Race::PROTOSS, 4200.0)
    };

    PreferenceGenerator gen(players);
    gen.generate();
    auto& pref = gen.getPreference();

    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(pref[i].size(), 3);
        std::unordered_set<int> unique(pref[i].begin(), pref[i].end());
        EXPECT_EQ(unique.size(), 3);
    }
}