/*
 * RenderSystem.cpp
 *
 * Created on: 3 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <iostream>
#include <typeinfo>

#include "Ashley/AshleyCore.hpp"

#include "components/Renderable.hpp"
#include "components/Position.hpp"
#include "components/Player.hpp"
#include "components/House.hpp"
#include "systems/PieceRenderSystem.hpp"

stinkingRich::PieceRenderSystem::PieceRenderSystem(SDL_Renderer *renderer, int priority) :
		ashley::IteratingSystem(
				ashley::Family::getFor(ashley::ComponentType::getBitsFor<Renderable, Position>(),
						ashley::ComponentType::getBitsFor<Player, House>(), ashley::BitsType()),
				priority), renderer(renderer) {
}

void stinkingRich::PieceRenderSystem::processEntity(std::shared_ptr<ashley::Entity> &ptr,
		float deltaTime) {
	const auto &p = ashley::ComponentMapper<Position>::getMapper().get(ptr);
	const auto &renderable = ashley::ComponentMapper<Renderable>::getMapper().get(ptr);

	const SDL_Rect rect = { p->position.x, p->position.y, renderable->w, renderable->h };

	SDL_RenderCopy(renderer, renderable->texture, nullptr, &rect);
}
