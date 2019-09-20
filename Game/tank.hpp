//
// Created by vhundef on 15.09.2019.
//

#ifndef TANKSCOURSEWORKRD_TANK_HPP
#define TANKSCOURSEWORKRD_TANK_HPP


#include "moveable_object.hpp"
#include "sprite.hpp"
#include "weapon.hpp"

class Tank : virtual public MoveableObject, virtual public Sprite, virtual public GameObject {
private:
	MapManager *mapManager{};
	bool isPlayer{false};
public:
	Weapon weapon;

	coords getLocation() {
		return location;
	}

	int getHP() { return hp; }

	Tank(ScreenManager *screenMgr, MapManager *mapMgr, bool player = false) {
		screenManager = screenMgr;
		mapManager = mapMgr;
		hp = 100;

		body.x = randIntInRange(100, screenManager->getScreenWidth() - 100);
		body.y = randIntInRange(100, screenManager->getScreenHeight() - 100);
		body.h = body.w = 42;
		width = height = body.h;
		movementDirection = randIntInRange(-2, -1);
		location = {body.x, body.x + body.w, body.y, body.y + body.h};
		spawnAtRandomLocation();
		weapon.init(screenManager);
		weapon.location = this->location;
		cout << "Spawned tank(" << this << ")" << endl;
		isPlayer = player;
	}

	int checkIfCanGo(int deltaLoc) override {
		GameObject::coords tmpCoords;
		tmpCoords.y1 = location.y1;
		tmpCoords.y2 = location.y2;
		if (movementDirection == 1 || movementDirection == -1) {
			tmpCoords.x1 = location.x1 + movementDirection * movementSpeed;
			tmpCoords.x2 = tmpCoords.x1 + body.w;
			tmpCoords.y1 = location.y1;
			tmpCoords.y2 = location.y2;
		} else {
			tmpCoords.x1 = location.x1;
			tmpCoords.x2 = location.x2;
			tmpCoords.y1 = location.y1 + movementDirection / -2 * movementSpeed;
			tmpCoords.y2 = tmpCoords.y1 + body.h;
		}
		if (mapManager->getCurrentMap()->checkForCollision(tmpCoords, true))
			return 0;

		return deltaLoc;
	}

	bool checkIfCanGo(int deltaLoc, int movementDir) {
		GameObject::coords tmpCoords;
		tmpCoords.y1 = location.y1;
		tmpCoords.y2 = location.y2;
		if (movementDir == 1 || movementDir == -1) {
			tmpCoords.x1 = location.x1 + deltaLoc;
			tmpCoords.x2 = tmpCoords.x1 + body.w;
			tmpCoords.y1 = location.y1;
			tmpCoords.y2 = location.y2;
		} else {
			tmpCoords.x1 = location.x1;
			tmpCoords.x2 = location.x2;
			tmpCoords.y1 = location.y1 + deltaLoc;
			tmpCoords.y2 = tmpCoords.y1 + body.h;
		}
		return !mapManager->getCurrentMap()->checkForCollision(tmpCoords, true);

	}

	void spawnAtRandomLocation() {
		MoveableObject::spawnAtRandomLocation(mapManager, screenManager);
	}

	void redraw() override {
		updateLocation();
		objBody.x = body.x = location.x1;
		objBody.y = body.y = location.y1;

		switch (movementDirection) {
			case -1:
				if (isPlayer)
					fileName = "../Game/Sprites/Tank_P_L.png";
				else
					fileName = "../Game/Sprites/Tank_L.png";
				break;
			case 1:
				if (isPlayer)
					fileName = "../Game/Sprites/Tank_P_R.png";
				else
					fileName = "../Game/Sprites/Tank_R.png";
				break;
			case -2:
				if (isPlayer)
					fileName = "../Game/Sprites/Tank_P_D.png";
				else
					fileName = "../Game/Sprites/Tank_D.png";
				break;
			case 2:
				if (isPlayer)
					fileName = "../Game/Sprites/Tank_P_U.png";
				else
					fileName = "../Game/Sprites/Tank_U.png";
				break;
			default:
				break;

		}
		weapon.update(location, movementDirection);
		Sprite::redraw();
	}

	void shoot() {
		if (isOnScreen)
			weapon.shoot();
	}

	void setMovementDirection(int direction) {
		movementDirection = direction;
	}

	void setMovementSpeed(int mvSpeed) {
		movementSpeed = mvSpeed;
	}
};


#endif //TANKSCOURSEWORKRD_TANK_HPP
