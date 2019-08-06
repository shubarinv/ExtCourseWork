//
// Created by vhundef on 06.08.2019.
//

#ifndef NEWCOURSEWORK_ASTEROID_H
#define NEWCOURSEWORK_ASTEROID_H
#define SMOOTHING_ON

#include "GameObject.h"
#include "ScreenManager.h"
#include <SDL/SDL_draw.h>
#include <SDL/SDL.h>


class Asteroid : GameObject {
private:
	ScreenManager screenManager;
	int movementByX{0}, movementByY{0}, size{0};
public:
	Asteroid(ScreenManager screenMgr) {
		screenManager = screenMgr;
		movementByX = randIntInRange(-10, 10);
		movementByX = randIntInRange(1, 4);
		location.x1 = randIntInRange(0, screenManager.getScreenWidth());
		size = randIntInRange(1, 3);
	}


};


#endif //NEWCOURSEWORK_ASTEROID_H
