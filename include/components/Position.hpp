/*
 * Position.hpp
 *
 * Created on: 3 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include "glm/glm.hpp"

namespace stinkingRich {

class Position : public ashley::Component {
public:
	glm::vec2 position;

	Position() : position(glm::vec2(0.0f, 0.0f)) {}
	Position(float x, float y) : position(glm::vec2(x, y)) {}
	Position(glm::vec2 position) : position(position) {}
};

}



#endif /* POSITION_HPP_ */
