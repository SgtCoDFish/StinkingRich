/*
 * Position.hpp
 *
 * Created on: 3 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <cstdint>
#include <memory>

#include "components/BoardLocation.hpp"

namespace stinkingRich {

class Position : public ashley::Component {
public:
	std::weak_ptr<BoardLocation> position = std::shared_ptr<BoardLocation>(nullptr);

	Position(std::shared_ptr<BoardLocation> pos) : position(std::weak_ptr<BoardLocation>(pos)) {}
};

}



#endif /* POSITION_HPP_ */
