/*
 * YesNoQuery.hpp
 *
 * Created on: 10 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef YESNOQUERY_HPP_
#define YESNOQUERY_HPP_

#include <memory>
#include <string>

#include "Ashley/core/Component.hpp"

namespace ashley {
class Entity;
}

namespace stinkingRich {

class YesNoQuery : public ashley::Component {
public:
	std::string question;

	YesNoQuery(std::string question) :
			question(question) {
	}

	static std::shared_ptr<ashley::Entity> makeYesNoQuery(std::string queryText);
};

}

#endif /* YESNOQUERY_HPP_ */
