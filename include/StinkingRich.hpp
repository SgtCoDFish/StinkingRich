/*
 * StinkingRich.hpp
 *
 * Created on: 5 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef STINKINGRICHMAIN_HPP_
#define STINKINGRICHMAIN_HPP_

#include <vector>
#include <string>
#include <memory>

#include "Ashley/core/Engine.hpp"
#include "Ashley/core/Entity.hpp"

#include "SDL2/SDL.h"

namespace stinkingRich {

class StinkingRich {
private:
	static const int BOARD_LOCATION_COUNT = 40;

	static bool _nextPlayer;

	SDL_Window *window;

	SDL_Renderer *renderer;

	ashley::Engine engine;

	const uint8_t playerAlpha = 0xAA;
	const std::vector<SDL_Color> playerColors = { { 0xFF, 0x00, 0x00, playerAlpha }, // red
			{ 0x00, 0xFF, 0x00, playerAlpha }, //green
			{ 0x00, 0x00, 0xFF, playerAlpha } //blue
	};

	std::shared_ptr<ashley::Entity> go = nullptr;
//	std::vector<std::shared_ptr<ashley::Entity>> *players = nullptr;

	void initBoard();
public:
	static int32_t windowWidth;
	static int32_t windowHeight;

	static int32_t leftGap;
	static int32_t topGap;

	static std::weak_ptr<ashley::Entity> currentPlayer;

	StinkingRich();
	~StinkingRich();

	StinkingRich(StinkingRich &other) = delete;
	StinkingRich(StinkingRich &&other) = delete;

	StinkingRich &operator=(StinkingRich &other) = delete;
	StinkingRich &operator=(StinkingRich &&other) = delete;

	void init();
	bool update(float deltaTime);
	void close();

	static void nextPlayer();
};

}



#endif /* STINKINGRICH_HPP_ */
