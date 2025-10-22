//  src/io/ResultWriter.cpp

#include "../../include/io/ResultWriter.h"
#include <fstream>
#include <iostream>
#include <unordered_set>

ResultWriter::ResultWriter(std::string path) : outputPath(std::move(path)) {}

std::string ResultWriter::matchTypeToString(MatchType type) {
    return (type == MatchType::STABLE_MATCH) ? "Stable Match (Irving Algorithm)" : "Backup Match (Seeding Adjacent)";
}

void ResultWriter::printResult(const MatchData& matchData) {
    std::cout << "==================== Match Result ====================\n";
    std::cout << "Match Type: " << matchTypeToString(matchData.getMatchType()) << "\n";
    std::cout << "Pairings:\n";

    std::unordered_set<std::string> printed;
    const auto& pairs = matchData.getPairResult();

    for (const auto& [id1, id2] : pairs) {
        if (printed.find(id1) != printed.end() || printed.find(id2) != printed.end()) {
            continue;
        }
        std::cout << "  " << id1 << " <-> " << id2 << "\n";
        printed.insert(id1);
        printed.insert(id2);
    }

    std::cout << "\nLog:\n" << matchData.getLog() << "\n";
    std::cout << "=======================================================\n";
}

void ResultWriter::writeResult(const MatchData& matchData) {
    std::ofstream file(outputPath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open output file: " + outputPath);
    }

    file << "Match Result - " << matchTypeToString(matchData.getMatchType()) << "\n";
    file << "=============================================\n";
    file << "Pairings:\n";

    std::unordered_set<std::string> printed;
    const auto& pairs = matchData.getPairResult();

    for (const auto& [id1, id2] : pairs) {
        if (printed.find(id1) != printed.end() || printed.find(id2) != printed.end()) {
            continue;
        }
        file << id1 << " <-> " << id2 << "\n";
        printed.insert(id1);
        printed.insert(id2);
    }

    file << "\nDetailed Log:\n" << matchData.getLog();
    file.close();
}