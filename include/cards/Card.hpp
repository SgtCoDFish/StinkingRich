/*
 * Card.hpp
 *
 * Created on: 9 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef CARD_HPP_
#define CARD_HPP_

#include <string>
#include <functional>
#include <queue>

#include "util/MoneyType.hpp"

namespace stinkingRich {

enum class CardType {
	CHANCE, COMMUNITY_CHEST,
};

class Card {
private:
	static void changeMoney(MoneyType money);
	static void doBirthday(MoneyType money);
	static void repairs(MoneyType houseCost, MoneyType hotelCost);
	static void moveToMayfair();
	static void moveToTrafalgarSquare();
	static void moveToPallMall();
	static void moveToMaryleboneStation();
	static void moveToGo();
	static void moveBackToOldKentRoad();
	static void moveBackThreeSpaces();
	static void getOutOfJailFree();
	static void jailPlayer();

public:
	CardType type;
	std::string text;

	using DoEffectType = std::function<void(void)>;
	DoEffectType doEffect;

	Card(CardType type, std::string text, DoEffectType doEffect) :
			type(type), text(text), doEffect(doEffect) {
	}

	static std::vector<Card> getAllChanceCards();
	static std::vector<Card> getAllCommunityChestCards();
};

class Deck {
private:
	CardType type;
	std::queue<Card> cards;

public:
	Deck(CardType type);

	/**
	 * <p>Also moves the top card to the bottom of the deck</p>
	 * @return the card on top of the deck.
	 */
	Card getTopCard();

	std::queue<Card> getCards();

	static void addGetOutOfJailFree(Deck &deck);

};

}

#endif /* CARD_HPP_ */
