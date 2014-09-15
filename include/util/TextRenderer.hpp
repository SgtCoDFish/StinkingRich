/*
 * TextRenderer.hpp
 *
 * Created on: 14 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef TEXTRENDERER_HPP_
#define TEXTRENDERER_HPP_

#include <string>

#include "SDL2/SDL_ttf.h"

struct SDL_Surface;

namespace stinkingRich {

class TextRenderer {
private:
	TTF_Font *font = nullptr;
	SDL_Color color;

public:
	TextRenderer(std::string fontLocation, int ptSize);
	~TextRenderer();

	SDL_Surface *render(std::string text, int32_t wrapWidth);

	void renderToSurface(SDL_Surface *target, int32_t x, int32_t y, std::string text,
			int32_t wrapWidth);

	SDL_Texture *renderToTexture(SDL_Renderer *renderer, int32_t x, int32_t y, int32_t w, int32_t h,
			std::string text, int32_t wrapWidth);

	TTF_Font *getFont() const;

	inline void setColor(SDL_Color color) {
		this->color = color;
	}
};

}

#endif /* TEXTRENDERER_HPP_ */
