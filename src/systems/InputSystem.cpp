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

	if (pressCooldown < 0.0f) {
		pressCooldown = -1.0f;

		keyStates = SDL_GetKeyboardState(nullptr);

		if (keyStates[SDL_SCANCODE_SPACE]) {
			if (doMove()) {

			}

			pressCooldown = TOTAL_PRESS_COOLDOWN;
		} else if (keyStates[SDL_SCANCODE_RETURN]) {
			stinkingRich::StinkingRich::nextPlayer();
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

	int dieOne = (std::rand() % 6) + 1;
	int dieTwo = (std::rand() % 6) + 1;

	int totalMove = dieOne + dieTwo;

	std::cout << "Rolled " << dieOne << " and " << dieTwo << ", moving " << totalMove
			<< " spaces.\n";

	if (dieOne == dieTwo) {
		playerComponent->rolledDouble();
		int doubles = playerComponent->getDoublesRolled();

		std::cout << "Double rolled, total of " << doubles << ".\n";
		retVal = true;

		if (doubles == 3) {
			jailPlayer();
			return false;
		}
	}

	std::cout.flush();

	auto boardLocationMapper = ashley::ComponentMapper<stinkingRich::BoardLocation>::getMapper();

	for (int i = 0; i < totalMove; i++) {
		auto newLocation = positionComponent->position.lock();
		auto newLoc = newLocation->nextLocation.lock();
		auto newBoardLoc = boardLocationMapper.get(newLoc);

		newLocation = nullptr;
		newLoc = nullptr;

		positionComponent->position = std::shared_ptr<BoardLocation>(newBoardLoc);
		stinkingRich::LocationType &type = newBoardLoc->details.type;

		if (type == stinkingRich::LocationType::GO) {
			std::cout << "GO: Money changed by " << newBoardLoc->details.value.toString() << ".\n";
			playerComponent->addMoney(newBoardLoc->details.value);
		}

		if (i == (totalMove - 1)) {
			if (type == stinkingRich::LocationType::INCOME_TAX
					|| type == stinkingRich::LocationType::SUPER_TAX) {
				std::cout << "Tax: Money changed by " << newBoardLoc->details.value.toString()
						<< ".\n";

				playerComponent->addMoney(newBoardLoc->details.value);
			} else if (type == stinkingRich::LocationType::PROPERTY) {
				std::cout << "Landed on " << newBoardLoc->details.name << ".\n";
			} else if (type == stinkingRich::LocationType::GO_TO_JAIL) {
				jailPlayer();
				retVal = false;
			}
		}

		newLoc = nullptr;
	}

	std::cout.flush();

	return retVal;
}

void stinkingRich::InputSystem::jailPlayer() {
	std::cout << "You're goin' to JAIL.\n";
	std::cerr << "NYI\n";
}
