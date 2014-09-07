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

stinkingRich::PieceRenderSystem::PieceRenderSystem(SDL_Surface *surface, int priority) :
		ashley::IteratingSystem(
				ashley::Family::getFor(ashley::ComponentType::getBitsFor<Renderable, Position>(),
						ashley::ComponentType::getBitsFor<Player, House>(),
						ashley::BitsType()), priority), surface(surface) {
}

void stinkingRich::PieceRenderSystem::processEntity(std::shared_ptr<ashley::Entity> &ptr,
		float deltaTime) {
	auto position = ashley::ComponentMapper<Position>::getMapper().get(ptr);
	auto &color = ashley::ComponentMapper<Player>::getMapper().getRaw(ptr)->color;

	ashley::ComponentMapper<Renderable>::getMapper().get(ptr)->render(position, color, deltaTime);
}
