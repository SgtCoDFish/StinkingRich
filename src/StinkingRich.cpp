/*
 * StinkingRich.cpp
 *
 * Created on: 5 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <cstdlib>
#include <cmath>

#include <iostream>
#include <typeinfo>
#include <vector>
#include <string>
#include <sstream>
#include <new>
#include <utility>
#include <memory>

#include "Ashley/AshleyCore.hpp"

#include "BoardLocationDetails.hpp"
#include "components/AllComponents.hpp"
#include "systems/AllSystems.hpp"
#include "util/InitException.hpp"
#include "StinkingRich.hpp"

class GoLocation;

using namespace ashley;
using namespace stinkingRich;

int32_t stinkingRich::StinkingRich::windowWidth = -1;
int32_t stinkingRich::StinkingRich::windowHeight = -1;
int32_t stinkingRich::StinkingRich::leftGap = -1;
int32_t stinkingRich::StinkingRich::topGap = -1;

bool stinkingRich::StinkingRich::_nextPlayer = false;

std::weak_ptr<ashley::Entity> stinkingRich::StinkingRich::currentPlayer = std::shared_ptr<
		ashley::Entity>(nullptr);

bool stinkingRich::StinkingRich::update(float deltaTime) {
	if (_nextPlayer) {
		_nextPlayer = false;

		auto currentPlayerID = currentPlayer.lock()->getComponent<Player>()->id;
		std::cout << "Advancing player, current id is " << currentPlayerID << std::endl;

		auto players = engine.getEntitiesFor(Family::getFor( { typeid(Player) }));

		if (players->size() > 1) {
			auto playerMapper = ComponentMapper<Player>::getMapper();

			auto it = std::find_if(players->begin(), players->end(),
					[&](std::shared_ptr<ashley::Entity> &ent) {
						auto player = playerMapper.get(ent);
						return player->id == currentPlayerID;
					});

			if (it == players->end()) {
				std::cerr << "Something went horribly wrong, couldn't find current player.\n";
				return true;
			} else {
				it++;

				if (it == players->end()) {
					it = players->begin();
				}

				currentPlayer = std::weak_ptr<ashley::Entity>((*it));
				currentPlayerID = currentPlayer.lock()->getComponent<Player>()->id;
			}
		}

		std::cout << "New current player id is " << currentPlayerID << std::endl;
	}

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
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		std::cerr << "Could not initialise SDL:\n" << SDL_GetError() << std::endl;
		throw stinkingRich::InitException("SDL_Init");
	}

	if (TTF_Init() < 0) {
		std::cerr << "Could not initialise SDL_TTF:\n" << TTF_GetError() << std::endl;
		throw stinkingRich::InitException("TTF_Init");
	}

	windowWidth = 1280;
	windowHeight = 768;

	leftGap = (stinkingRich::StinkingRich::windowWidth - stinkingRich::constants::boardWidth) / 2;
	topGap = (stinkingRich::StinkingRich::windowHeight - stinkingRich::constants::boardHeight) / 2;

	window = SDL_CreateWindow("Stinking Rich", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

	if (window == nullptr) {
		std::cerr << "Could not make window: " << SDL_GetError() << std::endl;
		throw stinkingRich::InitException("window");
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		std::cerr << "Could not initialise renderer: " << SDL_GetError() << std::endl;
		throw stinkingRich::InitException("renderer");
	}

	SDL_SetRenderDrawColor(renderer, 0x66, 0x66, 0x66, 0x66);
}

stinkingRich::StinkingRich::~StinkingRich() {
	currentPlayer = std::shared_ptr<ashley::Entity>(nullptr);
//	players = nullptr;
	go = nullptr;
	engine.removeAllEntities();
	close();
}

void stinkingRich::StinkingRich::initBoard() {
	TTF_Font *font = TTF_OpenFont("assets/RobotoRegular.ttf", 10);

	auto ents = stinkingRich::BoardLocationDetails::getAllBoardEntities(renderer, font);

	for (auto e : ents) {
		engine.addEntity(e);
	}

	auto goEnts = engine.getEntitiesFor(Family::getFor( { typeid(GoLocation) }));

	if (goEnts->size() == 0) {
		throw InitException("No \"Go\"");
	}

	go = std::shared_ptr<ashley::Entity>(goEnts->at(0));

	TTF_CloseFont(font);
}

void stinkingRich::StinkingRich::init() {
	initBoard();

	for (unsigned int i = 0; i < playerColors.size(); i++) {
		auto e = std::make_shared<Entity>();

		e->add<Position>(go->getComponent<BoardLocation>());
		e->add<Player>(playerColors[i]);
		e->add<Renderable>(Renderable::getTextureFromColor(renderer, playerColors[i], 32, 32));

		engine.addEntity(e);
	}

	// all players should be added before this point
	auto players = engine.getEntitiesFor(Family::getFor( { typeid(Player) }));
	if (players == nullptr || players->size() == 0) {
		throw stinkingRich::InitException("Could not init players.");
	}

	currentPlayer = std::shared_ptr<ashley::Entity>(players->at(0));

	engine.addSystem(std::make_shared<InputSystem>(100));
	engine.addSystem(std::make_shared<BoardRenderSystem>(renderer, 9000));
	engine.addSystem(std::make_shared<PieceRenderSystem>(renderer, 10000));
}

void stinkingRich::StinkingRich::nextPlayer() {
	_nextPlayer = true;
}

void stinkingRich::StinkingRich::close() {
	if (renderer != nullptr) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	SDL_DestroyWindow(window);
	window = nullptr;

	TTF_Quit();
	SDL_Quit();
}
