// src/model/MatchData.cpp

#include "../../include/model/MatchData.h"

MatchData::MatchData(MatchType type, PairResult result, std::string logMsg)
    : matchType(type), pairResult(std::move(result)), log(std::move(logMsg)) {}

MatchType MatchData::getMatchType() const {
    return matchType;
}

const PairResult& MatchData::getPairResult() const {
    return pairResult;
}

const std::string& MatchData::getLog() const {
    return log;
}