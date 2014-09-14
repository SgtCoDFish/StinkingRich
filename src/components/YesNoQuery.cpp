/*
 * YesNoQuery.cpp
 *
 * Created on: 10 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <memory>
#include <string>

#include "SDL2/SDL.h"

#include "Ashley/core/Entity.hpp"

#include "components/YesNoQuery.hpp"

std::shared_ptr<ashley::Entity> stinkingRich::YesNoQuery::makeYesNoQuery(std::string queryText) {
	auto e = std::make_shared<ashley::Entity>();

	e->add<stinkingRich::YesNoQuery>(queryText);

	return e;
}

