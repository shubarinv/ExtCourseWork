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
	int bodyColor = 0x727272;
	SDL_Rect LweaponBody{};
	SDL_Rect RweaponBody{};
public:
	Weapon weapon;
	explicit Player(ScreenManager *screenMgr) {
		screenManager = screenMgr;
		health = 1000;
		movementDirection = 0;
		movementSpeed = 1;
		LweaponBody.w = 12;
		LweaponBody.h = 40;
		LweaponBody.x = screenMgr->getScreenWidth() / 2 - LweaponBody.w;
		LweaponBody.y = screenMgr->getScreenHeight() - 70;

		RweaponBody.w = LweaponBody.w;
		RweaponBody.h = LweaponBody.h;
		RweaponBody.x = LweaponBody.x + RweaponBody.w + 15;
		RweaponBody.y = LweaponBody.y;


		SDL_FillRect(screenMgr->getMainSurface(), &LweaponBody, bodyColor);
		SDL_FillRect(screenMgr->getMainSurface(), &RweaponBody, bodyColor);

		location.x1 = LweaponBody.x;
		location.x2 = RweaponBody.x + RweaponBody.w;
		location.y1 = LweaponBody.y;
		location.y2 = location.y1 + RweaponBody.h;

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
			LweaponBody.x = location.x1;

			RweaponBody.x = location.x2 - RweaponBody.w;
			SDL_FillRect(screenManager->getMainSurface(), &LweaponBody, bodyColor);
			SDL_FillRect(screenManager->getMainSurface(), &RweaponBody, bodyColor);
			Draw_FillEllipse(screenManager->getMainSurface(), LweaponBody.x + LweaponBody.w + 7,
			                 (location.y1 + location.y2) / 2, 7, 20, 0x00ff00);

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
