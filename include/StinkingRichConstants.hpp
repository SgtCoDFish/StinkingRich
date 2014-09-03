/*
 * StinkingRichConstants.hpp
 *
 * Created on: 3 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef STINKINGRICHCONSTANTS_HPP_
#define STINKINGRICHCONSTANTS_HPP_

#include <string>

#include "util/MoneyType.hpp"

namespace stinkingRich {
using Money = MoneyType;

namespace constants {
const Money startingMoney = MoneyType(1500, 0);
const std::string currencySymbol = "£";
}

}


#endif /* STINKINGRICHCONSTANTS_HPP_ */
