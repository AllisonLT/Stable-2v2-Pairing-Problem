// test/TestFullFlow.cpp

#include <gtest/gtest.h>
#include <fstream>
#include "../include/io/DataReader.h"
#include "../include/generator/PreferenceGenerator.h"
#include "../include/solver/IrvingSolver.h"
#include "../include/backup/BackupMatcher.h"

TEST(FullFlowTest, StableMatchSuccess) {
    std::ofstream testFile("config/test_players.csv");
    testFile << "PlayerID,SeedingRank,Race,MMR\n";
    testFile << "P1,1,P,4500\n";
    testFile << "P2,2,T,4400\n";
    testFile << "P3,3,Z,4300\n";
    testFile << "P4,4,R,4200\n";
    testFile << "P5,5,P,4100\n";
    testFile << "P6,6,T,4000\n";
    testFile.close();

    DataReader reader("config/test_players.csv");
    std::vector<Player> players = reader.readPlayers();

    PreferenceGenerator prefGen(players);
    prefGen.generate();

    IrvingSolver solver(players, prefGen.getPreference(), prefGen.getRanking());
    auto result = solver.solve();

    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result->getMatchType(), MatchType::STABLE_MATCH);
}

TEST(FullFlowTest, BackupMatchTrigger) {
    std::ofstream testFile("config/test_players_no_sol.csv");
    testFile << "PlayerID,SeedingRank,Race,MMR\n";
    testFile << "P1,1,P,4500\n";
    testFile << "P2,2,T,4400\n";
    testFile << "P3,3,Z,4300\n";
    testFile << "P4,4,R,4200\n";
    testFile.close();

    DataReader reader("config/test_players_no_sol.csv");
    std::vector<Player> players = reader.readPlayers();

    PreferenceGenerator prefGen(players);
    prefGen.generate();

    std::vector<std::vector<int>> badPref = {
        {1, 2, 3},
        {2, 0, 3},
        {0, 1, 3},
        {0, 1, 2}
    };

    IrvingSolver solver(players, badPref, prefGen.getRanking());
    auto result = solver.solve();

    EXPECT_FALSE(result.has_value());

    BackupMatcher backup(players);
    MatchData backupResult = backup.match();
    EXPECT_EQ(backupResult.getMatchType(), MatchType::BACKUP_MATCH);
}