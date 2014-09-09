/*
 * MoneyType.cpp
 *
 * Created on: 3 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#include <cstdint>
#include <cmath>

#include <string>
#include <sstream>

#include "StinkingRichConstants.hpp"
#include "util/MoneyType.hpp"

using namespace stinkingRich;

stinkingRich::MoneyType::MoneyType(int64_t whole, int64_t fractional) :
		whole(whole), fractional(0) {
	addFract(fractional);
}

MoneyType stinkingRich::MoneyType::getFor(long double amount) {
	long double whole = 0.0, fractional = 0.0;

	fractional = std::modf(amount, &whole);

	fractional *= 100.0;
	fractional = std::round(fractional);

	int64_t wholeInt = static_cast<int64_t>(whole);
	int64_t fractInt = static_cast<int64_t>(fractional);

	return MoneyType(wholeInt, fractInt);
}

bool stinkingRich::MoneyType::operator==(MoneyType &other) {
	return (whole == other.whole && fractional == other.fractional);
}

bool stinkingRich::MoneyType::operator!=(MoneyType &other) {
	return whole != other.whole || fractional != other.fractional;
}

bool stinkingRich::MoneyType::operator<(MoneyType &other) {
	return whole < other.whole ? true : (fractional < other.fractional);
}

bool stinkingRich::MoneyType::operator<=(MoneyType &other) {
	return operator==(other) ? true : operator<(other);
}

bool stinkingRich::MoneyType::operator>(MoneyType &other) {
	return whole > other.whole ? true : fractional > other.fractional;
}

bool stinkingRich::MoneyType::operator>=(MoneyType &other) {
	return operator==(other) ? true : operator>(other);
}

MoneyType stinkingRich::MoneyType::operator+(MoneyType &other) {
	return MoneyType(whole + other.whole, fractional + other.fractional);
}

MoneyType &stinkingRich::MoneyType::operator +=(MoneyType &other) {
	whole += other.whole;
	addFract(other.fractional);

	return *this;
}

MoneyType stinkingRich::MoneyType::operator-(MoneyType &other) {
	return MoneyType(whole - other.whole, fractional - other.fractional);
}

MoneyType &stinkingRich::MoneyType::operator-=(MoneyType &other) {
	whole -= other.whole;
	addFract(-other.fractional);

	return *this;
}

MoneyType stinkingRich::MoneyType::operator-() {
	return MoneyType(-whole, -fractional);
}

std::string stinkingRich::MoneyType::toString() const {
	std::stringstream ss;
	ss << stinkingRich::constants::currencySymbol << whole;

	if(fractional != 0) {
		ss << stinkingRich::constants::currencySeparator << fractional;
	}

	return ss.str();
}

const char *stinkingRich::MoneyType::toCString() const {
	return toString().c_str();
}

std::ostream &stinkingRich::operator <<(std::ostream &os, const MoneyType &money) {
	// TODO: Better i18n
	os << money.toString();
	return os;
}
