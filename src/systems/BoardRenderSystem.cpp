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

	const int32_t leftGap = (stinkingRich::StinkingRich::windowWidth
			- stinkingRich::constants::boardWidth) / 2;
	const int32_t topGap = (stinkingRich::StinkingRich::windowHeight
			- stinkingRich::constants::boardHeight) / 2;

	const int32_t xPos = leftGap + boardLocation->boardX * renderable->w;
	const int32_t yPos = stinkingRich::constants::boardHeight
			- (1 + boardLocation->boardY) * renderable->h + topGap;

	const SDL_Rect rect = { xPos, yPos, renderable->w, renderable->h };

	SDL_RenderCopy(renderer, renderable->texture, nullptr, &rect);

}

