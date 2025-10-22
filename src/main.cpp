// src/main.cpp

#include <iostream>
#include <vector>
#include <optional>
#include "../include/io/DataReader.h"
#include "../include/generator/PreferenceGenerator.h"
#include "../include/solver/IrvingSolver.h"
#include "../include/backup/BackupMatcher.h"
#include "../include/io/ResultWriter.h"
#include "../include/model/Player.h"

int main() {
    try {
        DataReader reader("config/player_data.csv");
        std::vector<Player> players = reader.readPlayers();
        auto config = reader.readConfig();

        PreferenceGenerator prefGen(players);
        prefGen.generate();
        auto& preference = prefGen.getPreference();
        auto& ranking = prefGen.getRanking();

        IrvingSolver solver(players, preference, ranking);
        std::optional<MatchData> stableMatch = solver.solve();

        MatchData finalMatch = stableMatch.has_value()
            ? stableMatch.value()
            : BackupMatcher(players).match();

        std::string outputPath = config.count("OutputPath") ? config["OutputPath"] : "output/match_result.txt";
        ResultWriter writer(outputPath);
        writer.printResult(finalMatch);
        writer.writeResult(finalMatch);

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}