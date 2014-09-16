/*
 * RenderSystem.cpp
 *
 * Created on: 3 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <iostream>
#include <typeinfo>

#include "Ashley/AshleyCore.hpp"

#include "glm/glm.hpp"

#include "components/Renderable.hpp"
#include "components/Position.hpp"
#include "components/Player.hpp"
#include "components/House.hpp"
#include "systems/PieceRenderSystem.hpp"
#include "StinkingRich.hpp"
#include "StinkingRichConstants.hpp"

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

	const auto &playerMapper = ashley::ComponentMapper<Player>::getMapper();

	int xMod = 0;
	int yMod = 0;

	if(playerMapper.has(ptr)) {
		xMod += renderable->w * playerMapper.get(ptr)->id / 3;
		yMod += renderable->h * playerMapper.get(ptr)->id / 3;
	}

	//TODO: fix ignoring big sizes here
	auto posPtr =  p->position.lock();
	const glm::ivec2 pos = posPtr->getWindowPosition(stinkingRich::StinkingRich::leftGap,
			stinkingRich::StinkingRich::topGap, stinkingRich::constants::smallLocationWidth,
			stinkingRich::constants::smallLocationHeight);
	posPtr = nullptr;

	const SDL_Rect rect = { pos.x + xMod, pos.y + yMod, renderable->w, renderable->h };

	SDL_RenderCopy(renderer, renderable->texture, nullptr, &rect);
}
