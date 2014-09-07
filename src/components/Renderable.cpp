/*
 * Renderable.cpp
 *
 * Created on: 7 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include "components/Renderable.hpp"

stinkingRich::Renderable::Renderable(SDL_Texture *tex) : texture(tex) {
	int w = 0, h = 0;

	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	this->w = w;
	this->h = h;
}

stinkingRich::Renderable::~Renderable() {
	if(texture != nullptr) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}
