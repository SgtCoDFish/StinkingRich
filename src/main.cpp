/*
 * main.cpp
 *
 * Created on: 2 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <cstdlib>
#include <cmath>

#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include <chrono>

#include "SDL2/SDL.h"

#include "StinkingRich.hpp"

using namespace stinkingRich;

int main(int argc, char **argv) {
	SDL_Window *window = nullptr;
	SDL_Surface *surface = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Could not initialise SDL: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	window = SDL_CreateWindow("Stinking Rich", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			1280, 768, SDL_WINDOW_SHOWN);

	if (window == nullptr) {
		std::cerr << "Could not make window: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	surface = SDL_GetWindowSurface(window);

	bool done = false;
	SDL_Event event;

	StinkingRich game(window, surface);
	game.init();

	while (!done) {
		auto startTime = std::chrono::system_clock::now();

		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				done = true;
			}
		}

		game.update(std::chrono::duration_cast<std::chrono::seconds>(
						std::chrono::system_clock::now() - startTime).count());
	}

	SDL_DestroyWindow(window);

	SDL_Quit();

	return EXIT_SUCCESS;
}

