/*
 * BoardLocation.hpp
 *
 * Created on: 5 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef BOARDLOCATIONCOMPONENT_HPP_
#define BOARDLOCATIONCOMPONENT_HPP_

#include <cstdint>

#include "Ashley/core/Component.hpp"

#include "BoardLocationDetails.hpp"

namespace stinkingRich {

class BoardLocation : public ashley::Component {
public:
	BoardLocation(BoardLocationDetails &details, int8_t boardX, int8_t boardY) : details(details), boardX(boardX), boardY(boardY) {}

	static const int w = 50;
	static const int h = 50;

	stinkingRich::BoardLocationDetails details;

	int8_t boardX; // in "board" coordinates, 0 <= x <= 10
	int8_t boardY; // in "board" coordinates, 0 <= y <= 10
};

}

#endif /* BOARDLOCATION_HPP_ */
