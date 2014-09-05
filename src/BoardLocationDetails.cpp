/*
 * BoardLocations.cpp
 *
 * Created on: 5 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <vector>
#include <utility>

#include "BoardLocationDetails.hpp"
#include "util/MoneyType.hpp"

#include "SDL2/SDL.h"

using namespace stinkingRich;

stinkingRich::BoardLocationDetails::BoardLocationDetails(std::string &&name, LocationType &&type,
		PropertyGroup &&group, MoneyType &&value) :
		name(std::move(name)), type(std::move(type)), group(std::move(group)), value(
				std::move(value)) {

}

SDL_Color stinkingRich::BoardLocationDetails::getPropertyGroupColor(PropertyGroup group) {
	switch (group) {
	case PropertyGroup::BROWN:
		return {0x8B, 0x45, 0x13, 0xFF};

	case PropertyGroup::LIGHT_BLUE:
		return {0x87, 0xCE, 0xEB, 0xFF};

	case PropertyGroup::MAGENTA:
		return {0xFF, 0x14, 0x93, 0xFF};

	case PropertyGroup::ORANGE:
		return {0xFF, 0xA5, 0x00, 0xFF};

	case PropertyGroup::RED:
		return {0xFF, 0x00, 0x00, 0xFF};

	case PropertyGroup::YELLOW:
		return {0xFF, 0xFF, 0x00, 0xFF};

	case PropertyGroup::GREEN:
		return {0x00, 0x80, 0x00, 0xFF};

	case PropertyGroup::DARK_BLUE:
		return {0x00, 0x00, 0xFF, 0xFF};

	default:
		return {0xFF, 0xFF, 0xFF, 0xFF};
	}
}

std::vector<stinkingRich::BoardLocationDetails> stinkingRich::BoardLocationDetails::getAllLocations() {
	std::vector<stinkingRich::BoardLocationDetails> locations;

	const std::string communityChestString = "Community Chest";
	const std::string chanceString = "Chance";

	locations.emplace_back("Go", LocationType::GO, PropertyGroup::NONE, MoneyType(200, 0));

	locations.emplace_back("Old Kent Road", LocationType::PROPERTY, PropertyGroup::BROWN,
			MoneyType(60, 0));

	locations.emplace_back(std::string(communityChestString), LocationType::COMMUNITY_CHEST,
			PropertyGroup::NONE, MoneyType(0, 0));

	locations.emplace_back("Whitechapel Road", LocationType::PROPERTY, PropertyGroup::BROWN,
			MoneyType(60, 0));

	locations.emplace_back("Income Tax", LocationType::TAX, PropertyGroup::NONE,
			MoneyType(-200, 0));

	locations.emplace_back("King's Cross Station", LocationType::STATION, PropertyGroup::NONE,
			MoneyType(200, 0));

	locations.emplace_back("The Angel, Islington", LocationType::PROPERTY,
			PropertyGroup::LIGHT_BLUE, MoneyType(100, 0));

	locations.emplace_back(std::string(chanceString), LocationType::CHANCE, PropertyGroup::NONE,
			MoneyType(0, 0));

	locations.emplace_back("Euston Road", LocationType::PROPERTY, PropertyGroup::LIGHT_BLUE,
			MoneyType(100, 0));

	locations.emplace_back("Pentonville Road", LocationType::PROPERTY, PropertyGroup::LIGHT_BLUE,
			MoneyType(120, 0));

	locations.emplace_back("Just Visiting", LocationType::JUST_VISITING, PropertyGroup::NONE,
			MoneyType(0, 0));

	locations.emplace_back("Pall Mall", LocationType::PROPERTY, PropertyGroup::MAGENTA,
			MoneyType(140, 0));

	locations.emplace_back("Electric Company", LocationType::UTILITY, PropertyGroup::NONE,
			MoneyType(150, 0));

	locations.emplace_back("Whitehall", LocationType::PROPERTY, PropertyGroup::MAGENTA,
			MoneyType(140, 0));

	locations.emplace_back("Northumberland Avenue", LocationType::PROPERTY, PropertyGroup::MAGENTA,
			MoneyType(160, 0));

	locations.emplace_back("Marylebone Station", LocationType::STATION, PropertyGroup::NONE,
			MoneyType(0, 0));

	locations.emplace_back("Bow Street", LocationType::PROPERTY, PropertyGroup::ORANGE,
			MoneyType(180, 0));

	locations.emplace_back(std::string(communityChestString), LocationType::COMMUNITY_CHEST,
			PropertyGroup::NONE, MoneyType(0, 0));

	locations.emplace_back("Vine Street", LocationType::PROPERTY, PropertyGroup::ORANGE,
			MoneyType(200, 0));

	locations.emplace_back("Free Parking", LocationType::FREE_PARKING, PropertyGroup::NONE,
			MoneyType(0, 0));

	locations.emplace_back("Strand", LocationType::PROPERTY, PropertyGroup::RED, MoneyType(220, 0));

	locations.emplace_back(std::string(chanceString), LocationType::CHANCE, PropertyGroup::NONE,
			MoneyType(0, 0));

	locations.emplace_back("Fleet Street", LocationType::PROPERTY, PropertyGroup::RED,
			MoneyType(220, 0));

	locations.emplace_back("Trafalgar Square", LocationType::PROPERTY, PropertyGroup::RED,
			MoneyType(240, 0));

	locations.emplace_back("Fenchurch Street Station", LocationType::STATION, PropertyGroup::NONE,
			MoneyType(200, 0));

	locations.emplace_back("Leicester Square", LocationType::PROPERTY, PropertyGroup::YELLOW,
			MoneyType(260, 0));

	locations.emplace_back("Coventry Street", LocationType::PROPERTY, PropertyGroup::YELLOW,
			MoneyType(260, 0));

	locations.emplace_back("Water Works", LocationType::UTILITY, PropertyGroup::NONE,
			MoneyType(150, 0));

	locations.emplace_back("Piccadilly", LocationType::PROPERTY, PropertyGroup::YELLOW,
			MoneyType(280, 0));

	locations.emplace_back("Go to Jail", LocationType::GO_TO_JAIL, PropertyGroup::NONE,
			MoneyType(0, 0));

	locations.emplace_back("Regent Street", LocationType::PROPERTY, PropertyGroup::GREEN,
			MoneyType(300, 0));

	locations.emplace_back("Oxford Street", LocationType::PROPERTY, PropertyGroup::GREEN,
			MoneyType(300, 0));

	locations.emplace_back(std::string(communityChestString), LocationType::COMMUNITY_CHEST,
			PropertyGroup::NONE, MoneyType(0, 0));

	locations.emplace_back("Bond Street", LocationType::PROPERTY, PropertyGroup::GREEN,
			MoneyType(320, 0));

	locations.emplace_back("Liverpool Street Station", LocationType::STATION, PropertyGroup::NONE,
			MoneyType(200, 0));

	locations.emplace_back(std::string(chanceString), LocationType::CHANCE, PropertyGroup::NONE,
			MoneyType(0, 0));

	locations.emplace_back("Park Lane", LocationType::PROPERTY, PropertyGroup::DARK_BLUE,
			MoneyType(350, 0));

	locations.emplace_back("Super Tax", LocationType::TAX, PropertyGroup::NONE, MoneyType(-100, 0));

	locations.emplace_back("Mayfair", LocationType::PROPERTY, PropertyGroup::DARK_BLUE,
			MoneyType(400, 0));

	return locations;
}

