//
// Created by vhundef on 06.08.2019.
//

#ifndef NEWCOURSEWORK_ASTEROID_H
#define NEWCOURSEWORK_ASTEROID_H


#include "Lib/Lib.cpp"

class Asteroid : GameObject {
private:
	ScreenManager *screenManager;
	int movementByX{0}, movementByY{0}, size{0};
	Sint16 x{30}, y{60};
	bool isOnScreen{true};

	void updateLocation() {
		x += movementByX;
		y += movementByY;
	}

public:
	Asteroid(ScreenManager *screenMgr) {
		screenManager = screenMgr;
		movementByX = randIntInRange(-1, 1);
		movementByY = randIntInRange(1, 4);
		x = randIntInRange(0, screenManager->getScreenWidth());
		//y = randIntInRange(size*10+30, 400);
		size = randIntInRange(1, 6);
		Draw_Circle(screenMgr->getMainSurface(), x, y, 10 * size, 0xF4F1C9);
		initialised = true;
	}

	void reDraw() {
		if (initialised && isOnScreen) {
			updateLocation();
			if (y >= screenManager->getScreenHeight() - size * 10) {
				size = randIntInRange(1, 6);
				movementByX = randIntInRange(-1, 1);
				movementByY = randIntInRange(1, 4);
				y = size * 10;
				x = randIntInRange(1, screenManager->getScreenWidth() - size * 10);
			}
			Draw_FillCircle(screenManager->getMainSurface(), x, y, 10 * size, 0xF4F1C9);
		}
	}

	void checkForOverlap();


};


#endif //NEWCOURSEWORK_ASTEROID_H
