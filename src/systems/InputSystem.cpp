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
#include "components/MouseListener.hpp"
#include "systems/InputSystem.hpp"

int64_t stinkingRich::InputSystem::die1 = -1;
int64_t stinkingRich::InputSystem::die2 = -1;

stinkingRich::InputSystem::InputSystem(uint64_t priority) :
		EntitySystem(priority) {
}

void stinkingRich::InputSystem::addedToEngine(ashley::Engine &e) {
	ashley::EntitySystem::addedToEngine(e);

	this->engine = &e;
}

void stinkingRich::InputSystem::removedFromEngine(ashley::Engine &e) {
	ashley::EntitySystem::removedFromEngine(e);

	this->engine = nullptr;
}

void stinkingRich::InputSystem::update(float deltaTime) {
	if (pressCooldown > 0.0f) {
		pressCooldown -= deltaTime;
	}

	keyStates = SDL_GetKeyboardState(nullptr);

	bool advancePlayer = false;

	int mouseX = 0;
	int mouseY = 0;
	auto buttons = SDL_GetMouseState(&mouseX, &mouseY);

	if (pressCooldown < 0.0f) {
		pressCooldown = -1.0f;

		if (stinkingRich::StinkingRich::uiRenderSystem->checkProcessing()) {
			const auto mouseListeners = engine->getEntitiesFor(ashley::Family::getFor( {
					typeid(MouseListener) }));

			for (const auto &listener : *mouseListeners) {
				const auto &ml = ashley::ComponentMapper<MouseListener>::getMapper().get(listener);
				const auto &message = ml->message;
				const auto &rect = ml->rect;

				if (SDL_BUTTON_LEFT & buttons) {
					if (mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y
							&& mouseY <= rect.y + rect.h) {
						std::cout << "Got click.\n";
						std::cout.flush();

						switch (message) {
						case MouseMessage::YES: {
							buyProperty();
							if(!getsAnotherGo) advancePlayer = true;
							break;
						}

						case MouseMessage::NO: {
							auctionProperty();
							if(!getsAnotherGo) advancePlayer = true;
							break;
						}

						case MouseMessage::NONE: {
							std::cout << "MouseMessage::NONE Received.\n";
							break;
						}
						}

						stinkingRich::StinkingRich::uiRenderSystem->removeUIEntity();

						pressCooldown = TOTAL_PRESS_COOLDOWN;
						break;
					}
				}
			}
		} else {
			if (keyStates[SDL_SCANCODE_SPACE]) {
				if (!doMove()) {
					if(stinkingRich::StinkingRich::uiRenderSystem->checkProcessing()) {
						advancePlayer = false;
					} else {
						if(!getsAnotherGo) advancePlayer = true;
					}
				}

				pressCooldown = TOTAL_PRESS_COOLDOWN;
			} else if (keyStates[SDL_SCANCODE_F9]) {
				auto c = stinkingRich::StinkingRich::communityChestCards.getTopCard();
				std::cout << c.text << std::endl;
				c.doEffect();
				pressCooldown = TOTAL_PRESS_COOLDOWN;
			} else if (keyStates[SDL_SCANCODE_F10]) {
				auto c = stinkingRich::StinkingRich::chanceCards.getTopCard();
				std::cout << c.text << std::endl;
				c.doEffect();
				pressCooldown = TOTAL_PRESS_COOLDOWN;
			}
		}
	}

	if(advancePlayer) {
		getsAnotherGo = false;
		stinkingRich::StinkingRich::nextPlayer();
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

	die1 = dieOne;
	die2 = dieTwo;

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
			} else {
				getsAnotherGo = true;
			}
		}
	} else {
		getsAnotherGo = false;
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

	if (playerComponent->isJailed()) {
		retVal = false;
	}

	return retVal;
}

void stinkingRich::InputSystem::jailPlayer() {
	std::cout << "You're goin' to JAIL.\n";
	const auto &player = stinkingRich::StinkingRich::currentPlayer.lock();

	ashley::ComponentMapper<Player>::getMapper().get(player)->jail();
}

void stinkingRich::InputSystem::buyProperty() {
	const auto &player = stinkingRich::StinkingRich::currentPlayer.lock();

	const auto &positionMapper = ashley::ComponentMapper<Position>::getMapper();
	const auto &playerMapper = ashley::ComponentMapper<Player>::getMapper();

	const auto &positionComponent = positionMapper.get(player);
	const auto &playerComponent = playerMapper.get(player);

	//TODO: Handle insufficient funds.

	const std::shared_ptr<stinkingRich::BoardLocation> &playerLocation = positionComponent->position.lock();

	std::cout << "Buying \"" <<playerLocation->details.name << "\".\nFunds before: " << playerComponent->getBalance() << ".\n";

	playerLocation->owner = std::weak_ptr<ashley::Entity>(player);
	playerComponent->addMoney(-(playerLocation->details.value));
	stinkingRich::StinkingRich::increasePropertyGroupOwned(playerLocation->details.group);

	std::cout << "Funds after: "<< playerComponent->getBalance() << ".\n";
	std::cout.flush();
}

void stinkingRich::InputSystem::auctionProperty() {
	std::cout << "Auctioning not implemented.\n";
	std::cout.flush();
}
