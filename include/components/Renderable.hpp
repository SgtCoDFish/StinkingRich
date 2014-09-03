/*
 * Renderable.hpp
 *
 * Created on: 3 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef RENDERABLE_HPP_
#define RENDERABLE_HPP_

#include <functional>


namespace stinkingRich {
class Position;

class Renderable : public ashley::Component {
public:
	std::function<void(Position,float)> render;

	Renderable(decltype(render) renderFunction) : render(renderFunction) {}
};

}

#endif /* RENDERABLE_HPP_ */
