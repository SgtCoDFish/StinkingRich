/*
 * UIRenderSystem.cpp
 *
 * Created on: 14 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <string>
#include <algorithm>
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

	const SDL_Rect yesBox = { mainBox.x + gapW, optionY, optionW, 50 };
	const SDL_Rect noBox = { mainBox.x + gapW * 2 + optionW, optionY, optionW, 50 };

	boxes.push_back(yesBox);
	boxes.push_back(noBox);

	const auto textRenderer = stinkingRich::StinkingRich::getTextRenderer();

	textRenderer->setColor({0x00, 0x00, 0x00, 0xFF});

	yesTexture = textRenderer->renderToTexture(renderer, 0, 0, yesBox.w, yesBox.h, "Yes", yesBox.w);
	noTexture = textRenderer->renderToTexture(renderer, 0, 0, noBox.w, noBox.h, "No", noBox.w);

	constexpr int queryOffsetX = 10;
	constexpr int queryOffsetY = 10;
	const int queryBoxW = mainBox.w - (2 * queryOffsetX);
	const int queryBoxH = static_cast<int>(mainBox.h * 0.25);

	const SDL_Rect queryBox = { mainBox.x + queryOffsetX, mainBox.y + queryOffsetY, queryBoxW,
			queryBoxH };

	boxes.push_back(queryBox);
}

stinkingRich::UIRenderSystem::~UIRenderSystem() {
	if (addedUIEntities.size() > 0) {
		removeUIEntity();
	}

	if (queryTexture != nullptr) {
		SDL_DestroyTexture(queryTexture);
	}

	if (yesTexture != nullptr) {
		SDL_DestroyTexture(yesTexture);
	}

	if (noTexture != nullptr) {
		SDL_DestroyTexture(noTexture);
	}
}

void stinkingRich::UIRenderSystem::processEntity(std::shared_ptr<ashley::Entity> &entity,
		float deltaTime) {
	auto &text =
			ashley::ComponentMapper<stinkingRich::YesNoQuery>::getMapper().get(entity)->question;

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRects(renderer, boxes.data(), boxes.size());

	SDL_RenderCopy(renderer, yesTexture, nullptr, &boxes[1]);
	SDL_RenderCopy(renderer, noTexture, nullptr, &boxes[2]);
	SDL_RenderCopy(renderer, queryTexture, nullptr, &boxes[3]);

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderDrawRects(renderer, boxes.data(), boxes.size());

}

void stinkingRich::UIRenderSystem::addUIEntity(std::shared_ptr<ashley::Entity>& e) {
	if (engine == nullptr) {
		std::cerr << "Call to addQuery with invalid engine.\n";
		return;
	}

	if (addedUIEntities.size() > 0) {
		std::cerr << "Trying to add new ui component when one already exists.\n";
		return;
	}

	engine->addEntity(e);
	auto yes = std::make_shared<ashley::Entity>();
	auto no = std::make_shared<ashley::Entity>();

	yes->add<stinkingRich::MouseListener>(boxes[1], stinkingRich::MouseMessage::YES);
	no->add<stinkingRich::MouseListener>(boxes[2], stinkingRich::MouseMessage::NO);

	engine->addEntity(yes);
	engine->addEntity(no);

	addedUIEntities.emplace_back(std::shared_ptr<ashley::Entity>(e));
	addedUIEntities.emplace_back(std::shared_ptr<ashley::Entity>(yes));
	addedUIEntities.emplace_back(std::shared_ptr<ashley::Entity>(no));

	auto queryText = std::string(ashley::ComponentMapper<YesNoQuery>::getMapper().get(e)->question);

	queryText.erase(std::remove(queryText.begin(), queryText.end(), '\n'), queryText.end());

	const auto textRenderer = stinkingRich::StinkingRich::getTextRenderer();
	textRenderer->setColor({0x00, 0x00, 0x00, 0xFF});
	queryTexture = textRenderer->renderToTexture(renderer, 0, 0, boxes[3].w, boxes[3].h, queryText, boxes[3].w);
}

void stinkingRich::UIRenderSystem::removeUIEntity() {
	if (addedUIEntities.size() == 0) {
		std::cerr << "Trying to remove UI entity when none exists.\n";
		return;
	}

	for (const auto &e : addedUIEntities) {
		engine->removeEntity(e);
	}

	addedUIEntities.clear();

	if(queryTexture != nullptr) {
		SDL_DestroyTexture(queryTexture);
	}
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
