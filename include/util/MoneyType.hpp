/*
 * MoneyType.hpp
 *
 * Created on: 3 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef MONEYTYPE_HPP_
#define MONEYTYPE_HPP_

#include <cstdint>
#include <iostream>

#include <string>

namespace stinkingRich {

/**
 * <p>Represents a fixed-point decimal amount of money.</p>
 * <p>E.g. 2.5 + 0.6 = 3.1</p>
 */
class MoneyType {
private:
	int64_t whole;
	int64_t fractional;

	inline void addFract(int64_t fract) {
		fractional += fract;

		if (fractional >= 100) {
			whole++;
			fractional -= 100;
		} else if (fractional < 0) {
			whole--;
			fractional = 100 + fractional;
		}
	}

public:
	/**
	 * <p>Returns a {@link MoneyType} for the given double amount.<br />
	 * Note that some precision may be lost because of floating point.</p>
	 * <p>Using the integer versions is reccommended.</p>
	 * @param amount the amount to convert into a {@link MoneyType}.
	 * @return a {@link MoneyType} instance corresponding to the given amount.
	 */
	static MoneyType getFor(long double amount);

	MoneyType(int64_t whole, int64_t fractional);

	bool operator==(MoneyType &other);
	bool operator!=(MoneyType &other);

	bool operator<(MoneyType &other);
	bool operator<=(MoneyType &other);
	bool operator>(MoneyType &other);
	bool operator>=(MoneyType &other);

	MoneyType operator+(MoneyType &other);
	MoneyType &operator+=(MoneyType &other);

	MoneyType operator-(MoneyType &other);
	MoneyType &operator-=(MoneyType &other);

	MoneyType &operator*=(int64_t other);

	MoneyType operator-();

	std::string toString() const;
	const char *toCString() const;

	friend std::ostream &operator<<(std::ostream &os, const MoneyType &money);
};

std::ostream &operator<<(std::ostream &os, const MoneyType &money);
bool operator==(MoneyType &one, MoneyType other);
bool operator!=(MoneyType &one, MoneyType other);

}

#endif /* MONEYTYPE_HPP_ */
