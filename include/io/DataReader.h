// include/io/DataReader.h

#ifndef DATAREADER_H
#define DATAREADER_H

#include <string>
#include <vector>
#include <unordered_map>
#include "../model/Player.h"

class DataReader {
private:
    std::string filePath;

    Race parseRace(const std::string& raceStr);

public:
    DataReader(std::string path);

    std::vector<Player> readPlayers();
    std::unordered_map<std::string, std::string> readConfig();
};

#endif