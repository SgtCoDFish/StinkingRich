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
#include "util/InitException.hpp"
#include "StinkingRich.hpp"

using namespace ashley;
using namespace stinkingRich;

int32_t stinkingRich::StinkingRich::windowWidth = -1;
int32_t stinkingRich::StinkingRich::windowHeight = -1;

bool stinkingRich::StinkingRich::update(float deltaTime) {
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			return true;
		}
	}

	SDL_RenderClear(renderer);

	engine.update(deltaTime);

	SDL_RenderPresent(renderer);

	return false;
}

stinkingRich::StinkingRich::StinkingRich() :
		engine() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Could not initialise SDL:\n" << SDL_GetError() << std::endl;
		throw stinkingRich::InitException("SDL_Init");
	}

	if(TTF_Init() < 0) {
		std::cerr << "Could not initialise SDL_TTF:\n" << TTF_GetError() << std::endl;
		throw stinkingRich::InitException("TTF_Init");
	}

	windowWidth = 1280;
	windowHeight = 768;

	window = SDL_CreateWindow("Stinking Rich", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);


	if (window == nullptr) {
		std::cerr << "Could not make window: " << SDL_GetError() << std::endl;
		throw stinkingRich::InitException("window");
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == nullptr) {
		std::cerr << "Could not initialise renderer: " << SDL_GetError() << std::endl;
		throw stinkingRich::InitException("renderer");
	}

	SDL_SetRenderDrawColor(renderer, 0x66, 0x66, 0x66, 0x66);
}

stinkingRich::StinkingRich::~StinkingRich() {
	close();
}

void stinkingRich::StinkingRich::initBoard() {
	TTF_Font *font = TTF_OpenFont("assets/RobotoRegular.ttf", 10);

	auto ents = stinkingRich::BoardLocationDetails::getAllBoardEntities(renderer, font);

	for(auto e : ents) {
		engine.addEntity(e);
	}

	TTF_CloseFont(font);
}

void stinkingRich::StinkingRich::init() {
	initBoard();

	engine.addSystem(std::make_shared<BoardRenderSystem>(renderer, 9000));
	engine.addSystem(std::make_shared<PieceRenderSystem>(renderer, 10000));
}

void stinkingRich::StinkingRich::close() {
	if(renderer != nullptr) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	SDL_DestroyWindow(window);
	window = nullptr;

	TTF_Quit();
	SDL_Quit();
}
