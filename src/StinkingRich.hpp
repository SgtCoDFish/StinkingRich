/*
 * StinkingRich.hpp
 *
 * Created on: 5 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef STINKINGRICH_HPP_
#define STINKINGRICH_HPP_

#include <vector>
#include <string>

#include "Ashley/core/Engine.hpp"
#include "Ashley/core/Entity.hpp"

#include "SDL2/SDL.h"

namespace stinkingRich {

class StinkingRich {
private:
	static const int BOARD_LOCATION_COUNT = 40;

	SDL_Window *window;
	SDL_Surface *surface;

	ashley::Engine engine;

	const std::vector<SDL_Color> playerColors = { { 0xFF, 0x00, 0x00, 0xFF }, // red
			{ 0x00, 0xFF, 0x00, 0xFF }, //green
			{ 0x00, 0x00, 0xFF, 0xFF } //blue
	};

	std::vector<ashley::Entity> players;

	void initBoard();
public:
	StinkingRich(SDL_Window *window, SDL_Surface *surface);
	~StinkingRich();

	StinkingRich(StinkingRich &other) = delete;
	StinkingRich(StinkingRich &&other) = delete;

	StinkingRich &operator=(StinkingRich &other) = delete;
	StinkingRich &operator=(StinkingRich &&other) = delete;

	void init();
	void update(float deltaTime);
};

}



#endif /* STINKINGRICH_HPP_ */
