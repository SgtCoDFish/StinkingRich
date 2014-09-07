/*
 * Position.hpp
 *
 * Created on: 3 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <cstdint>

#include "glm/glm.hpp"

namespace stinkingRich {

class Position : public ashley::Component {
public:
	glm::ivec2 position;

	Position() : position(glm::vec2(0, 0)) {}
	Position(int32_t x, int32_t y) : position(glm::ivec2(x, y)) {}
	Position(glm::ivec2 position) : position(position) {}
};

}



#endif /* POSITION_HPP_ */
