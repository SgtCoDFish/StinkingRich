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

#include "systems/BoardRenderSystem.hpp"

#include "SDL2/SDL.h"

stinkingRich::BoardRenderSystem::BoardRenderSystem(SDL_Surface *surface, int64_t priority) :
		surface(surface), priority(priority), family(
				ashley::Family::getFor( { typeid(BoardLocation) })) {
}

void stinkingRich::BoardRenderSystem::processEntity(std::shared_ptr<ashley::Entity> &entity,
		float deltaTime) {
	const auto &boardLocation = ashley::ComponentMapper<BoardLocation>::getMapper().get(entity);
	const SDL_Color color = stinkingRich::BoardLocationDetails::getPropertyGroupColor(boardLocation->details.group);

	const SDL_Rect rect = {boardLocation->boardX, boardLocation->boardY, BoardLocation::w, BoardLocation::h};

	SDL_FillRect(surface, &rect, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
}

