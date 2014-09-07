/*
 * StinkingRich.cpp
 *
 * Created on: 5 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <cstdlib>
#include <cmath>

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

	int8_t posX = 10;
	int8_t posY = 0;

	int8_t xDiff = 0;
	int8_t yDiff = 0;

	int8_t xDir = -1;
	int8_t yDir = 0;

	for(auto loc : locations) {
		auto e = std::make_shared<ashley::Entity>();

		e->add<stinkingRich::BoardLocation>(loc, posX, posY);

		posX += xDir;
		posY += yDir;

		xDiff += xDir;
		yDiff += yDir;

		if(xDiff == 10) {
			xDiff = 0;
			xDir = 0;
			yDir = -1;
		} else if(yDiff == 10) {
			yDiff = 0;
			xDir = 1;
			yDir = 0;
		} else if(xDiff == -10) {
			xDiff = 0;
			xDir = 0;
			yDir = 1;
		}

		engine.addEntity(e);
	}
}

void stinkingRich::StinkingRich::init() {
//	for (const auto &color : playerColors) {
//		auto entity = std::make_shared<Entity>();
//
//		entity->add<Player>(color);
//		entity->add<Position>(std::rand() % 100, std::rand() % 100);
//		entity->add<Renderable>(
//				[&](std::shared_ptr<Position> p, const SDL_Color &color, float delta) {
//					SDL_Rect rect( {static_cast<int>(p->position.x), static_cast<int>(p->position.y), 32, 32});
//					SDL_FillRect(surface, &rect, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
//				});
//
//		engine.addEntity(entity);
//	}

	initBoard();

	engine.addSystem(std::make_shared<PieceRenderSystem>(surface, 10000));
	engine.addSystem(std::make_shared<BoardRenderSystem>(surface, 9000));
}

void stinkingRich::StinkingRich::update(float deltaTime) {
	SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));

	const int totalBoardWidth = stinkingRich::BoardLocation::boardW;
	const int totalBoardHeight = stinkingRich::BoardLocation::boardH;

	const SDL_Rect sideRectL = { 0, 0, (surface->w - totalBoardWidth) / 2, surface->h };
	const SDL_Rect sideRectR = { ((surface->w - totalBoardWidth) / 2) + totalBoardWidth, 0,
			(surface->w - totalBoardWidth) / 2, surface->h };

	SDL_FillRect(surface, &sideRectL, SDL_MapRGBA(surface->format, 0, 0, 0, 0xff));
	SDL_FillRect(surface, &sideRectR, SDL_MapRGBA(surface->format, 0, 0, 0, 0xff));

	const SDL_Rect topRect = { (surface->w - totalBoardWidth) / 2, 0, totalBoardWidth, (surface->h
			- totalBoardHeight) / 2 };
	const SDL_Rect bottomRect = { (surface->w - totalBoardWidth) / 2,
			(surface->h - totalBoardHeight) / 2 + totalBoardHeight, totalBoardWidth, (surface->h
					- totalBoardHeight) / 2 };

	SDL_FillRect(surface, &topRect, SDL_MapRGBA(surface->format, 0, 0, 0, 0xff));
	SDL_FillRect(surface, &bottomRect, SDL_MapRGBA(surface->format, 0, 0, 0, 0xff));

	engine.update(deltaTime);

	SDL_UpdateWindowSurface(window);
}
