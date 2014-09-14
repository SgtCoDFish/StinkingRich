/*
 * UIRenderSystem.cpp
 *
 * Created on: 14 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <bitset>

#include "SDL2/SDL.h"

#include "Ashley/AshleyCore.hpp"

#include "StinkingRich.hpp"
#include "StinkingRichConstants.hpp"
#include "components/YesNoQuery.hpp"
#include "components/MouseListener.hpp"
#include "systems/UIRenderSystem.hpp"

using namespace stinkingRich;

stinkingRich::UIRenderSystem::UIRenderSystem(int priority) :
		UIRenderSystem(nullptr, priority) {
}

stinkingRich::UIRenderSystem::UIRenderSystem(SDL_Renderer *renderer, int priority) :
		ashley::IteratingSystem(
				ashley::Family::getFor(
						ashley::BitsType(ashley::ComponentType::getBitsFor<YesNoQuery>()),
						ashley::BitsType(), ashley::BitsType()), priority), renderer(renderer) {

	const int boxW = static_cast<int>(constants::boardWidth * 0.75);
	const int boxWDiff = (constants::boardWidth - boxW) / 2;

	const int boxH = static_cast<int>(constants::boardHeight * 0.75);
	const int boxHDiff = (constants::boardHeight - boxH) / 2;

	const SDL_Rect mainBox = { StinkingRich::leftGap + boxWDiff, StinkingRich::topGap + boxHDiff,
			boxW, boxH };

	boxes.push_back(mainBox);

	constexpr int optionW = 100;
	const int optionY = static_cast<int>(mainBox.h * 0.75) + mainBox.y;
	const int gapW = (boxW - (2 * optionW)) / 3;

	boxes.push_back( { mainBox.x + gapW, optionY, optionW, 50 });
	boxes.push_back( { mainBox.x + gapW * 2 + optionW, optionY, optionW, 50 });
}

void stinkingRich::UIRenderSystem::setRenderer(SDL_Renderer *renderer) {
	this->renderer = renderer;
}

void stinkingRich::UIRenderSystem::addedToEngine(ashley::Engine &engine) {
	ashley::IteratingSystem::addedToEngine(engine);

	this->engine = &engine;
}

void stinkingRich::UIRenderSystem::removedFromEngine(ashley::Engine &engine) {
	ashley::IteratingSystem::addedToEngine(engine);

	this->engine = nullptr;
}

void stinkingRich::UIRenderSystem::processEntity(std::shared_ptr<ashley::Entity> &entity,
		float deltaTime) {
	auto &text =
			ashley::ComponentMapper<stinkingRich::YesNoQuery>::getMapper().get(entity)->question;

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRects(renderer, boxes.data(), boxes.size());

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderDrawRects(renderer, boxes.data(), boxes.size());
}

void stinkingRich::UIRenderSystem::addQuery(std::shared_ptr<ashley::Entity> e) {
	if (engine == nullptr) {
		std::cerr << "Call to addQuery with invalid engine.\n";
	} else {
		engine->addEntity(e);
		auto yes = std::make_shared<ashley::Entity>();
		auto no = std::make_shared<ashley::Entity>();

		yes->add<stinkingRich::MouseListener>(boxes[1], stinkingRich::MouseMessage::YES);
		no->add<stinkingRich::MouseListener>(boxes[2], stinkingRich::MouseMessage::NO);

		engine->addEntity(yes);
		engine->addEntity(no);
	}
}

