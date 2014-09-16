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
#include <random>
#include <map>

#include "Ashley/AshleyCore.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "BoardLocationDetails.hpp"
#include "StinkingRich.hpp"
#include "components/AllComponents.hpp"
#include "systems/AllSystems.hpp"
#include "util/InitException.hpp"
#include "util/TextRenderer.hpp"
#include "util/PropGroupCounter.hpp"

class GoLocation;

using namespace ashley;
using namespace stinkingRich;


int32_t stinkingRich::StinkingRich::windowWidth = -1;
int32_t stinkingRich::StinkingRich::windowHeight = -1;
int32_t stinkingRich::StinkingRich::leftGap = -1;
int32_t stinkingRich::StinkingRich::topGap = -1;

bool stinkingRich::StinkingRich::_nextPlayer = false;

std::map<PropertyGroup, stinkingRich::PropGroupCounter> stinkingRich::StinkingRich::groupMap;

std::mt19937_64 stinkingRich::StinkingRich::randomEngine = std::mt19937_64(std::random_device().operator ()());

std::unique_ptr<stinkingRich::TextRenderer> stinkingRich::StinkingRich::textRenderer = nullptr;
// the ui render system uses the text renderer so the text renderer must be initialised first.
std::shared_ptr<UIRenderSystem> stinkingRich::StinkingRich::uiRenderSystem = nullptr;

std::weak_ptr<ashley::Entity> stinkingRich::StinkingRich::currentPlayer = std::shared_ptr<
		ashley::Entity>(nullptr);

std::vector<std::weak_ptr<ashley::Entity>> stinkingRich::StinkingRich::allPlayers;

Deck stinkingRich::StinkingRich::chanceCards = Deck(stinkingRich::CardType::CHANCE);
Deck stinkingRich::StinkingRich::communityChestCards = Deck(stinkingRich::CardType::COMMUNITY_CHEST);

bool stinkingRich::StinkingRich::update(float deltaTime) {
	if(handleNextPlayer()) {
		return true;
	}

	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			return true;
		}
	}

	SDL_SetRenderDrawColor(renderer, 0x66, 0x66, 0x66, 0x66);
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

	textRenderer = std::make_unique<stinkingRich::TextRenderer>("assets/RobotoRegular.ttf", 10);

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

	StinkingRich::uiRenderSystem = std::make_shared<UIRenderSystem>(renderer, 20000);

	SDL_SetRenderDrawColor(renderer, 0x66, 0x66, 0x66, 0x66);
}

stinkingRich::StinkingRich::~StinkingRich() {
	currentPlayer = std::shared_ptr<ashley::Entity>(nullptr);
	textRenderer = nullptr;
//	players = nullptr;
	go = nullptr;
	engine.removeAllEntities();
	close();
}

void stinkingRich::StinkingRich::initGroupMap() {
	groupMap[PropertyGroup::BROWN] = PropGroupCounter(2);
	groupMap[PropertyGroup::LIGHT_BLUE] = PropGroupCounter(3);
	groupMap[PropertyGroup::MAGENTA] = PropGroupCounter(3);
	groupMap[PropertyGroup::ORANGE] = PropGroupCounter(3);
	groupMap[PropertyGroup::RED] = PropGroupCounter(3);
	groupMap[PropertyGroup::YELLOW] = PropGroupCounter(3);
	groupMap[PropertyGroup::GREEN] = PropGroupCounter(3);
	groupMap[PropertyGroup::DARK_BLUE] = PropGroupCounter(2);

	groupMap[PropertyGroup::STATION] = PropGroupCounter(4);
	groupMap[PropertyGroup::UTILITY] = PropGroupCounter(2);
}

void stinkingRich::StinkingRich::initBoard() {
	auto ents = stinkingRich::BoardLocationDetails::getAllBoardEntities(renderer);

	for (auto e : ents) {
		engine.addEntity(e);
	}

	auto goEnts = engine.getEntitiesFor(Family::getFor( { typeid(GoLocation) }));

	if (goEnts->size() == 0) {
		throw InitException("No \"Go\"");
	}

	go = std::shared_ptr<ashley::Entity>(goEnts->at(0));
}

void stinkingRich::StinkingRich::init() {
	initBoard();
	initGroupMap();

	for (unsigned int i = 0; i < playerColors.size(); i++) {
		auto e = std::make_shared<Entity>();

		e->add<Position>(go->getComponent<BoardLocation>());
		e->add<Player>(playerColors[i]);
		e->add<Renderable>(Renderable::getTextureFromColor(renderer, playerColors[i], 32, 32));

		engine.addEntity(e);
	}

	// all players should be added before this point
	auto players = engine.getEntitiesFor(Family::getFor( { typeid(Player) }));
	for(auto player : *players) {
		allPlayers.emplace_back(std::weak_ptr<ashley::Entity>(player));
	}

	if (players == nullptr || players->size() == 0) {
		throw stinkingRich::InitException("Could not init players.");
	}

	currentPlayer = std::shared_ptr<ashley::Entity>(players->at(0));

	engine.addSystem(std::make_shared<InputSystem>(100));
	engine.addSystem(std::make_shared<BoardRenderSystem>(renderer, 9000));
	engine.addSystem(std::make_shared<PieceRenderSystem>(renderer, 10000));
	engine.addSystem(uiRenderSystem);
}

void stinkingRich::StinkingRich::nextPlayer() {
	_nextPlayer = true;
}

bool stinkingRich::StinkingRich::handleNextPlayer() {
	if (_nextPlayer) {
		_nextPlayer = false;

		auto currentPlayerComponent = currentPlayer.lock()->getComponent<Player>();
		auto currentPlayerID = currentPlayerComponent->id;
		currentPlayerComponent->resetDoubles();

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

	return false;
}

void stinkingRich::StinkingRich::increasePropertyGroupOwned(PropertyGroup group) {
	groupMap[group].addOwner(ashley::ComponentMapper<Player>::getMapper().get(currentPlayer.lock()));
	std::cout << "Group's owned count now at " << groupMap[group].getOwnedCount() << ".\n";
	std::cout.flush();
}

bool stinkingRich::StinkingRich::isAllInGroupOwned(PropertyGroup group) {
	return groupMap[group].isAllSameOwner();
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
