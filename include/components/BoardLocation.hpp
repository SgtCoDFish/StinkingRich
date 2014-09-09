/*
 * BoardLocation.hpp
 *
 * Created on: 5 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef BOARDLOCATIONCOMPONENT_HPP_
#define BOARDLOCATIONCOMPONENT_HPP_

#include <cstdint>

#include "glm/glm.hpp"

#include "Ashley/core/Component.hpp"

#include "BoardLocationDetails.hpp"

namespace stinkingRich {

class BoardLocation : public ashley::Component {
public:
	BoardLocation(BoardLocationDetails &details, int8_t boardX, int8_t boardY) : details(details), boardX(boardX), boardY(boardY) {}

	stinkingRich::BoardLocationDetails details;

	int8_t boardX; // in "board" coordinates, 0 <= x <= 10
	int8_t boardY; // in "board" coordinates, 0 <= y <= 10

	std::weak_ptr<ashley::Entity> nextLocation = std::shared_ptr<ashley::Entity>(nullptr);
	std::weak_ptr<ashley::Entity> prevLocation = std::shared_ptr<ashley::Entity>(nullptr);

	glm::ivec2 getWindowPosition(int32_t xOffset, int32_t yOffset, int32_t width, int32_t height) const;
};

}

#endif /* BOARDLOCATION_HPP_ */
