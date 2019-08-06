//
// Created by vhundef on 26.06.19.
//

#ifndef COURSEWORK_ENEMY_H
#define COURSEWORK_ENEMY_H


#include "Ship.h"

class Enemy : public Ship {
private:
	bool initialised;
public:

	Enemy() {
		initialised = false;
	};

	void init(ScreenManager *screenMgr) {
		cout << "Enemy was spawned: " << this << endl;
		health = 100;
		screenManager = screenMgr;
		movementDirection = 1;
		movementSpeed = 1;
			body.w = 80;
			body.h = 30;
			body.x = randIntInRange(100, screenManager->getScreenWidth());
			body.y = 70;
			SDL_FillRect(screenMgr->getMainSurface(), &body, bodyColor);

		location.x1 = body.x;
		location.x2 = body.x + body.w;
		location.y1 = body.y;
		location.y2 = body.y + body.h;

		weapon.init(screenManager, true);
		weapon.location = this->location;

		hitLoc = new int[health / 20]{-1};

		initialised = true;
	}


	void reDraw() {
		if (!initialised)throw runtime_error("ERROR: tried to call reDraw for uninitialised Enemy ship!");
		if (health > 0) {
			updateLocation();
			body.x = location.x1;
            location.x2=location.x1+body.w;
			SDL_FillRect(screenManager->getMainSurface(), &body, bodyColor);
			weapon.update(location);

			/**
			 * @bug code bellow will somewhy throw SEGFAULT
			 * */
			/*if (movementDirection == -1) {
				//  Draw_Line(screenManager->getMainSurface(), location.x1, location.y2, location.x1-30, location.y1, 0x00);
			} else {
				// Draw_Line(screenManager->getMainSurface(), location.x2, location.y2, location.x2+1, location.y1, 0xff);
			}*/

			for (int i = 0; hitLoc[i]!=-1 ; ++i) {
				Draw_FillCircle(screenManager->getMainSurface(), hitLoc[i] + location.x1, location.y2 + 10, 10, 0xff1100);
			}
		} else {
			cout << "WARNING: Enemy(" << this << ") Should have been deleted, but got reDraw command" << endl;
		}
	}

};


#endif //COURSEWORK_ENEMY_H
