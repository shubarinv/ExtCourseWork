//
// Created by vhundef on 14.09.2019.
//

#ifndef NEWCOURSEWORK_MOVING_OBJECT_HPP
#define NEWCOURSEWORK_MOVING_OBJECT_HPP


#include "GameObject.h"

class MovingObject : public GameObject {
protected:
	int movementSpeed{0}, movementDirection{0};
protected:
	virtual void updateLocation() {
		if ((movementDirection == 1 || movementDirection == -1) &&
		    checkIfCanGo(movementDirection * movementSpeed) != 0) {
			location.x1 += movementDirection * movementSpeed;
			location.x2 = location.x1 + width;
		} else if (checkIfCanGo(movementDirection / -2 * movementSpeed) != 0) {
			location.y1 += movementDirection / -2 * movementSpeed;
			location.y2 = location.y1 + height;
		}
	}

	virtual int checkIfCanGo(int deltaLoc) {
		return 1;
	}
};


#endif //NEWCOURSEWORK_MOVING_OBJECT_HPP
