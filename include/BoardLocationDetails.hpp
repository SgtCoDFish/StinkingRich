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

struct LandingCost {
	int32_t unimproved = 0;
	int32_t oneImprovement = 0;
	int32_t twoImprovements = 0;
	int32_t threeImprovements = 0;
	int32_t fourImprovements = 0;
	int32_t fiveImprovements = 0;

	LandingCost(int32_t &&unimproved, int32_t &&one, int32_t &&two, int32_t &&three, int32_t &&four,
			int32_t &&five) :
			unimproved(std::move(unimproved)), oneImprovement(std::move(one)), twoImprovements(
					std::move(two)), threeImprovements(std::move(three)), fourImprovements(
					std::move(four)), fiveImprovements(std::move(five)) {
	}

	inline MoneyType operator[](unsigned int index) const {
		if (index == 0) {
			return MoneyType(unimproved, 0);
		} else if (index == 1) {
			return MoneyType(oneImprovement, 0);
		} else if (index == 2) {
			return MoneyType(twoImprovements, 0);
		} else if (index == 3) {
			return MoneyType(threeImprovements, 0);
		} else if (index == 4) {
			return MoneyType(fourImprovements, 0);
		} else if (index == 5) {
			return MoneyType(fiveImprovements, 0);
		} else {
			return MoneyType(0, 0);
		}
	}
}
;

class BoardLocationDetails {
public:
	std::string name;
	LocationType type;

	PropertyGroup group;
	MoneyType value;

	LandingCost landingCost;

	BoardLocationDetails(std::string &&name, LocationType &&type, PropertyGroup &&group,
			MoneyType &&value, LandingCost *cost);
	~BoardLocationDetails() = default;

	static SDL_Color getPropertyGroupColor(PropertyGroup group);
	static std::vector<BoardLocationDetails> getAllLocationDetails();

	/**
	 * <p>Creates an ashley::Entity for each possible board position, using <em>font</em> to render where text is needed.</p>
	 * @param font the font to render with.
	 * @return an std::vector of all the entities for the board if successful, or an empty std::vector if the function failed.
	 */
	static std::vector<std::shared_ptr<ashley::Entity>> getAllBoardEntities(SDL_Renderer *renderer);

	static std::vector<LandingCost> getLandingCostsFor(PropertyGroup group);
};

}

#endif /* BOARDLOCATION_HPP_ */
