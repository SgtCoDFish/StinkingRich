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
#include "util/InitException.hpp"

using namespace stinkingRich;

int main(int argc, char **argv) {


	std::unique_ptr<StinkingRich> game = nullptr;

	try {
		game = std::make_unique<StinkingRich>();
	} catch(stinkingRich::InitException &ie) {
		std::cerr << "Caught InitException, failing.\n";
		return EXIT_FAILURE;
	}

	game->init();

	bool done = false;

	auto startTime = std::chrono::system_clock::now();
	while (!done) {
		auto timeNow = std::chrono::system_clock::now();
		auto deltaTime =
				std::chrono::duration_cast<std::chrono::seconds>(timeNow - startTime).count();
		startTime = timeNow;

		done = game->update(deltaTime);
	}

	return EXIT_SUCCESS;
}

