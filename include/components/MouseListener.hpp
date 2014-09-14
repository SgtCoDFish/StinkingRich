/*
 * MouseListener.hpp
 *
 * Created on: 14 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef MOUSELISTENER_HPP_
#define MOUSELISTENER_HPP_

#include "Ashley/core/Component.hpp"
#include "SDL2/SDL_rect.h"

namespace stinkingRich {

enum class MouseMessage {
	YES, NO, NONE
};

class MouseListener : public ashley::Component {
public:
	MouseListener(SDL_Rect rect, MouseMessage message = MouseMessage::NONE) : message(message), rect(rect) {}

	MouseMessage message;
	SDL_Rect rect;
};

}

#endif /* MOUSELISTENER_HPP_ */
