// include/io/ResultWriter.h

#ifndef RESULTWRITER_H
#define RESULTWRITER_H

#include <string>
#include "../model/MatchData.h"

class ResultWriter {
private:
    std::string outputPath;

    std::string matchTypeToString(MatchType type);

public:
    ResultWriter(std::string path);

    void printResult(const MatchData& matchData);
    void writeResult(const MatchData& matchData);
};

#endif