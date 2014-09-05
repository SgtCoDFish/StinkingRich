/*
 * StinkingRich.cpp
 *
 * Created on: 5 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <cstdlib>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <new>
#include <utility>

#include "Ashley/AshleyCore.hpp"

#include "BoardLocationDetails.hpp"
#include "components/AllComponents.hpp"
#include "systems/AllSystems.hpp"
#include "StinkingRich.hpp"

using namespace ashley;
using namespace stinkingRich;

stinkingRich::StinkingRich::StinkingRich(SDL_Window *window, SDL_Surface *surface) : window(window), surface(surface), engine() {
}

stinkingRich::StinkingRich::~StinkingRich() {
}

void stinkingRich::StinkingRich::initBoard() {
	auto locations = stinkingRich::BoardLocationDetails::getAllLocations();

	int8_t posX = 0;
	int8_t posY = 0;

	int8_t xDir = 1;
	int8_t yDir = 0;

	for(auto loc : locations) {
		auto e = std::make_shared<ashley::Entity>();

		e->add<stinkingRich::BoardLocation>(loc, posX, posY);

		posX += xDir;
		posY += yDir;

		if(posX > 10) {
			posX = 10;
			xDir = 0;
			yDir = 1;
		} else if(posY > 10) {
			posY = 10;
			xDir = -1;
			yDir = 0;
		} else if(posX < 0) {
			posX = 0;
			yDir = -1;
			xDir = 0;
		}
	}
}

void stinkingRich::StinkingRich::init() {
	for (const auto &color : playerColors) {
		auto entity = std::make_shared<Entity>();

		entity->add<Player>(color);
		entity->add<Position>(std::rand() % 100, std::rand() % 100);
		entity->add<Renderable>(
				[&](std::shared_ptr<Position> p, const SDL_Color &color, float delta) {
					SDL_Rect rect( {static_cast<int>(p->position.x), static_cast<int>(p->position.y), 32, 32});
					SDL_FillRect(surface, &rect, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
				});

		engine.addEntity(entity);
	}

	engine.addSystem(std::make_shared<PieceRenderSystem>(10000));
}

void stinkingRich::StinkingRich::update(float deltaTime) {
	SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));

	engine.update(deltaTime);

	SDL_UpdateWindowSurface(window);
}
