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
int64_t stinkingRich::Player::made = 0;

void stinkingRich::Player::addMoney(Money amount) {
	balance += amount;
}

void stinkingRich::Player::removeMoney(Money amount) {
	balance -= amount;
}

const std::string stinkingRich::Player::getBalance() const {
	return balance.toString();
}

int64_t stinkingRich::Player::getTotalPlayerCount() {
	return Player::made;
}

void stinkingRich::Player::rolledDouble() {
	doublesRolled++;
}

void stinkingRich::Player::resetDoubles() {
	doublesRolled = 0;
}

void stinkingRich::Player::spentTurnInJail() {
	turnsLeftInJail--;
}

int8_t stinkingRich::Player::getTurnsLeftInJail() const {
	return turnsLeftInJail;
}

int8_t stinkingRich::Player::getDoublesRolled() const {
	return doublesRolled;
}
