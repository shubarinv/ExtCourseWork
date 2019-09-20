//
// Created by vhundef on 16.09.2019.
//

#ifndef TANKSCOURSEWORKRD_WEAPON_HPP
#define TANKSCOURSEWORKRD_WEAPON_HPP


#include <list>
#include "ScreenManager.h"
#include "drawable_object.hpp"
#include "moveable_object.hpp"

class Particle : virtual public DrawableObject, virtual public MoveableObject, virtual public GameObject {
private:
	SDL_Rect particle{};
public:
	Particle() {
		isOnScreen = true;
	}

	void init(ScreenManager *screenMgr, coords loc, int movementDir) {
		cout << "Particle was spawned: " << this << endl;
		if (abs(movementDir) == 1) {
			particle.h = 5;
			particle.w = 10;
		} else {
			particle.h = 10;
			particle.w = 5;
		}
		particle.x = (loc.x1 + loc.x2) / 2;
		particle.y = (loc.y1 + loc.y2) / 2;
		cout << "particle init with x1: " << loc.x1 << " x2: " << loc.x2 << " y1: " << loc.y1 << " y2: " << loc.y2
		     << endl;
		screenManager = screenMgr;
		location.x1 = loc.x1;
		location.x2 = loc.x2 + particle.w;
		location.y1 = loc.y1;
		location.y2 = loc.y2 + particle.w;
		movementDirection = movementDir;
	}

	void redraw() override {
		if (isOnScreen) {
			updateLocation();
			SDL_FillRect(screenManager->getMainSurface(), &particle, 0xff0000);
		} else {
			cout << "WARNING: Particle Should have been deleted, but got reDraw command" << endl;
		}
	}

private:
	void updateLocation() override {
		if (isOnScreen) {
			switch (movementDirection) {
				case -1:
					particle.x -= 2;
					break;
				case 1:
					particle.x += 2;
					break;
				case -2:
					particle.y += 2;
					break;
				case 2:
					particle.y -= 2;
					break;
				default:
					break;
			}

			if (particle.y >= screenManager->getScreenHeight() || particle.y <= 0 || particle.x <= 0 ||
			    particle.x >= screenManager->getScreenWidth())
				isOnScreen = false;

			location.y1 = particle.y;
			location.y2 = particle.y + particle.h;
			location.x1 = particle.x;
			location.x2 = particle.x + particle.w;
		}
	}

public:
	static bool removalCheck(const Particle &prtcl) {
		return !prtcl.isOnScreen;
	}
};


class Weapon : public GameObject {
private:
	ScreenManager *screenManager{};
	int facingDirection{-0};
public:

	void init(ScreenManager *screenMgr) {
		cout << "Weapon was spawned: " << this << endl;
		screenManager = screenMgr;
	}

	void shoot() {
		particles.push_back(*new Particle());
		particles.back().init(screenManager, location, facingDirection);
	}

	void update(coords newloc, int movementDirection) {
		location = newloc;
		facingDirection = movementDirection;
		particles.remove_if(Particle::removalCheck);
		if (!particles.empty()) {
			for (auto &particle : particles) {
				particle.redraw();
			}

		}
	}

	list<Particle> particles;
};


#endif //TANKSCOURSEWORKRD_WEAPON_HPP
