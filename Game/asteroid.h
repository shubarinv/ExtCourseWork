//
// Created by vhundef on 06.08.2019.
//

#ifndef NEWCOURSEWORK_ASTEROID_H
#define NEWCOURSEWORK_ASTEROID_H

#include "GameObject.h"
#include "Weapon.h"

#define CUTE_C2_IMPLEMENTATION

#include "Lib/cute_c2.h"

class Asteroid : GameObject {
private:
	ScreenManager *screenManager;
	int movementByX{0}, movementByY{0}, size{0}, hp{100};
	Sint16 x{30}, y{60};

	bool isOnScreen{true};

	void updateLocation() {
		x += movementByX;
		y += movementByY;
	}

	bool swtch{false};

public:
	static bool removalCheck(Asteroid asteroid) {
		return (!asteroid.isOnScreen);
	}

	Asteroid(ScreenManager *screenMgr) {
		screenManager = screenMgr;
		movementByX = randIntInRange(-1, 1);
		movementByY = randIntInRange(1, 3);
		x = randIntInRange(0, screenManager->getScreenWidth());
		//y = randIntInRange(size*10+30, 400);
		size = randIntInRange(1, 6);
		Draw_Circle(screenMgr->getMainSurface(), x, y, 10 * size, 0xF4F1C9);
		initialised = true;
	}

	Asteroid(ScreenManager *screenMgr, int CoordX, int CoordY, int mvByX, int mvByY, int astSize) {
		screenManager = screenMgr;
		x = CoordX;
		y = CoordY;
		movementByX = mvByX;
		movementByY = mvByY;
		size = astSize / 2;
		initialised = true;
	}

	void setIsOnScreen(bool isOnScreen) {
		Asteroid::isOnScreen = isOnScreen;
	}


	void reDraw() {
		swtch = !swtch;
		if (hp <= 0) {
			if (size > 1) {
				shouldBreak = true;
			} else isOnScreen = false;
		}
		if (initialised && isOnScreen) {
			if (swtch) {
				updateLocation();
				if (y >= screenManager->getScreenHeight() - size * 10) {
					y = size * 10;
					x = randIntInRange(1, screenManager->getScreenWidth() - size * 10);
				}
			}
			Draw_FillCircle(screenManager->getMainSurface(), x, y, 10 * size, 0xF4F1C9);
		}
	}

	void checkForOverlap(Particle *particle) {
		c2Circle c1;
		c1.r = 10 * size;
		c1.p = c2V(x, y);
		c2AABB prticle;
		prticle.min = c2V(particle->location.x1, particle->location.y1);
		prticle.max = c2V(particle->location.x2, particle->location.y2);
		if (c2CircletoAABB(c1, prticle) != 0) {
			particle->setIsOnScreem(false);
			hp -= 30;
			cout << "Asteroid(" << this << "): got hit HP(" << hp << ")" << endl;
		}
	}

	[[nodiscard]] int getMovementByX() const {
		return movementByX;
	}

	[[nodiscard]] int getMovementByY() const {
		return movementByY;
	}

	[[nodiscard]] int getSize() const {
		return size;
	}

	[[nodiscard]] Sint16 getX() const {
		return x;
	}

	[[nodiscard]] Sint16 getY() const {
		return y;
	}

	bool shouldBreak{false};
};


#endif //NEWCOURSEWORK_ASTEROID_H
