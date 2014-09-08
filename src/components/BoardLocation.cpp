/*
 * BoardLocation.cpp
 *
 * Created on: 8 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <cstdint>

#include "glm/glm.hpp"

#include "StinkingRichConstants.hpp"
#include "components/BoardLocation.hpp"

glm::ivec2 stinkingRich::BoardLocation::getWindowPosition(int32_t xOffset, int32_t yOffset,
		int32_t width, int32_t height) const {
	const int32_t x = boardX * width;
	const int32_t y = stinkingRich::constants::boardHeight - (1 + boardY) * height;

	return glm::ivec2(x + xOffset, y + yOffset);
}
