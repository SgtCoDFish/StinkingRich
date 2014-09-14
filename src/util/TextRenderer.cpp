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

	retVal = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, wrapWidth);

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
		// but there's nothing wrong for now.
		goto finish;
	}


	SDL_BlitSurface(temp, nullptr, target, &targetRect);

	finish: SDL_FreeSurface(temp);
}

TTF_Font * stinkingRich::TextRenderer::getFont() const {
	return font;
}

