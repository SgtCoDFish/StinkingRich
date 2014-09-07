/*
 * InitException.hpp
 *
 * Created on: 7 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef INITEXCEPTION_HPP_
#define INITEXCEPTION_HPP_

#include <string>
#include <utility>

namespace stinkingRich {

class InitException {
public:
	std::string msg;

	InitException(std::string &&msg = "nothing") : msg(std::move(msg)) {
	}
};

}



#endif /* INITEXCEPTION_HPP_ */
