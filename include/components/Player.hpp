/*
 * Player.hpp
 *
 * Created on: 2 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <SDL2/SDL.h>

namespace stinkingRich {

class Player : public ashley::Component {
public:
	Player() : color({0xFF, 0x00, 0x00, 0x00}) {}
	Player(SDL_Color color) : color(color) {}

	SDL_Color color;
};

}

#endif /* PLAYER_HPP_ */
