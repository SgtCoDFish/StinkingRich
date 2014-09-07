/*
 * Renderable.hpp
 *
 * Created on: 3 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef RENDERABLE_HPP_
#define RENDERABLE_HPP_

#include <cstdint>
#include <memory>

#include "Ashley/core/Component.hpp"

#include <SDL2/SDL.h>

namespace stinkingRich {
/**
 * <p>Indicates that an entity can be drawn to the screen.</p>
 *
 * <p>Note that the component owns its texture frees it upon destruction.</p>
 */
class Renderable : public ashley::Component {
public:
	 int32_t w;
	 int32_t h;

	 SDL_Texture *texture;

	 Renderable(SDL_Texture *tex);
	 ~Renderable();
};

}

#endif /* RENDERABLE_HPP_ */
