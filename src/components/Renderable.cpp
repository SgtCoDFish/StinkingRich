/*
 * Renderable.cpp
 *
 * Created on: 7 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <iostream>
#include <memory>

#include "SDL2/SDL.h"

#include "components/Renderable.hpp"

uint64_t stinkingRich::Renderable::nextIndex = 0;

stinkingRich::Renderable::Renderable(SDL_Texture *tex) : index(nextIndex++), texture(tex) {
	int32_t w = 0, h = 0;

	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	this->w = w;
	this->h = h;

	std::cout << "Constructed Renderable #" << index << ".\n";
}

stinkingRich::Renderable::~Renderable() {
	if(texture != nullptr) {
		std::cout << "Freeing renderable #" << index << std::endl;
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

SDL_Texture *stinkingRich::Renderable::getTextureFromColor(SDL_Renderer *renderer, SDL_Color color, int32_t width, int32_t height) {
	SDL_Surface *surface = SDL_CreateRGBSurface(0, width, height, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	SDL_Texture *texture = nullptr;

	SDL_Rect rect = {0, 0, width, height};

	SDL_FillRect(surface, &rect, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	return texture;
}
