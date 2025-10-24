// src/model/Player.cpp

#include "../../include/model/Player.h"

Player::Player(std::string id, int rank, Race r, int m)
    : playerId(std::move(id)), seedingRank(rank), race(r), mmr(m) {}

std::string Player::getPlayerId() const {
    return playerId;
}

int Player::getSeedingRank() const {
    return seedingRank;
}

Race Player::getRace() const {
    return race;
}

int Player::getMMR() const {
    return mmr;
}

const std::vector<int>& Player::getPrefList() const {
    return prefList;
}

void Player::setPrefList(std::vector<int> list) {
    prefList = std::move(list);
}