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

#include "SDL2/SDL.h"

namespace stinkingRich {
/**
 * <p>Indicates that an entity can be drawn to the screen.</p>
 *
 * <p>Note that the component may own its texture and free it upon destruction.</p>
 */
class Renderable : public ashley::Component {
private:
	static uint64_t nextIndex;
	uint64_t index;
public:
	 int32_t w;
	 int32_t h;

	 SDL_Texture *texture;

	 Renderable(SDL_Texture *tex);
	 ~Renderable();

	 Renderable(Renderable &other) = default;
	 Renderable(const Renderable &other) = default;
	 Renderable &operator=(Renderable &other) = default;
	 Renderable &operator=(const Renderable &other) = default;

	 Renderable(Renderable &&other) = default;
	 Renderable &operator=(Renderable &&other) = default;


	 /**
	  * Creates a new renderable which is just a rectangle with dimensions width * height coloured entirely in color.
	  * @return rvalue reference to new renderable.
	  */
	 static SDL_Texture *getTextureFromColor(SDL_Renderer *renderer, SDL_Color color, int32_t width, int32_t height);
};

}

#endif /* RENDERABLE_HPP_ */
