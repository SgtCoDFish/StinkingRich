/*
 * Player.cpp
 *
 * Created on: 3 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <cstdint>

#include "StinkingRichConstants.hpp"
#include "components/Player.hpp"

using namespace stinkingRich;

uint64_t stinkingRich::Player::nextID = 0;


void stinkingRich::Player::addMoney(Money &amount) {
	balance += amount;
}

void stinkingRich::Player::removeMoney(Money &amount) {
	balance -= amount;
}

const std::string stinkingRich::Player::getBalance() const {
	return balance.toString();
}
