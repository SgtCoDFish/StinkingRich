/*
 * StinkingRich.hpp
 *
 * Created on: 5 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef STINKINGRICHMAIN_HPP_
#define STINKINGRICHMAIN_HPP_

#include <cstdint>

#include <map>
#include <memory>
#include <random>
#include <vector>
#include <chrono>

#include "SDL2/SDL.h"

#include "Ashley/core/Engine.hpp"

#include "cards/Card.hpp"
#include "systems/UIRenderSystem.hpp"
#include "util/TextRenderer.hpp"
#include "util/PropGroupCounter.hpp"
#include "components/Player.hpp"

struct SDL_Renderer;
namespace ashley {
class Entity;
}

namespace stinkingRich {

class StinkingRich {
private:
	static const int BOARD_LOCATION_COUNT = 40;

	static std::unique_ptr<stinkingRich::TextRenderer> textRenderer;

	static std::mt19937_64 randomEngine;

	static bool _nextPlayer;

	static std::map<PropertyGroup, PropGroupCounter> groupMap;
	static void initGroupMap();

	SDL_Window *window;

	SDL_Renderer *renderer;

	ashley::Engine engine;

	const uint8_t playerAlpha = 0xDD;
	const std::vector<SDL_Color> playerColors = { { 0xFF, 0x66, 0x22, playerAlpha }, // red
			{ 0x22, 0xFF, 0x22, playerAlpha }, //green
			{ 0x22, 0x22, 0xFF, playerAlpha } //blue
	};

	std::chrono::high_resolution_clock::time_point nseed1; // used for timing initialisation and then seeding prng

	std::shared_ptr<ashley::Entity> go = nullptr;

	void initBoard();
	bool handleNextPlayer();
public:
	static int32_t windowWidth;
	static int32_t windowHeight;

	static int32_t leftGap;
	static int32_t topGap;

	static std::shared_ptr<stinkingRich::UIRenderSystem> uiRenderSystem;

	static std::weak_ptr<ashley::Entity> currentPlayer;
	static std::vector<std::weak_ptr<ashley::Entity>> allPlayers;

	static Deck chanceCards;
	static Deck communityChestCards;

	StinkingRich();
	~StinkingRich();

	StinkingRich(StinkingRich &other) = delete;
	StinkingRich(StinkingRich &&other) = delete;

	StinkingRich &operator=(StinkingRich &other) = delete;
	StinkingRich &operator=(StinkingRich &&other) = delete;

	void init();
	bool update(float deltaTime);
	void close();

	static void increasePropertyGroupOwned(PropertyGroup group);
	static bool isAllInGroupOwned(PropertyGroup group);
	static int countOwnedByPlayer(std::shared_ptr<stinkingRich::Player> player, PropertyGroup group);

	static void nextPlayer();

	static inline int64_t getRand(int64_t min, int64_t max) {
		return std::uniform_int_distribution<>(min, max).operator ()(randomEngine);
	}

	static inline std::mt19937_64 &getRandEngine() {
		return randomEngine;
	}

	static inline TextRenderer *getTextRenderer() {
		return textRenderer.get();
	}
};

}

#endif /* STINKINGRICH_HPP_ */
