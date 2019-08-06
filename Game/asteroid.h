//
// Created by vhundef on 06.08.2019.
//

#ifndef NEWCOURSEWORK_ASTEROID_H
#define NEWCOURSEWORK_ASTEROID_H


#include "GameObject.h"
#include "ScreenManager.h"

class Asteroid : GameObject {
private:
	ScreenManager *screenManager;
	int movementByX{0}, movementByY{0}, size{0};
	Sint16 x{30}, y{60};

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
		//y = randIntInRange(size*10+20, screenManager->getScreenHeight()-size*15-1);
		size = randIntInRange(1, 6);
		Draw_Circle(screenMgr->getMainSurface(), x, y, 10 * size, 0xF4F1C9);
	}

	void reDraw() {
		updateLocation();
		if (y >= screenManager->getScreenHeight() - size * 10) {
			size = randIntInRange(1, 6);
			y = size * 10;
		}
		Draw_FillCircle(screenManager->getMainSurface(), x, y, 10 * size, 0xF4F1C9);
	}


};


#endif //NEWCOURSEWORK_ASTEROID_H
