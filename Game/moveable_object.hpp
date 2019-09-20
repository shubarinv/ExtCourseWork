//
// Created by vhundef on 15.09.2019.
//

#ifndef TANKSCOURSEWORKRD_MOVEABLE_OBJECT_HPP
#define TANKSCOURSEWORKRD_MOVEABLE_OBJECT_HPP


#include <stdexcept>
#include <iostream>
#include "game_object.hpp"
#include "MapManager.h"

using namespace std;

class MoveableObject : protected virtual GameObject {
protected:
	SDL_Rect body{};

	int movementSpeed{0}, movementDirection{0};
	int width{0}, height{0};

	virtual void updateLocation() {
		if (!isOnScreen) { return; }
		if (width == 0 || height == 0)
			cout << "(" << this << ") INVALID Width or Height" << endl;
		else {
			if ((movementDirection == 1 || movementDirection == -1) &&
			    checkIfCanGo(movementDirection * movementSpeed) != 0) {
				location.x1 += movementDirection * movementSpeed;
				location.x2 = location.x1 + width;
			} else if (checkIfCanGo(movementDirection / -2 * movementSpeed) != 0) {
				location.y1 += movementDirection / -2 * movementSpeed;
				location.y2 = location.y1 + height;
			}
		}
	}

	void checkCollision() { throw runtime_error("Not yet implemented"); }

	virtual int checkIfCanGo(int deltaLoc) { return 0; }

	void spawnAtRandomLocation(MapManager *mapManager, ScreenManager *screenManager) {
		while (mapManager->getCurrentMap()->checkForCollision(location) != 0) {
			body.x = randIntInRange(100, screenManager->getScreenWidth() - 100);
			body.y = randIntInRange(100, screenManager->getScreenHeight() - 100);
			body.h = 42;
			body.w = body.h;
			width = body.w;
			height = body.h;


			location.x1 = body.x;
			location.x2 = body.x + body.w;
			location.y1 = body.y;
			location.y2 = body.y + body.h;
		}
	}
};


#endif //TANKSCOURSEWORKRD_MOVEABLE_OBJECT_HPP
