//
// Created by vhundef on 26.06.19.
//

#ifndef COURSEWORK_PLAYER_H
#define COURSEWORK_PLAYER_H


#include "GameObject.h"
#include "ScreenManager.h"
#include "Weapon.h"

class Player : GameObject {
private:
	int health{0}, movementDirection{0}, movementSpeed{0};
	ScreenManager *screenManager = nullptr;
	int score{0};
    int bodyColor = 0x3E4800;
    SDL_Rect UTrackBody{};
    SDL_Rect DTrackBody{};
public:
	Weapon weapon;
	explicit Player(ScreenManager *screenMgr) {
		screenManager = screenMgr;
        health = 100;
		movementDirection = 0;
		movementSpeed = 1;
        UTrackBody.w = 40;
        UTrackBody.h = 12;
        UTrackBody.x = screenMgr->getScreenWidth() / 2 - UTrackBody.w;
        UTrackBody.y = screenMgr->getScreenHeight() - 60;

        DTrackBody.w = UTrackBody.w;
        DTrackBody.h = UTrackBody.h;
        DTrackBody.x = UTrackBody.x;
        DTrackBody.y = UTrackBody.y + 26;


        SDL_FillRect(screenMgr->getMainSurface(), &UTrackBody, bodyColor);
        SDL_FillRect(screenMgr->getMainSurface(), &DTrackBody, bodyColor);

        location.x1 = UTrackBody.x;
        location.x2 = DTrackBody.x + DTrackBody.w;
        location.y1 = UTrackBody.y;
        location.y2 = location.y1 + DTrackBody.h;

		weapon.init(screenManager, false);
		weapon.location = this->location;

		score = 0;
	}

	void updateLocation() {
		location.x1 += movementDirection * movementSpeed;
		location.x2 += movementDirection * movementSpeed;
		// ==== Location checks (so that player won't go off screen) ==== //
		if ((location.x2 >= screenManager->getScreenWidth() - 2) && movementDirection == 1)
			movementDirection = 0;

		if ((location.x1 - 2 < 0) && movementDirection == -1)
			movementDirection = 0;

	}

	void reDraw() {
		if (health > 0) {
			updateLocation();
            UTrackBody.x = location.x1;

            DTrackBody.x = location.x2 - DTrackBody.w;
            SDL_FillRect(screenManager->getMainSurface(), &UTrackBody, bodyColor);
            SDL_FillRect(screenManager->getMainSurface(), &DTrackBody, bodyColor);
			
            Draw_FillEllipse(screenManager->getMainSurface(), UTrackBody.x + UTrackBody.w / 2,
                             (location.y1 + location.y2) / 2 + UTrackBody.h, 20, 7, 0x436F3E);

			weapon.update(location);
		}
	}

	/**
	 * @param direction -1=left ; 1=right
	 **/
	void setMovementDirection(int direction) {
		movementDirection = direction;
	}

	int getScore() {
		return score;
	}

	void setScore(int Deltascore) {
		score += Deltascore;
	}

	void shoot() {
		weapon.shoot();
	}

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
		movementSpeed = mvSpeed;
	}

	coords location{};

};


#endif //COURSEWORK_PLAYER_H
