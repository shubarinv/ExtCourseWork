//
// Created by vhundef on 15.09.2019.
//

#ifndef TANKSCOURSEWORKRD_STATIONARY_OBJECT_HPP
#define TANKSCOURSEWORKRD_STATIONARY_OBJECT_HPP


#include <iostream>
#include "game_object.hpp"

using namespace std;

class StationaryObject : virtual protected GameObject {
protected:
	bool destructible{false};

	void applyDamage(int deltaHP) override {
		if (destructible) {
			GameObject::applyDamage(deltaHP);
		} else {
			cout << "Cannot apply damage to (" << this << " cause it's marked indestructible" << endl;
		}
	}
};


#endif //TANKSCOURSEWORKRD_STATIONARY_OBJECT_HPP
