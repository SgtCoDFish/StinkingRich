/*
 * main.cpp
 *
 * Created on: 2 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <cstdlib>

#include <iostream>
#include <memory>
#include <utility>
#include <chrono>

#include "SDL2/SDL.h"

#include "Ashley/AshleyCore.hpp"

#include "components/AllComponents.hpp"

#include "systems/AllSystems.hpp"

using namespace ashley;
using namespace stinkingRich;

SDL_Window *window = nullptr;
SDL_Surface *surface = nullptr;

Engine engine;

void update(float deltaTime) {
	SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));

	engine.update(deltaTime);

	SDL_UpdateWindowSurface (window);
}

int main(int argc, char **argv) {
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

	auto e = std::make_shared<Entity>();
	e->add<Player>();
	e->add<Position>(25.0f, 25.0f);
	e->add<Renderable>([](Position p, float delta) {
		SDL_Rect rect({static_cast<int>(p.position.x), static_cast<int>(p.position.y), 32, 32});
		SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, 0xFF, 0x00, 0xFF));
	});

	auto rs = std::make_shared<RenderSystem>(100);
	engine.addEntity(e);
	engine.addSystem(rs);

	bool done = false;
	SDL_Event event;

	std::cout << "asdasd\n";

	while (!done) {
		auto startTime = std::chrono::system_clock::now();

		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				done = true;
			}
		}

		update(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - startTime).count());
	}

	SDL_DestroyWindow(window);

	SDL_Quit();

	return EXIT_SUCCESS;
}

