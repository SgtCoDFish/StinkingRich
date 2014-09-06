/*
 * BoardLocation.hpp
 *
 * Created on: 5 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef BOARDLOCATIONDETAILS_HPP_
#define BOARDLOCATIONDETAILS_HPP_

#include "SDL2/SDL.h"

#include "util/MoneyType.hpp"

namespace stinkingRich {

enum class LocationType {
	GO,
	PROPERTY,
	STATION,
	UTILITY,
	COMMUNITY_CHEST,
	CHANCE,
	JUST_VISITING,
	JAIL,
	FREE_PARKING,
	GO_TO_JAIL,
	TAX,
};

enum class PropertyGroup {
	BROWN, LIGHT_BLUE, MAGENTA, ORANGE, RED, YELLOW, GREEN, DARK_BLUE, NONE
};

class BoardLocationDetails {
public:
	std::string name;
	LocationType type;

	PropertyGroup group;
	MoneyType value;

	BoardLocationDetails(std::string &&name, LocationType &&type, PropertyGroup &&group, MoneyType &&value);

	static SDL_Color getPropertyGroupColor(PropertyGroup group);
	static std::vector<BoardLocationDetails> getAllLocations();
};

}

#endif /* BOARDLOCATION_HPP_ */
