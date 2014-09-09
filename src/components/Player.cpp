/*
 * Player.cpp
 *
 * Created on: 3 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <cstdint>

#include <memory>

#include "Ashley/core/ComponentMapper.hpp"

#include "StinkingRichConstants.hpp"
#include "components/BoardLocation.hpp"
#include "components/Player.hpp"
#include "components/Position.hpp"
#include "StinkingRich.hpp"

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

void stinkingRich::Player::jail() {
	turnsLeftInJail = 3;

	auto playerMapper = ashley::ComponentMapper<Player>::getMapper();
	auto positionMapper = ashley::ComponentMapper<Position>::getMapper();

	auto players = stinkingRich::StinkingRich::allPlayers;

	for (auto p : players) {
		auto plShared = p.lock();
		auto positionS = positionMapper.get(plShared);
		auto playerCompShared = playerMapper.get(plShared);

		if (playerCompShared->id == id) {
			// found this player
			auto posLock = positionS->position.lock();

			while (posLock->details.type != LocationType::JUST_VISITING) {
				auto next = posLock->nextLocation.lock();

				positionS->position = std::weak_ptr<BoardLocation>(
						ashley::ComponentMapper<BoardLocation>::getMapper().get(next));

				posLock = positionS->position.lock();
			}
		}
	}
}
