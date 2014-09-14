/*
 * BoardLocation.hpp
 *
 * Created on: 5 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef BOARDLOCATIONDETAILS_HPP_
#define BOARDLOCATIONDETAILS_HPP_

#include <cstdint>

#include <memory>

#include "SDL2/SDL.h"

#include "Ashley/core/Entity.hpp"

#include "util/MoneyType.hpp"

namespace stinkingRich {

enum class LocationType {
	GO,
	PROPERTY,
	COMMUNITY_CHEST,
	CHANCE,
	JUST_VISITING,
	JAIL,
	FREE_PARKING,
	GO_TO_JAIL,
	SUPER_TAX,
	INCOME_TAX
};

enum class PropertyGroup {
	BROWN, LIGHT_BLUE, MAGENTA, ORANGE, RED, YELLOW, GREEN, DARK_BLUE, STATION, UTILITY, NONE
};

class BoardLocationDetails {
public:
	std::string name;
	LocationType type;

	PropertyGroup group;
	MoneyType value;

	BoardLocationDetails(std::string &&name, LocationType &&type, PropertyGroup &&group,
			MoneyType &&value);
	~BoardLocationDetails() = default;

	static SDL_Color getPropertyGroupColor(PropertyGroup group);
	static std::vector<BoardLocationDetails> getAllLocationDetails();

	/**
	 * <p>Creates an ashley::Entity for each possible board position, using <em>font</em> to render where text is needed.</p>
	 * @param font the font to render with.
	 * @return an std::vector of all the entities for the board if successful, or an empty std::vector if the function failed.
	 */
	static std::vector<std::shared_ptr<ashley::Entity>> getAllBoardEntities(SDL_Renderer *renderer);
};

}

#endif /* BOARDLOCATION_HPP_ */
