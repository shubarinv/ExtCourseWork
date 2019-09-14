//
// Created by vhundef on 26.08.2019.
//

#ifndef NEWCOURSEWORK_WALL_H
#define NEWCOURSEWORK_WALL_H


#include <SDL/SDL_video.h>
#include "GameObject.h"
#include "ScreenManager.h"
#include "drawable_object.hpp"
#include "sprite.hpp"
#include "stationary_object.hpp"

class Wall : public virtual DrawableObject, public virtual StationaryObject {
public:
	[[nodiscard]] int getHp() const {
		return hp;
	}

private:
	SDL_Rect block{};
	ScreenManager *screenManager{};
public:
	explicit Wall(ScreenManager *screenMgr, bool canBeDestroyed) : DrawableObject() {
		block.h = 50;
		block.w = block.h;
		screenManager = screenMgr;
		if (canBeDestroyed) destructible = true;
	}

	void reDraw() {
		if (!destructible) {
			SDL_FillRect(screenManager->getMainSurface(), &block, 0x535356);
		} else {
			SDL_FillRect(screenManager->getMainSurface(), &block, 0x8D3516);
		}
	}

	void setHp(int deltaHP) {
		if (destructible) {
			hp += deltaHP;
		}
	}

	void setLocation(int x, int y) {
		if (x * block.h <= screenManager->getScreenWidth() && x * block.h >= 0 &&
		    y * block.h <= screenManager->getScreenHeight() &&
		    y * block.h >= 0) {
			block.x = x * block.h;
			block.y = y * block.h;
		} else
			cout << "WALL(" << this << ")->SetLocation Unable to set location, coords out of bounds " << "X:" << x
			     << "Y:" << y << endl;
	}

	int getSize() { return block.w; }

	int getX() { return block.x; }

	int getY() { return block.y; }


};


#endif //NEWCOURSEWORK_WALL_H
