/*
 * InputSystem.hpp
 *
 * Created on: 8 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef INPUTSYSTEM_HPP_
#define INPUTSYSTEM_HPP_

#include <cstdint>

#include "Ashley/core/EntitySystem.hpp"

namespace stinkingRich {

class InputSystem : public ashley::EntitySystem {
	constexpr static float TOTAL_PRESS_COOLDOWN = 1.0f;

	const uint8_t *keyStates = nullptr;

	float pressCooldown = -1.0f;

	bool doMove();
	void jailPlayer();
public:
	InputSystem(uint64_t priority);

	void update(float deltaTime) override;

};

}

#endif /* INPUTSYSTEM_HPP_ */
