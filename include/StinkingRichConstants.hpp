/*
 * StinkingRichConstants.hpp
 *
 * Created on: 3 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef STINKINGRICHCONSTANTS_HPP_
#define STINKINGRICHCONSTANTS_HPP_

#include <cstdint>

#include <string>

#include "util/MoneyType.hpp"

namespace stinkingRich {
using Money = MoneyType;

namespace constants {

const Money startingMoney = MoneyType(1500, 0);
const std::string currencySymbol = "£";

constexpr int32_t smallLocationWidth = 90;
constexpr int32_t smallLocationHeight = 65;

constexpr int32_t bigLocationWidth = 90;
constexpr int32_t bigLocationHeight = 65;

constexpr int32_t boardWidth = bigLocationWidth * 2 + smallLocationWidth * 9;
constexpr int32_t boardHeight = bigLocationHeight * 2 + smallLocationHeight * 9;

}

}


#endif /* STINKINGRICHCONSTANTS_HPP_ */
