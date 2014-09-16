/*
 * Player.cpp
 *
 * Created on: 3 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <cstdint>

#include <string>
#include <sstream>
#include <memory>

#include "Ashley/core/ComponentMapper.hpp"

#include "StinkingRich.hpp"
#include "StinkingRichConstants.hpp"

#include "components/BoardLocation.hpp"
#include "components/Player.hpp"
#include "components/Position.hpp"
#include "components/YesNoQuery.hpp"

#include "systems/InputSystem.hpp"

using namespace stinkingRich;

uint64_t stinkingRich::Player::nextID = 0;
int64_t stinkingRich::Player::made = 0;

void stinkingRich::Player::addMoney(MoneyType amount) {
	balance += amount;
}

void stinkingRich::Player::removeMoney(MoneyType amount) {
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

void stinkingRich::Player::handleMoveResult(std::shared_ptr<stinkingRich::Position> &pos) {
	const auto &boardLoc = pos->position.lock();
	stinkingRich::LocationType &type = boardLoc->details.type;

	if (type == stinkingRich::LocationType::INCOME_TAX
			|| type == stinkingRich::LocationType::SUPER_TAX) {
		std::cout << "Tax: Money changed by " << boardLoc->details.value.toString() << ".\n";

		addMoney(boardLoc->details.value);
	} else if (type == stinkingRich::LocationType::PROPERTY) {
		std::cout << "Landed on " << boardLoc->details.name << ".\n";

		if (boardLoc->isOwned()) {
			auto owner = ashley::ComponentMapper<Player>::getMapper().get(boardLoc->owner.lock());
			const auto &group = boardLoc->details.group;

			std::cout << "Owned by " << owner->id << ".\n";

			std::cout << "Being charged for \"" << boardLoc->details.name << "\".\nFunds before: "
					<< getBalance() << ".\n";

			MoneyType landingCost(0,0);

			if (group == PropertyGroup::STATION) {
				const int ownedCount = stinkingRich::StinkingRich::countOwnedByPlayer(owner, PropertyGroup::STATION);
				landingCost = boardLoc->details.landingCost[ownedCount];
			} else if (group == PropertyGroup::UTILITY) {
				const int ownedCount = stinkingRich::StinkingRich::countOwnedByPlayer(owner, PropertyGroup::UTILITY);
				int mod = 1;

				if(ownedCount == 1) {
					mod = 4;
				} else if(ownedCount == 2) {
					mod = 10;
				} else {
					std::cerr << "Invalid number of utilities owned; something is horribly wrong.\n";
					std::cerr.flush();

					return;
				}

				const int totalCharge = mod * (stinkingRich::InputSystem::getDieOne() + stinkingRich::InputSystem::getDieTwo());
				landingCost = MoneyType(totalCharge, 0);
			} else {
				landingCost = boardLoc->getLandingCost();
			}

			addMoney(-landingCost);
			owner->addMoney(landingCost);

			std::cout << "After: " << getBalance() << ".\n";
			std::cout.flush();
		} else {
			std::cout << "Not owned.\n";

			if (boardLoc->details.value <= balance) {
				std::stringstream ss;
				ss << "Would you like to purchase " << boardLoc->details.name << " for "
						<< boardLoc->details.value.toString() << "?";

				auto e = stinkingRich::YesNoQuery::makeYesNoQuery(ss.str());
				stinkingRich::StinkingRich::uiRenderSystem->addUIEntity(e);
			} else {
				std::cout << "We require more minerals.\n";
				std::cout.flush();
			}
		}
	} else if (type == stinkingRich::LocationType::GO_TO_JAIL) {
		jail();
	} else if (type == stinkingRich::LocationType::CHANCE) {
		auto card = stinkingRich::StinkingRich::chanceCards.getTopCard();
		std::cout << "Drew \"" << card.text << "\".\n";
		card.doEffect();
	} else if (type == stinkingRich::LocationType::COMMUNITY_CHEST) {
		auto card = stinkingRich::StinkingRich::communityChestCards.getTopCard();

		std::cout << "Drew \"" << card.text << "\".\n";
		std::cout.flush();

		card.doEffect();
	}
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
