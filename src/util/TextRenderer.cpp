/*
 * TextRenderer.cpp
 *
 * Created on: 14 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <cstdint>
#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "util/TextRenderer.hpp"

stinkingRich::TextRenderer::TextRenderer(std::string fontLocation, int fontSize) :
		color( { 0xFF, 0xFF, 0xFF, 0xFF }) {
	font = TTF_OpenFont(fontLocation.c_str(), fontSize);

	if (font == nullptr) {
		std::cerr << "Could not load " << fontLocation << " in size " << fontSize
				<< ". TTF_Error:\n" << TTF_GetError() << std::endl;
	}
}

stinkingRich::TextRenderer::~TextRenderer() {
	if (font != nullptr) {
		TTF_CloseFont(font);
	}
}

SDL_Surface *stinkingRich::TextRenderer::render(std::string text, int32_t wrapWidth) {
	SDL_Surface *retVal = nullptr;

	retVal = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), color, wrapWidth);

	return retVal;
}

void stinkingRich::TextRenderer::renderToSurface(SDL_Surface *target, int32_t x, int32_t y,
		std::string text, int32_t wrapWidth) {

	SDL_Surface *temp = render(text, wrapWidth);
	SDL_Rect targetRect = { x, y, temp->w, temp->h };

	if (x + temp->w > target->w || y + temp->h > target->h) {
		std::cerr << "Can not render \"" << text
				<< "\" to surface; the surface isn't large enough to contain the text.\n";

		// evil, I know; I chose this mainly because SDL is a C API and therefore the cleanup rules aren't sensible.
		// I'd prefer to write a C++ wrapper for SDL features which cleans up when the object is destroyed
		// but there's nothing wrong with this for now.

		// also I've never used goto before and I wanted to know what it felt like.
		goto finish;
	}

	SDL_BlitSurface(temp, nullptr, target, &targetRect);

	finish: SDL_FreeSurface(temp);
}

SDL_Texture *stinkingRich::TextRenderer::renderToTexture(SDL_Renderer *renderer, int32_t x, int32_t y, int32_t w, int32_t h,
		std::string text, int32_t wrapWidth) {
	SDL_Surface *temp = SDL_CreateRGBSurface(0, w, h, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	SDL_FillRect(temp, nullptr, SDL_MapRGBA(temp->format, 0xFF, 0xFF, 0xFF, 0xFF));
	renderToSurface(temp, x, y, text, wrapWidth);

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_Texture *ret = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	return ret;
}

TTF_Font * stinkingRich::TextRenderer::getFont() const {
	return font;
}

