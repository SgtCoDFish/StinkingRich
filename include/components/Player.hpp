/*
 * Player.hpp
 *
 * Created on: 2 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <cstdint>

#include <string>
#include <memory>

#include <SDL2/SDL.h>

#include "Ashley/core/Component.hpp"

#include "StinkingRichConstants.hpp"
#include "components/Position.hpp"

namespace stinkingRich {

class Player : public ashley::Component {
public:
	const uint64_t id;
	SDL_Color color;

	Player() :
			Player( { 0xFF, 0x00, 0x00, 0x00 }) {
	}

	Player(SDL_Color color) :
			id(nextID++), color(color), balance(constants::startingMoney), doublesRolled(0), turnsLeftInJail(
					0) {
		made++;
	}

	~Player() {
		made--;
	}

	void addMoney(MoneyType amount);
	void removeMoney(MoneyType amount);

	const std::string getBalance() const;

	void rolledDouble();
	void resetDoubles();
	void spentTurnInJail();

	inline bool isJailed() {
		return turnsLeftInJail > 0;
	}

	void jail();

	inline void freeFromJail() {
		turnsLeftInJail = 0;
	}

	int8_t getTurnsLeftInJail() const;
	int8_t getDoublesRolled() const;

	void handleMoveResult(std::shared_ptr<Position>& pos);

	/**
	 * @return the total number of created Player
	 */
	static int64_t getTotalPlayerCount();

private:
	static uint64_t nextID;
	static int64_t made;

	MoneyType balance;

	int doublesRolled;
	int turnsLeftInJail;
};

}

#endif /* PLAYER_HPP_ */
