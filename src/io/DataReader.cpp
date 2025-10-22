// src/io/DataReader.cpp

#include "../../include/io/DataReader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

DataReader::DataReader(std::string path) : filePath(std::move(path)) {}

Race DataReader::parseRace(const std::string& raceStr) {
    if (raceStr == "P" || raceStr == "Protoss") return Race::PROTOSS;
    if (raceStr == "T" || raceStr == "Terran") return Race::TERRAN;
    if (raceStr == "Z" || raceStr == "Zerg") return Race::ZERG;
    if (raceStr == "R" || raceStr == "Random") return Race::RANDOM;
    throw std::runtime_error("Invalid race string: " + raceStr);
}

std::vector<Player> DataReader::readPlayers() {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open player data file: " + filePath);
    }

    std::vector<Player> players;
    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, raceStr;
        int rank;
        double mmr;

        std::getline(ss, id, ',');
        ss >> rank;
        ss.ignore();
        std::getline(ss, raceStr, ',');
        ss >> mmr;

        Race race = parseRace(raceStr);
        players.emplace_back(id, rank, race, mmr);
    }

    file.close();
    return players;
}

std::unordered_map<std::string, std::string> DataReader::readConfig() {
    std::ifstream file("config/PairingConfig.ini");
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open config file");
    }

    std::unordered_map<std::string, std::string> config;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == ';') continue;

        size_t eqPos = line.find('=');
        if (eqPos == std::string::npos) continue;

        std::string key = line.substr(0, eqPos);
        std::string value = line.substr(eqPos + 1);
        config[key] = value;
    }

    file.close();
    return config;
}