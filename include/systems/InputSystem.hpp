/*
 * InputSystem.hpp
 *
 * Created on: 8 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef INPUTSYSTEM_HPP_
#define INPUTSYSTEM_HPP_

#include <cstdint>

#include "Ashley/core/Engine.hpp"
#include "Ashley/core/EntitySystem.hpp"

namespace stinkingRich {

class InputSystem : public ashley::EntitySystem {
	constexpr static float TOTAL_PRESS_COOLDOWN = 0.5f;

	static int64_t die1;
	static int64_t die2;

	const uint8_t *keyStates = nullptr;

	ashley::Engine *engine = nullptr;

	float pressCooldown = -1.0f;

	bool getsAnotherGo = false;

	bool doMove();
	void jailPlayer();

	void buyProperty();
	void auctionProperty();

public:
	InputSystem(uint64_t priority);

	void addedToEngine(ashley::Engine &e) override;
	void removedFromEngine(ashley::Engine &e) override;

	void update(float deltaTime) override;

	static inline int64_t getDieOne() {
		return die1;
	}

	static inline int64_t getDieTwo() {
		return die2;
	}
};

}

#endif /* INPUTSYSTEM_HPP_ */
