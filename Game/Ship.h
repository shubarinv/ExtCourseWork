//
// Created by vhundef on 25.06.19.
//

#ifndef COURSEWORK_SHIP_H
#define COURSEWORK_SHIP_H

#include <SDL/SDL.h>
#include <SDL/SDL_draw.h>
#include "GameObject.h"
#include "ScreenManager.h"
#include "Weapon.h"
#include <list>

using namespace std;

class Ship : public GameObject {
protected:
    int health{0}, movementDirection{0}, movementSpeed{0};

    ScreenManager *screenManager = nullptr;
    int bodyColor = 0x727272;
	int *hitLoc;

    void updateLocation() {
        location.x1 += movementDirection * movementSpeed;

        // ==== Location checks (so that player won't go off screen) ==== //
        if ((location.x1 >= screenManager->getScreenWidth() - 90) && movementDirection == 1)
            location.x1 -= screenManager->getScreenWidth() - 120;

        if ((location.x1 < 0) && movementDirection == -1)
            location.x1 += screenManager->getScreenWidth() - 90;
    }

public:
    coords getCoords() {
        return location;
    }

    void setHealth(int deltaHealth) {
        health += deltaHealth;
    }

    int getHealth() {
        return health;
    }

    int getMovementSpeed() const {
        return movementSpeed;
    }

    void setMovementSpeed(int mvSpeed) {
        Ship::movementSpeed = mvSpeed;
    }
	void gotHit(int loc){
		int i;
		for (i = 0; hitLoc[i]!=-1 ; ++i) ;
		hitLoc[i]=loc-location.x1;
	}

    Weapon weapon;
    coords location;
    SDL_Rect body;
};


#endif //COURSEWORK_SHIP_H
