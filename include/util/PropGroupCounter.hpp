/*
 * PropGroupCounter.hpp
 *
 * Created on: 16 Sep 2014
 * Author: Ashley Davis (SgtCoDFish)
 */

#ifndef PROPGROUPCOUNTER_HPP_
#define PROPGROUPCOUNTER_HPP_

#include <cstdint>

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

#include "components/Player.hpp"

namespace stinkingRich {
class PropGroupCounter {
private:
	int32_t ownedCount;

	std::vector<int> ownerIDs;
	int32_t groupLocationCount;
public:
	PropGroupCounter() : PropGroupCounter(0) {}

	PropGroupCounter(int32_t groupLocationCount) :
			ownedCount(0), groupLocationCount(groupLocationCount) {
	}

	void addOwner(std::shared_ptr<stinkingRich::Player> newOwner) {
		if (ownedCount == groupLocationCount) {
			std::cerr << "Trying to add new owner to completely owned property group.\n";
			return;
		}

		ownedCount++;
		ownerIDs.emplace_back(newOwner->id);
		std::cout << "New ownerIDs size: " << ownerIDs.size() << ".\n";
	}

	int countOwnedByPlayerID(int64_t id) const {
		return std::count(ownerIDs.begin(), ownerIDs.end(), id);
	}

	int countOwnedByPlayer(std::shared_ptr<stinkingRich::Player> player) const {
		return countOwnedByPlayerID(player->id);
	}

	bool isAllSameOwner() const {
		if (ownerIDs.size() > 0) {
			auto count = countOwnedByPlayerID(ownerIDs[0]);

			std::cout << "Counted " << count << " when size was " << ownerIDs.size() << ", location count was "<< groupLocationCount << ".\n";
			std::cout.flush();

			return count == groupLocationCount;
		}

		return false;
	}

	int32_t getOwnedCount() const {
		return ownedCount;
	}
};
}

#endif /* PROPGROUPCOUNTER_HPP_ */
