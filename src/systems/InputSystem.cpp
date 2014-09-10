/*
 * InputSystem.cpp
 *
 * Created on: 8 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <cstdint>
#include <cmath>

#include <iostream>
#include <memory>

#include "SDL2/SDL.h"

#include "Ashley/AshleyCore.hpp"

#include "StinkingRich.hpp"
#include "BoardLocationDetails.hpp"
#include "components/Player.hpp"
#include "components/Position.hpp"
#include "components/BoardLocation.hpp"
#include "systems/InputSystem.hpp"

stinkingRich::InputSystem::InputSystem(uint64_t priority) :
		EntitySystem(priority) {
}

void stinkingRich::InputSystem::update(float deltaTime) {
	if (pressCooldown > 0.0f) {
		pressCooldown -= deltaTime;
	}

	keyStates = SDL_GetKeyboardState(nullptr);

	if (pressCooldown < 0.0f) {
		pressCooldown = -1.0f;

		if (keyStates[SDL_SCANCODE_SPACE]) {
			if (!doMove()) {
				stinkingRich::StinkingRich::nextPlayer();
			}

			pressCooldown = TOTAL_PRESS_COOLDOWN;
		} else if (keyStates[SDL_SCANCODE_F9]) {
			auto c = stinkingRich::StinkingRich::communityChestCards.getTopCard();
			std::cout << c.text << std::endl;
			c.doEffect();
			pressCooldown = TOTAL_PRESS_COOLDOWN;
		}else if (keyStates[SDL_SCANCODE_F10]) {
			auto c = stinkingRich::StinkingRich::chanceCards.getTopCard();
			std::cout << c.text << std::endl;
			c.doEffect();
			pressCooldown = TOTAL_PRESS_COOLDOWN;
		}
	}
}

// returns true if the player gets another go.
bool stinkingRich::InputSystem::doMove() {
	bool retVal = false;

	auto playerEntity = stinkingRich::StinkingRich::currentPlayer.lock();
	auto positionComponent = ashley::ComponentMapper<stinkingRich::Position>::getMapper().get(
			playerEntity);
	auto playerComponent = ashley::ComponentMapper<stinkingRich::Player>::getMapper().get(
			playerEntity);

	int dieOne = stinkingRich::StinkingRich::getRand(1, 6);
	int dieTwo = stinkingRich::StinkingRich::getRand(1, 6);

	int totalMove = dieOne + dieTwo;

	if (keyStates[SDL_SCANCODE_1]) {
		totalMove = 1;
	} else if (keyStates[SDL_SCANCODE_5]) {
		totalMove = 5;
	}

	std::cout << "Rolled " << dieOne << " and " << dieTwo << ", moving " << totalMove
			<< " spaces.\n";

	if (dieOne == dieTwo) {
		playerComponent->rolledDouble();
		int doubles = playerComponent->getDoublesRolled();

		std::cout << "Double rolled, total of " << doubles << ".\n";

		if (playerComponent->isJailed()) {
			playerComponent->freeFromJail();
		} else {
			retVal = true;

			if (doubles == 3) {
				jailPlayer();
				return false;
			}
		}
	}

	if (!playerComponent->isJailed()) {
		auto boardLocationMapper =
				ashley::ComponentMapper<stinkingRich::BoardLocation>::getMapper();

		for (int i = 0; i < totalMove; i++) {
			auto newLocation = positionComponent->position.lock();
			auto newLoc = newLocation->nextLocation.lock();
			auto newBoardLoc = boardLocationMapper.get(newLoc);

			newLocation = nullptr;
			newLoc = nullptr;

			positionComponent->position = std::shared_ptr<BoardLocation>(newBoardLoc);
			stinkingRich::LocationType &type = newBoardLoc->details.type;

			if (type == stinkingRich::LocationType::GO) {
				std::cout << "GO: Money changed by " << newBoardLoc->details.value.toString()
						<< ".\n";
				playerComponent->addMoney(newBoardLoc->details.value);
			}

			if (i == (totalMove - 1)) {
				playerComponent->handleMoveResult(positionComponent);
			}

			newLoc = nullptr;
		}
	}

	std::cout.flush();

	if(playerComponent->isJailed()) {
		retVal = false;
	}

	return retVal;
}

void stinkingRich::InputSystem::jailPlayer() {
	std::cout << "You're goin' to JAIL.\n";
	const auto &player = stinkingRich::StinkingRich::currentPlayer.lock();

	ashley::ComponentMapper<Player>::getMapper().get(player)->jail();
}
