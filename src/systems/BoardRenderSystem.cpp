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

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "StinkingRich.hpp"
#include "StinkingRichConstants.hpp"
#include "BoardLocationDetails.hpp"
#include "components/Position.hpp"
#include "components/BoardLocation.hpp"
#include "components/Renderable.hpp"
#include "systems/BoardRenderSystem.hpp"

stinkingRich::BoardRenderSystem::BoardRenderSystem(SDL_Renderer *renderer, int64_t priority) :
		ashley::IteratingSystem(ashley::Family::getFor( { typeid(stinkingRich::Renderable),
				typeid(stinkingRich::BoardLocation) }), priority), renderer(renderer) {
}

void stinkingRich::BoardRenderSystem::processEntity(std::shared_ptr<ashley::Entity> &entity,
		float deltaTime) {
	const auto &boardLocation =
			ashley::ComponentMapper<stinkingRich::BoardLocation>::getMapper().get(entity);
	const auto &renderable = ashley::ComponentMapper<stinkingRich::Renderable>::getMapper().get(
			entity);

	glm::ivec2 loc = boardLocation->getWindowPosition(stinkingRich::StinkingRich::leftGap,
			stinkingRich::StinkingRich::topGap, renderable->w, renderable->h);

	const SDL_Rect rect = { loc.x, loc.y, renderable->w, renderable->h };

	SDL_RenderCopy(renderer, renderable->texture, nullptr, &rect);
}

