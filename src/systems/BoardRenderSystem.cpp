/*
 * BoardRenderSystem.cpp
 *
 * Created on: 5 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <typeinfo>
#include <memory>

#include "Ashley/core/Entity.hpp"
#include "Ashley/core/Family.hpp"
#include "Ashley/core/ComponentMapper.hpp"
#include "Ashley/systems/IteratingSystem.hpp"

#include "BoardLocationDetails.hpp"
#include "components/BoardLocation.hpp"
#include "systems/BoardRenderSystem.hpp"

#include "SDL2/SDL.h"

stinkingRich::BoardRenderSystem::BoardRenderSystem(SDL_Surface *surface, int64_t priority) :
		ashley::IteratingSystem(ashley::Family::getFor( { typeid(stinkingRich::BoardLocation) }),
				priority), surface(surface) {
}

void stinkingRich::BoardRenderSystem::processEntity(std::shared_ptr<ashley::Entity> &entity,
		float deltaTime) {
	const auto &boardLocation = ashley::ComponentMapper<BoardLocation>::getMapper().get(entity);
	const SDL_Color color = stinkingRich::BoardLocationDetails::getPropertyGroupColor(
			boardLocation->details.group);

	const int totalBoardWidth = stinkingRich::BoardLocation::boardW;
	const int totalBoardHeight = stinkingRich::BoardLocation::boardH;

	// (surface->w - totalBoardWidth) / 2 == the gap either side of the board
	const int boardBottomRightX = surface->w - totalBoardWidth
			- ((surface->w - totalBoardWidth) / 2);

	const int boardBottomRightY = (surface->h - totalBoardHeight) / 2 + totalBoardHeight;

	const SDL_Rect rect = { boardLocation->boardX * stinkingRich::BoardLocation::w
			+ boardBottomRightX, boardBottomRightY
			- (boardLocation->boardY + 1) * stinkingRich::BoardLocation::h, BoardLocation::w,
			BoardLocation::h };

	SDL_FillRect(surface, &rect, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
}

