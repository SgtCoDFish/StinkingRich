/*
 * Card.cpp
 *
 * Created on: 9 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <functional>
#include <string>
#include <vector>
#include <random>

#include "Ashley/AshleyCore.hpp"

#include "util/MoneyType.hpp"
#include "StinkingRichConstants.hpp"
#include "StinkingRich.hpp"
#include "components/Player.hpp"
#include "components/Position.hpp"
#include "cards/Card.hpp"

std::vector<stinkingRich::Card> stinkingRich::Card::getAllChanceCards() {
	std::vector<stinkingRich::Card> retVal;
	std::vector<std::pair<const std::string, DoEffectType>> vals;

	vals.emplace_back("Advance to Mayfair", []() {moveToMayfair();});
	vals.emplace_back("Advance to \"Go!\".", []() {moveToGo();});
	vals.emplace_back(
			"You are assessed for street repairs:\nFor each house pay <CURR>25.\nFor each hotel pay <CURR>115.",
			[]() {repairs(MoneyType(25,0), MoneyType(115,0));});

	vals.emplace_back("Bank pays you dividend of <CURR>50.", []() {changeMoney(MoneyType(50,0));});

	vals.emplace_back("Go back 3 spaces.", []() {moveBackThreeSpaces();});
	vals.emplace_back("Pay school fees of <CURR>150.", []() {changeMoney(MoneyType(150,0));});
	vals.emplace_back(
			"Make general repairs on all of your property:\nFor each house pay <CURR>25.\nFor each hotel pay <CURR>100.",
			[]() {repairs(MoneyType(25,0), MoneyType(100,0));});

	vals.emplace_back("Speeding fine; pay <CURR>15.", []() {changeMoney(MoneyType(15,0));});

	vals.emplace_back("You've won a crossword competition; collect <CURR>100.",
			[]() {changeMoney(MoneyType(100,0));});

	vals.emplace_back("Your annuity matures; collect <CURR>150.",
			[]() {changeMoney(MoneyType(150,0));});

//	vals.emplace_back("Get out of jail free!", []() {getOutOfJailFree();});

	vals.emplace_back("Advance to Trafalgar Sqaure.\nIf you pass \"Go\" collect <CURR>200.",
			[]() {moveToTrafalgarSquare();});

	vals.emplace_back("Take a trip to Marylebone Station.\nIf you pass \"Go\" collect <CURR>200.",
			[]() {moveToMaryleboneStation();});

	vals.emplace_back("Advance to Pall Mall.\nIf you pass \"Go\" collect <CURR>200.",
			[]() {moveToPallMall();});

	vals.emplace_back("Drunk in charge. Pay <CURR>20.", []() {changeMoney(MoneyType(20,0));});

	for (const auto &entry : vals) {
		std::string text = std::string(entry.first);
		const auto &doFunc = entry.second;

		const std::string currString = "<CURR>";

		auto pos = text.find(currString);
		if (pos != text.npos) {
			//	text = text.replace(pos, currString.length(), stinkingRich::constants::currencySymbol);
			// note using the above causes a segfault because of static order initialisation
			// could be fixed by changing stinkingRich::constants from a namespace into a class
			// with "create on first access" semantics.
			text = text.replace(pos, currString.length(), std::string("£"));
		}

		retVal.emplace_back(CardType::CHANCE, std::string(text), doFunc);
//		std::cout << "Added " << retVal.back().text << "\n";
	}

	return retVal;
}

std::vector<stinkingRich::Card> stinkingRich::Card::getAllCommunityChestCards() {
	std::vector<stinkingRich::Card> retVal;
	std::vector<std::pair<std::string, DoEffectType>> vals;

	vals.emplace_back("Income tax refund; collect <CURR>20.", []() {changeMoney(MoneyType(20,0));});

	vals.emplace_back("From sale of stock you get <CURR>50.", []() {changeMoney(MoneyType(50,0));});

	vals.emplace_back("It's your birthday! Collect <CURR>10 from each player.",
			[]() {doBirthday(MoneyType(10,0));});

	vals.emplace_back("Receive interest on 7% preference shares; collect <CURR>25.",
			[]() {changeMoney(MoneyType(25,0));});

//	vals.emplace_back("Get out of Jail Free.", []() {getOutOfJailFree();});

	vals.emplace_back("Advance to \"Go\".", []() {moveToGo();});

	vals.emplace_back("Pay hospital <CURR>100.", []() {changeMoney(MoneyType(-100,0));});

	vals.emplace_back("You've won second prize in a beauty contest!\nCollect <CURR>10.",
			[]() {changeMoney(MoneyType(10,0));});

	vals.emplace_back("Bank error in your favour; collect <CURR>200.",
			[]() {changeMoney(MoneyType(200,0));});

	vals.emplace_back("You inherit <CURR>100.", []() {changeMoney(MoneyType(100,0));});

	vals.emplace_back(
			"Go to jail. Move directly to jail.\nDo not pass \"Go\". Do not collect <CURR>200.",
			[]() {jailPlayer();});

	vals.emplace_back("Pay your <CURR>50 insurance premium.",
			[]() {changeMoney(MoneyType(-50, 0));});

	//vals.emplace_back("Pay a <CURR>10 fine, or take a chance.", [](){fineOrTakeChance(MoneyType(10,0));});

	vals.emplace_back("Doctor's fee; pay <CURR>50.", []() {changeMoney(MoneyType(-50,0));});

	vals.emplace_back("Go back to Old Kent Road.", []() {moveBackToOldKentRoad();});

	vals.emplace_back("Annuity matures; collect <CURR>100.", []() {changeMoney(MoneyType(100,0));});

	for (const auto &entry : vals) {
		std::string text = std::string(entry.first);
		const auto &doFunc = entry.second;

		const std::string currString = "<CURR>";

		auto pos = text.find(currString);
		if (pos != text.npos) {
			//	text = text.replace(pos, currString.length(), stinkingRich::constants::currencySymbol);
			// note using the above causes a segfault because of static order initialisation
			// could be fixed by changing stinkingRich::constants from a namespace into a class
			// with "create on first access" semantics.
			text = text.replace(pos, currString.length(), std::string("£"));
		}

		retVal.emplace_back(CardType::CHANCE, std::string(text), doFunc);
//		std::cout << "Added " << retVal.back().text << "\n";
	}

	return retVal;
}

stinkingRich::Deck::Deck(CardType type) :
		type(type) {
	std::vector<Card> cardsT = (
			type == CardType::CHANCE ?
					Card::getAllChanceCards() :
					(type == CardType::COMMUNITY_CHEST ?
							Card::getAllCommunityChestCards() : std::vector<Card>()));

	std::shuffle(cardsT.begin(), cardsT.end(), stinkingRich::StinkingRich::getRandEngine());

	for (auto &c : cardsT) {
		cards.emplace(c);
	}
}

stinkingRich::Card stinkingRich::Deck::getTopCard() {
	Card topCard = Card(cards.front());

	cards.pop();
	cards.push(topCard);

	return topCard;
}

std::queue<stinkingRich::Card> stinkingRich::Deck::getCards() {
	return cards;
}

void stinkingRich::Card::changeMoney(MoneyType amt) {
	const auto &currentPlayer = stinkingRich::StinkingRich::currentPlayer.lock();
	const auto &currentPlayerComponent = ashley::ComponentMapper<Player>::getMapper().get(
			currentPlayer);

	currentPlayerComponent->addMoney(amt);
}

void stinkingRich::Card::doBirthday(MoneyType money) {
	const auto &playerMapper = ashley::ComponentMapper<Player>::getMapper();

	const auto &currentPlayer = stinkingRich::StinkingRich::currentPlayer.lock();
	const auto &currentPlayerComponent = playerMapper.get(currentPlayer);

	const auto &allPlayers = stinkingRich::StinkingRich::allPlayers;

	int playersFound = 0;

	for (auto &playerWeak : allPlayers) {
		auto player = playerWeak.lock();
		auto playerComponent = playerMapper.get(player);

		if (playerComponent->id == currentPlayerComponent->id) {
			continue;
		} else {
			playersFound++;
			playerComponent->removeMoney(money);
		}
	}

	for (int i = 0; i < playersFound; i++) {
		currentPlayerComponent->addMoney(money);
	}
}

void stinkingRich::Card::repairs(MoneyType houseCost, MoneyType hotelCost) {

}

void stinkingRich::Card::moveToGo() {
	auto playerEntity = stinkingRich::StinkingRich::currentPlayer.lock();
	auto positionComponent = ashley::ComponentMapper<stinkingRich::Position>::getMapper().get(
			playerEntity);
	auto playerComponent = ashley::ComponentMapper<stinkingRich::Player>::getMapper().get(
			playerEntity);

	auto posDetails = positionComponent->position.lock();

	while (true) {
		auto nextEntity = posDetails->nextLocation.lock();
		posDetails = ashley::ComponentMapper<BoardLocation>::getMapper().get(nextEntity);
		positionComponent->position = std::weak_ptr<stinkingRich::BoardLocation>(posDetails);

		if (posDetails->details.type == LocationType::GO) {
			std::cout << "GO: Money changed by " << posDetails->details.value.toString() << ".\n";
			playerComponent->addMoney(posDetails->details.value);
			break;
		}
	}
}

void stinkingRich::Card::moveToMayfair() {
	auto playerEntity = stinkingRich::StinkingRich::currentPlayer.lock();
	auto positionComponent = ashley::ComponentMapper<stinkingRich::Position>::getMapper().get(
			playerEntity);
	auto playerComponent = ashley::ComponentMapper<stinkingRich::Player>::getMapper().get(
			playerEntity);

	auto posDetails = positionComponent->position.lock();

	while (true) {
		auto nextEntity = posDetails->nextLocation.lock();
		posDetails = ashley::ComponentMapper<BoardLocation>::getMapper().get(nextEntity);
		positionComponent->position = std::weak_ptr<stinkingRich::BoardLocation>(posDetails);

		if (posDetails->details.group == PropertyGroup::DARK_BLUE) {
			if (posDetails->details.value == MoneyType(400, 0)) {
				break;
			}
		}
	}

	playerComponent->handleMoveResult(positionComponent);
}

void stinkingRich::Card::moveToTrafalgarSquare() {
	auto playerEntity = stinkingRich::StinkingRich::currentPlayer.lock();
	auto positionComponent = ashley::ComponentMapper<stinkingRich::Position>::getMapper().get(
			playerEntity);
	auto playerComponent = ashley::ComponentMapper<stinkingRich::Player>::getMapper().get(
			playerEntity);

	auto posDetails = positionComponent->position.lock();

	while (true) {
		auto nextEntity = posDetails->nextLocation.lock();
		posDetails = ashley::ComponentMapper<BoardLocation>::getMapper().get(nextEntity);
		positionComponent->position = std::weak_ptr<stinkingRich::BoardLocation>(posDetails);

		if (posDetails->details.type == stinkingRich::LocationType::GO) {
			std::cout << "GO: Money changed by " << posDetails->details.value.toString() << ".\n";
			playerComponent->addMoney(posDetails->details.value);
		}

		if (posDetails->details.group == PropertyGroup::RED) {
			if (posDetails->details.value == MoneyType(240, 0)) {
				break;
			}
		}
	}

	playerComponent->handleMoveResult(positionComponent);
}

void stinkingRich::Card::moveToPallMall() {
	auto playerEntity = stinkingRich::StinkingRich::currentPlayer.lock();
	auto positionComponent = ashley::ComponentMapper<stinkingRich::Position>::getMapper().get(
			playerEntity);
	auto playerComponent = ashley::ComponentMapper<stinkingRich::Player>::getMapper().get(
			playerEntity);

	auto posDetails = positionComponent->position.lock();

	while (true) {
		auto nextEntity = posDetails->nextLocation.lock();
		posDetails = ashley::ComponentMapper<BoardLocation>::getMapper().get(nextEntity);
		positionComponent->position = std::weak_ptr<stinkingRich::BoardLocation>(posDetails);

		if (posDetails->details.type == stinkingRich::LocationType::GO) {
			std::cout << "GO: Money changed by " << posDetails->details.value.toString() << ".\n";
			playerComponent->addMoney(posDetails->details.value);
		}

		if (posDetails->details.group == PropertyGroup::MAGENTA) {
			// works because pall mall is first in group, but brittle
			// TODO: Make this less brittle
			break;
		}
	}

	playerComponent->handleMoveResult(positionComponent);
}

void stinkingRich::Card::moveToMaryleboneStation() {
	auto playerEntity = stinkingRich::StinkingRich::currentPlayer.lock();
	auto positionComponent = ashley::ComponentMapper<stinkingRich::Position>::getMapper().get(
			playerEntity);
	auto playerComponent = ashley::ComponentMapper<stinkingRich::Player>::getMapper().get(
			playerEntity);

	auto posDetails = positionComponent->position.lock();

	while (true) {
		auto nextEntity = posDetails->nextLocation.lock();
		posDetails = ashley::ComponentMapper<BoardLocation>::getMapper().get(nextEntity);
		positionComponent->position = std::weak_ptr<stinkingRich::BoardLocation>(posDetails);

		if (posDetails->details.type == stinkingRich::LocationType::GO) {
			std::cout << "GO: Money changed by " << posDetails->details.value.toString() << ".\n";
			playerComponent->addMoney(posDetails->details.value);
		}

		if (posDetails->details.group == PropertyGroup::STATION) {
			if (posDetails->details.name.substr(0, 4).compare("Mary") == 0) {
				break;
			}
		}
	}

	playerComponent->handleMoveResult(positionComponent);
}

void stinkingRich::Card::moveBackToOldKentRoad() {
	auto playerEntity = stinkingRich::StinkingRich::currentPlayer.lock();
	auto positionComponent = ashley::ComponentMapper<stinkingRich::Position>::getMapper().get(
			playerEntity);
	auto playerComponent = ashley::ComponentMapper<stinkingRich::Player>::getMapper().get(
			playerEntity);

	auto posDetails = positionComponent->position.lock();

	while (true) {
		auto prevEntity = posDetails->prevLocation.lock();
		posDetails = ashley::ComponentMapper<BoardLocation>::getMapper().get(prevEntity);
		positionComponent->position = std::weak_ptr<stinkingRich::BoardLocation>(posDetails);

		if (posDetails->details.group == PropertyGroup::BROWN) {
			if (posDetails->details.name.substr(0, 3).compare(std::string("Old")) == 0) {
				break;
			}
		}
	}

	playerComponent->handleMoveResult(positionComponent);
}

void stinkingRich::Card::moveBackThreeSpaces() {
	auto playerEntity = stinkingRich::StinkingRich::currentPlayer.lock();
	auto positionComponent = ashley::ComponentMapper<stinkingRich::Position>::getMapper().get(
			playerEntity);
	auto playerComponent = ashley::ComponentMapper<stinkingRich::Player>::getMapper().get(
			playerEntity);

	auto posDetails = positionComponent->position.lock();

	for (int i = 0; i < 3; i++) {
		auto prevEntity = posDetails->prevLocation.lock();
		if(prevEntity == nullptr) {
			std::cout.flush();
			std::cerr << "Couldn't move back :(\n.";
			std::cerr.flush();
		} else {
			posDetails = ashley::ComponentMapper<BoardLocation>::getMapper().get(prevEntity);
			positionComponent->position = std::weak_ptr<stinkingRich::BoardLocation>(posDetails);
		}
	}

	playerComponent->handleMoveResult(positionComponent);
}

void stinkingRich::Card::getOutOfJailFree() {

}

void stinkingRich::Card::jailPlayer() {
	auto playerEntity = stinkingRich::StinkingRich::currentPlayer.lock();
	auto playerComponent = ashley::ComponentMapper<stinkingRich::Player>::getMapper().get(
			playerEntity);

	playerComponent->jail();
}
