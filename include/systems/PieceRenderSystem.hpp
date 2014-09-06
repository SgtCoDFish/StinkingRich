/*
 * RenderSystem.hpp
 *
 * Created on: 3 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef PIECERENDERSYSTEM_HPP_
#define PIECERENDERSYSTEM_HPP_

#include "Ashley/systems/IteratingSystem.hpp"

namespace stinkingRich {

class PieceRenderSystem : public ashley::IteratingSystem {
public:
	PieceRenderSystem(int priority);

	void processEntity(std::shared_ptr<ashley::Entity> &ptr, float deltaTime) override;
};

}


#endif /* RENDERSYSTEM_HPP_ */
