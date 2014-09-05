/*
 * BoardRenderSystem.hpp
 *
 * Created on: 5 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef BOARDRENDERSYSTEM_HPP_
#define BOARDRENDERSYSTEM_HPP_

#include <cstdint>
#include <memory>

#include "Ashley/core/Entity.hpp"
#include "Ashley/systems/IteratingSystem.hpp"

struct SDL_Surface;

namespace stinkingRich {

class BoardRenderSystem : public ashley::IteratingSystem {
private:
	SDL_Surface *surface;
public:
	BoardRenderSystem(SDL_Surface *surface, int64_t priority);

	void processEntity(std::shared_ptr<ashley::Entity> &entity, float deltaTime) override;
};

}



#endif /* BOARDRENDERSYSTEM_HPP_ */
