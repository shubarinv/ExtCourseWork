//
// Created by vhundef on 15.09.2019.
//

#ifndef TANKSCOURSEWORKRD_GAME_OBJECT_HPP
#define TANKSCOURSEWORKRD_GAME_OBJECT_HPP

#include <random>

class GameObject {
public:
	struct coords {
		int x1{1}, x2{1};
		int y1{1}, y2{1};
	};

	static int randIntInRange(int min, int max) {
		std::random_device rd;     // only used once to initialise (seed) engine
		std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
		std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased

		auto random_integer = uni(rng);
		return random_integer;
	}

	coords location{0, 0, 0, 0};

	bool isOnScreen{true};

	virtual void applyDamage(int DeltaHP) {
		hp += DeltaHP;
		if (hp <= 0) {
			isOnScreen = false;
		}
	}

	static bool removalCheck(const GameObject &obj) {
		return !obj.isOnScreen;
	}

protected:

	int hp{100};

};


#endif //TANKSCOURSEWORKRD_GAME_OBJECT_HPP
