/*
 * HUDRenderSystem.hpp
 *
 * Created on: 16 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef HUDRENDERSYSTEM_HPP_
#define HUDRENDERSYSTEM_HPP_

#include "SDL2/SDL.h"

#include "Ashley/core/Engine.hpp"
#include "Ashley/core/Entity.hpp"
#include "Ashley/core/EntitySystem.hpp"

namespace stinkingRich {

class HUDRenderSystem : public ashley::EntitySystem {
private:
	ashley::Engine *engine = nullptr;
	SDL_Renderer *renderer = nullptr;

public:
	HUDRenderSystem(SDL_Renderer *renderer, int priority) : EntitySystem(priority), renderer(renderer) {}

	void addedToEngine(ashley::Engine &engine) override;
	void removedFromEngine(ashley::Engine &engine) override;

	void update(float deltaTime) override;
};

}



#endif /* HUDRENDERSYSTEM_HPP_ */
