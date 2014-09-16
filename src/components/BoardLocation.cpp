/*
 * BoardLocation.cpp
 *
 * Created on: 8 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <cstdint>

#include <iostream>

#include "glm/glm.hpp"

#include "components/BoardLocation.hpp"
#include "StinkingRich.hpp"
#include "StinkingRichConstants.hpp"

glm::ivec2 stinkingRich::BoardLocation::getWindowPosition(int32_t xOffset, int32_t yOffset,
		int32_t width, int32_t height) const {
	const int32_t x = boardX * width;
	const int32_t y = stinkingRich::constants::boardHeight - (1 + boardY) * height;

	return glm::ivec2(x + xOffset, y + yOffset);
}

stinkingRich::MoneyType stinkingRich::BoardLocation::getLandingCost() const {
	auto i = details.landingCost[improvements];

	if(improvements == 0) {
		if(stinkingRich::StinkingRich::isAllInGroupOwned(details.group)) {
			std::cout << "All in group owned; was " << i;
			i *= 2;
			std::cout << ", now " << i << ".\n";
			std::cout.flush();
		}
	}

	return i;
}
