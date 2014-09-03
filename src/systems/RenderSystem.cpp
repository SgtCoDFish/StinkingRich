/*
 * RenderSystem.cpp
 *
 * Created on: 3 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <iostream>
#include <typeinfo>

#include "Ashley/AshleyCore.hpp"

#include "systems/RenderSystem.hpp"
#include "components/AllComponents.hpp"

stinkingRich::RenderSystem::RenderSystem(int priority) :
		ashley::IteratingSystem(
				ashley::Family::getFor( { typeid(Position), typeid(Renderable) }), priority) {

}

void stinkingRich::RenderSystem::processEntity(std::shared_ptr<ashley::Entity> &ptr,
		float deltaTime) {
	ashley::ComponentMapper<Renderable>::getFor().get(ptr)->render(
			ashley::ComponentMapper<Position>::getFor().get(ptr).get(), deltaTime);
}
