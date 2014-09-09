/*
 * BoardLocations.cpp
 *
 * Created on: 5 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <cstdint>

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <sstream>
#include <memory>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "BoardLocationDetails.hpp"
#include "util/MoneyType.hpp"

#include "StinkingRichConstants.hpp"
#include "components/BoardLocation.hpp"
#include "components/Renderable.hpp"
#include "components/Position.hpp"
#include "components/GoLocation.hpp"
#include "components/JailLocation.hpp"

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

	case PropertyGroup::UTILITY:
	case PropertyGroup::STATION:
		return {0xFF, 0xFF, 0xFF, 0xFF};

	default:
		return {0xFF, 0xFF, 0xFF, 0xFF};
	}
}

std::vector<stinkingRich::BoardLocationDetails> stinkingRich::BoardLocationDetails::getAllLocationDetails() {
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

	locations.emplace_back("Income Tax", LocationType::INCOME_TAX, PropertyGroup::NONE,
			MoneyType(-200, 0));

	locations.emplace_back("King's Cross\nStation", LocationType::PROPERTY, PropertyGroup::STATION,
			MoneyType(200, 0));

	locations.emplace_back("The Angel,\nIslington", LocationType::PROPERTY,
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

	locations.emplace_back("Electric Company", LocationType::PROPERTY, PropertyGroup::UTILITY,
			MoneyType(150, 0));

	locations.emplace_back("Whitehall", LocationType::PROPERTY, PropertyGroup::MAGENTA,
			MoneyType(140, 0));

	locations.emplace_back("Northumberland\nAvenue", LocationType::PROPERTY, PropertyGroup::MAGENTA,
			MoneyType(160, 0));

	locations.emplace_back("Marylebone\nStation", LocationType::PROPERTY, PropertyGroup::STATION,
			MoneyType(200, 0));

	locations.emplace_back("Bow Street", LocationType::PROPERTY, PropertyGroup::ORANGE,
			MoneyType(180, 0));

	locations.emplace_back(std::string(communityChestString), LocationType::COMMUNITY_CHEST,
			PropertyGroup::NONE, MoneyType(0, 0));

	locations.emplace_back("Marlborough Street", LocationType::PROPERTY, PropertyGroup::ORANGE,
			MoneyType(180, 0));

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

	locations.emplace_back("Fenchurch Street\nStation", LocationType::PROPERTY, PropertyGroup::STATION,
			MoneyType(200, 0));

	locations.emplace_back("Leicester Square", LocationType::PROPERTY, PropertyGroup::YELLOW,
			MoneyType(260, 0));

	locations.emplace_back("Coventry Street", LocationType::PROPERTY, PropertyGroup::YELLOW,
			MoneyType(260, 0));

	locations.emplace_back("Water Works", LocationType::PROPERTY, PropertyGroup::UTILITY,
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

	locations.emplace_back("Liverpool Street\nStation", LocationType::PROPERTY, PropertyGroup::STATION,
			MoneyType(200, 0));

	locations.emplace_back(std::string(chanceString), LocationType::CHANCE, PropertyGroup::NONE,
			MoneyType(0, 0));

	locations.emplace_back("Park Lane", LocationType::PROPERTY, PropertyGroup::DARK_BLUE,
			MoneyType(350, 0));

	locations.emplace_back("Super Tax", LocationType::SUPER_TAX, PropertyGroup::NONE,
			MoneyType(-100, 0));

	locations.emplace_back("Mayfair", LocationType::PROPERTY, PropertyGroup::DARK_BLUE,
			MoneyType(400, 0));

	std::cout << "Location count: " << locations.size() << std::endl;

	return locations;
}

std::vector<std::shared_ptr<ashley::Entity>> stinkingRich::BoardLocationDetails::getAllBoardEntities(
		SDL_Renderer *renderer, TTF_Font *font) {
	auto locs = getAllLocationDetails();

	if (locs.size() == 0) {
		std::cerr << "getAllLocationDetails() failed.\n";
		return std::vector<std::shared_ptr<ashley::Entity>>();
	}

	std::vector<std::shared_ptr<ashley::Entity>> entities;

	int8_t posX = 10;
	int8_t posY = 0;

	int8_t xDiff = 0;
	int8_t yDiff = 0;

	int8_t xDir = -1;
	int8_t yDir = 0;

	// by value because we want to copy the details for each
	// into a new entity.
	for (const auto location : locs) {
		auto e = std::make_shared<ashley::Entity>();

		int32_t locationWidth = -1;
		int32_t locationHeight = -1;

		e->add<stinkingRich::BoardLocation>(stinkingRich::BoardLocationDetails(location), posX,
				posY);

		posX += xDir;
		posY += yDir;

		xDiff += xDir;
		yDiff += yDir;

		if (xDiff == 10) {
			xDiff = 0;
			xDir = 0;
			yDir = -1;

			locationWidth = stinkingRich::constants::bigLocationWidth;
			locationHeight = stinkingRich::constants::bigLocationHeight;
		} else if (yDiff == 10) {
			yDiff = 0;
			xDir = 1;
			yDir = 0;

			locationWidth = stinkingRich::constants::bigLocationWidth;
			locationHeight = stinkingRich::constants::bigLocationHeight;
		} else if (xDiff == -10) {
			xDiff = 0;
			xDir = 0;
			yDir = 1;

			locationWidth = stinkingRich::constants::bigLocationWidth;
			locationHeight = stinkingRich::constants::bigLocationHeight;
		} else {
			locationWidth = stinkingRich::constants::smallLocationWidth;
			locationHeight = stinkingRich::constants::smallLocationHeight;
		}

		SDL_Surface *surfaceTemp = SDL_CreateRGBSurface(0, locationWidth, locationHeight, 32,
				0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
		SDL_FillRect(surfaceTemp, nullptr,
				SDL_MapRGBA(surfaceTemp->format, 0xFF, 0xFF, 0xFF, 0xFF));

		auto renderText =
				[&](const char *text) {SDL_Surface *textSurface = TTF_RenderUTF8_Blended_Wrapped(font, text, {0x00, 0x00, 0x00, 0xFF}, surfaceTemp->w);
					SDL_BlitSurface(textSurface, nullptr, surfaceTemp, nullptr);};

		if (surfaceTemp == nullptr) {
			std::cerr << "Could not create surface while loading all entities:\n" << SDL_GetError()
					<< std::endl;
			return std::vector<std::shared_ptr<ashley::Entity>>();
		}

		SDL_Texture *texture = nullptr;

		switch (location.type) {
		case LocationType::PROPERTY: {
			auto color = getPropertyGroupColor(location.group);

			if(location.group == PropertyGroup::UTILITY) {
				if (location.name.find("Water") == std::string::npos) {
					color = {0x00, 0x66, 0x99, 0xFF};
				} else {
					color = {0xDD, 0xDD, 0x00, 0xFF};
				}
			}

			SDL_FillRect(surfaceTemp, nullptr,
					SDL_MapRGBA(surfaceTemp->format, color.r, color.g, color.b, color.a));

			//TODO: Non i18n ready
			std::stringstream ss;
			ss << location.name << "\n" << location.value;
			renderText(ss.str().c_str());
			break;
		}

		case LocationType::CHANCE: {
			renderText("Chance!");
			break;
		}

		case LocationType::COMMUNITY_CHEST: {
			renderText("Community Chest");
			break;
		}

		case LocationType::GO: {
			// TODO: Non-i18n ready hack
			std::stringstream ss;
			ss << "GO!\nCollect " << stinkingRich::constants::currencySymbol << "200!";

			renderText(ss.str().c_str());
			e->add<GoLocation>();
			break;
		}

		case LocationType::GO_TO_JAIL: {
			renderText("Go to jail.");
			break;
		}


		case LocationType::FREE_PARKING: {
			renderText("Free\nParking");
			break;
		}

		case LocationType::SUPER_TAX: {
			// TODO: Non-i18n ready hack
			std::stringstream ss;
			ss << "Super Tax\nPay " << stinkingRich::constants::currencySymbol << "100.";
			renderText(ss.str().c_str());
			break;
		}

		case LocationType::INCOME_TAX: {
			// TODO: Non-i18n ready hack
			std::stringstream ss;
			ss << "Income Tax\nPay " << stinkingRich::constants::currencySymbol << "200.";
			renderText(ss.str().c_str());
			break;
		}

		case LocationType::JUST_VISITING: {
			renderText("Just Visiting!");
			e->add<JailLocation>();
			break;
		}

		default: {
			std::cout << "Unhandled case in getAllBoardEntities()" << std::endl;
			break;
		}
		};

		texture = SDL_CreateTextureFromSurface(renderer, surfaceTemp);

		e->add<Renderable>(texture);

		entities.push_back(e);

		SDL_FreeSurface(surfaceTemp);
	}

	for(uint16_t i = 0; i < entities.size(); i++) {
		uint16_t next = i + 1;
		int16_t prev = i - 1;

		if(next == entities.size()) {
			next = 0;
		} else if(prev < 0) {
			prev = entities.size() - 1;
		}

		entities[i]->getComponent<BoardLocation>()->nextLocation = std::weak_ptr<ashley::Entity>(entities[next]);
		entities[i]->getComponent<BoardLocation>()->prevLocation = std::weak_ptr<ashley::Entity>(entities[prev]);
	}

	return entities;
}

