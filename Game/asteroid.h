//
// Created by vhundef on 06.08.2019.
//

#ifndef NEWCOURSEWORK_ASTEROID_H
#define NEWCOURSEWORK_ASTEROID_H

#include "GameObject.h"
#include "Weapon.h"

#define CUTE_C2_IMPLEMENTATION

#include "Lib/cute_c2.h"
#include "ScreenManager.h"

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

	explicit Asteroid(ScreenManager *screenMgr) {
		cout << "Spawned new asteroid(" << this << ")" << endl;
		screenManager = screenMgr;
		movementByX = randIntInRange(-1, 1);
		movementByY = randIntInRange(1, 2);
		if (movementByX == -1)
			x = randIntInRange(screenManager->getScreenWidth() / 2, screenManager->getScreenWidth());
		else if (movementByX == 1)
			x = randIntInRange(0, screenManager->getScreenWidth() / 2);
		else
			x = randIntInRange(0, screenManager->getScreenWidth());
		//y = randIntInRange(size*10+30, 400);
		size = randIntInRange(2, 5);
		hp = size * 20;
		Draw_Circle(screenMgr->getMainSurface(), x, y, 10 * size, 0xF4F1C9);
		initialised = true;
	}

	Asteroid(ScreenManager *screenMgr, int CoordX, int CoordY, int mvByX, int mvByY, int astSize) {
		cout << "Spawned new asteroid(with params)(" << this << ")" << endl;
		screenManager = screenMgr;
		x = CoordX;
		y = CoordY;
		movementByX = mvByX;
		movementByY = mvByY;
		if (movementByY == 0) {
			movementByY = 1;
		}
		size = astSize / 2;
		hp = size * 20;
		initialised = true;
	}

	void setIsOnScreen(bool isOnScreen) {
		Asteroid::isOnScreen = isOnScreen;
	}


	int reDraw() {
		swtch = !swtch;
		if (hp <= 0) {
			if (size > 1) {
				shouldBreak = true;
			} else isOnScreen = false;
		}
		if (initialised && isOnScreen) {
			if (swtch) {
				updateLocation();
				if (y >= screenManager->getScreenHeight() - size * 15) {
					y = size * 10;
					x = screenManager->getScreenWidth() + 100;
					isOnScreen = false;
					if (size == 1) {
						return 0;
					}
					return size * 20;
				}
			}
			Draw_FillCircle(screenManager->getMainSurface(), x, y, 10 * size, 0xF4F1C9);
		}
		return 0;
	}
/**
 * @brief checks if particle shot by player overlaps asteroid, using cute_c2 lib
 **/
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

/**
 * @brief checks if one asteroid overlaps this asteroid, using cute_c2 lib
 * @deprecated This function was planed to be used to merge two asteroids into one, since this mecanic was not implemented this function is deprecated
 **/
	void checkForOverlap(Asteroid asteroid) {
		c2Circle c1;
		c1.r = 10 * size;
		c1.p = c2V(x, y);
		c2Circle c2;
		c2.r = 10 * asteroid.getSize();
		c2.p = c2V(asteroid.getX(), asteroid.getY());
		if (c2CircletoCircle(c1, c2) != 0) {
			shouldUnite = true;
			cout << "Asteroid(" << this << "): got hit and will be united" << endl;
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
	bool shouldUnite{false};
};


#endif //NEWCOURSEWORK_ASTEROID_H
