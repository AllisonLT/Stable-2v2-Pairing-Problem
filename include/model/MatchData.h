// include/model/MatchData.h

#ifndef MATCHDATA_H
#define MATCHDATA_H

#include <string>
#include <unordered_map>
#include <vector>

enum class MatchType {
    STABLE_MATCH,
    BACKUP_MATCH
};

using PairResult = std::unordered_map<std::string, std::string>;

class MatchData {
private:
    MatchType matchType;
    PairResult pairResult;
    std::string log;

public:
    MatchData(MatchType type, PairResult result, std::string logMsg);

    MatchType getMatchType() const;
    const PairResult& getPairResult() const;
    const std::string& getLog() const;
};

#endif