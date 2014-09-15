/*
 * UIRenderSystem.hpp
 *
 * Created on: 14 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef UIRENDERSYSTEM_HPP_
#define UIRENDERSYSTEM_HPP_

#include <memory>
#include <vector>

#include "Ashley/systems/IteratingSystem.hpp"
#include "SDL2/SDL_rect.h"

struct SDL_Renderer;
namespace ashley {
class Entity;
}

namespace stinkingRich {

class UIRenderSystem : public ashley::IteratingSystem {
private:
	SDL_Renderer *renderer = nullptr;

	ashley::Engine *engine = nullptr;

	std::vector<std::shared_ptr<ashley::Entity>> addedUIEntities;
	std::vector<SDL_Rect> boxes;

	SDL_Texture *queryTexture = nullptr;
	SDL_Texture *yesTexture = nullptr;
	SDL_Texture *noTexture = nullptr;
public:
	UIRenderSystem(int priority);
	UIRenderSystem(SDL_Renderer *renderer, int priority);
	virtual ~UIRenderSystem();

	void addedToEngine(ashley::Engine &engine) override;
	void removedFromEngine(ashley::Engine &engine) override;

	void setRenderer(SDL_Renderer *renderer);

	void processEntity(std::shared_ptr<ashley::Entity> &entity, float deltaTime) override;

	void addUIEntity(std::shared_ptr<ashley::Entity> &e);
	void removeUIEntity();
};

}



#endif /* UIRENDERSYSTEM_HPP_ */
