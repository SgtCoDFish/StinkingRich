/*
 * Position.hpp
 *
 * Created on: 3 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <cstdint>

#include "components/BoardLocation.hpp"

namespace stinkingRich {

class Position : public ashley::Component {
public:
	std::shared_ptr<BoardLocation> position;

	Position(std::shared_ptr<BoardLocation> pos) : position(pos) {}
};

}



#endif /* POSITION_HPP_ */
