/*
 * HUDRenderSystem.cpp
 *
 * Created on: 16 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <typeinfo>
#include <sstream>

#include "Ashley/AshleyCore.hpp"

#include "StinkingRichConstants.hpp"
#include "StinkingRich.hpp"
#include "components/Player.hpp"
#include "components/Renderable.hpp"
#include "systems/HUDRenderSystem.hpp"
#include "util/TextRenderer.hpp"

void stinkingRich::HUDRenderSystem::update(float deltaTime) {
	const int x = stinkingRich::StinkingRich::leftGap + stinkingRich::constants::boardWidth + 1;
	const int y = stinkingRich::StinkingRich::topGap;

	const int w = stinkingRich::StinkingRich::windowWidth - stinkingRich::StinkingRich::leftGap
			- 15;
	const int h = stinkingRich::constants::boardHeight;

	const SDL_Rect rect = { x, y, w, h };

	const auto &textRenderer = stinkingRich::StinkingRich::getTextRenderer();

	auto players = engine->getEntitiesFor(ashley::Family::getFor( { typeid(stinkingRich::Player),
			typeid(stinkingRich::Renderable) }));

	const auto &playerMapper = ashley::ComponentMapper<stinkingRich::Player>::getMapper();
	const auto &renderableMapper = ashley::ComponentMapper<stinkingRich::Renderable>::getMapper();

	const auto playerWidth = renderableMapper.get(players->at(0))->w;
	const auto playerHeight = renderableMapper.get(players->at(0))->h;

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, &rect);

	int fontPaddingTop = 0;
	auto fontHeight = TTF_FontHeight(textRenderer->getFont());

	if (fontHeight < playerHeight) {
		fontPaddingTop = (playerHeight - fontHeight) / 2;
	}

	SDL_Surface *tempSurface = SDL_CreateRGBSurface(0, w, h, 32, 0x000000FF, 0x0000FF00, 0x00FF0000,
			0xFF000000);
	SDL_FillRect(tempSurface, nullptr, SDL_MapRGBA(tempSurface->format, 0xFF, 0xFF, 0xFF, 0xFF));

	const int leftPadding = 5;
	const int textRenderX = playerWidth + leftPadding*2;
	int textRenderY = (h/10) + fontPaddingTop;

	for (unsigned int i = 0; i < players->size(); i++) {
		auto playerComponent = playerMapper.get(players->at(i));
		auto currentPlayerID = playerMapper.get(stinkingRich::StinkingRich::currentPlayer.lock())->id;

		std::stringstream ss;
		if(playerComponent->id == currentPlayerID) {
			ss << "*";
		}

		ss << playerComponent->getBalance();

		textRenderer->setColor( { 0x00, 0x00, 0x00, 0xFF });
		textRenderer->renderToSurface(tempSurface, textRenderX, textRenderY,
				ss.str(), w);

		textRenderY += (h / 5);
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, tempSurface);

	SDL_RenderCopy(renderer, texture, nullptr, &rect);

	for (unsigned int i = 0; i < players->size(); i++) {
		auto renderableComponent = renderableMapper.get(players->at(i));

		const int playerY = y + (h / 10) + i * (h / 5);

		const SDL_Rect dstRect = { x + leftPadding, playerY, renderableComponent->w,
				renderableComponent->h };
		SDL_RenderCopy(renderer, renderableComponent->texture, nullptr, &dstRect);
	}

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderDrawRect(renderer, &rect);

	SDL_FreeSurface(tempSurface);
	SDL_DestroyTexture(texture);
}

void stinkingRich::HUDRenderSystem::addedToEngine(ashley::Engine &engine) {
	ashley::EntitySystem::addedToEngine(engine);
	this->engine = &engine;
}

void stinkingRich::HUDRenderSystem::removedFromEngine(ashley::Engine &engine) {
	ashley::EntitySystem::removedFromEngine(engine);
	this->engine = nullptr;
}

