/*
 * main.cpp
 *
 * Created on: 2 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <cstdlib>
#include <cmath>
#include <ctime>

#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include <chrono>

#include "SDL2/SDL.h"

#include "StinkingRich.hpp"
#include "util/InitException.hpp"

using namespace stinkingRich;

int main(int argc, char **argv) {
	std::srand(std::time(nullptr));

	std::unique_ptr<StinkingRich> game = nullptr;

	try {
		game = std::make_unique<StinkingRich>();
	} catch (stinkingRich::InitException &ie) {
		std::cerr << "Caught InitException, failing.\n";
		return EXIT_FAILURE;
	}

	game->init();

	bool done = false;

	auto startTime = std::chrono::high_resolution_clock::now();
	while (!done) {
		auto timeNow = std::chrono::high_resolution_clock::now();
		float deltaTime =
				std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - startTime).count() / 1000.0f;

		startTime = timeNow;

		done = game->update(deltaTime);
	}

	return EXIT_SUCCESS;
}

