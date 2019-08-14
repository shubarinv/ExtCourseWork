//
// Created by vhundef on 01.07.19.
//

#ifndef COURSEWORK_WEAPON_H
#define COURSEWORK_WEAPON_H


#include <list>
#include "ScreenManager.h"

class Particle : public GameObject {
private:
    bool bIsOnScreen{true};
    ScreenManager *screenManager{};
    SDL_Rect particle{};
public:
    Particle() {
        bIsOnScreen = true;
	    initialised = false;
    }
    void init(ScreenManager *screenMgr, coords loc) {
        cout << "Particle was spawned: " << this << endl;
        particle.h = 10;
        particle.w = 5;
        particle.x = (loc.x1 + loc.x2) / 2;
        particle.y = (loc.y1 + loc.y2) / 2;
        screenManager = screenMgr;
        location.x1 = particle.x;
        location.x2 = particle.x + particle.w;
	    initialised = true;
    }

    [[nodiscard]] bool isOnScreen() const {
        return bIsOnScreen;
    }

    void setIsOnScreem(bool OnScreen) {
        Particle::bIsOnScreen = OnScreen;
    }

    void reDraw() {
	    if (!initialised) cout << "WARNING: Particle is UNINITIALISED, but got reDraw command" << endl;
	    if (initialised && bIsOnScreen) {
            updateLocation();
            SDL_FillRect(screenManager->getMainSurface(), &particle, 0xff0000);
        } else {
            cout << "WARNING: Particle Should have been deleted, but got reDraw command" << endl;
        }
    }

private:
    void updateLocation() {
            if (bIsOnScreen) {
                if (particle.y >= screenManager->getScreenHeight() || particle.y <= 0)
                    bIsOnScreen = false;
                particle.y--;
                location.y1 = particle.y;
                location.y2 = particle.y + particle.h;
            }
        }

public:
    static bool removalCheck(Particle prtcl) {
	    return !prtcl.isOnScreen();
    }
};


class Weapon : public GameObject {
private:
    ScreenManager *screenManager{};
public:
    void init(ScreenManager *screenMgr, bool isEnemy) {
        cout << "Weapon was spawned: " << this << endl;
        screenManager = screenMgr;
	    initialised = true;
    }

    Weapon() {
	    initialised = false;
    }

    void shoot() {
	    if (!initialised) throw runtime_error("ERROR: attempt to call shoot on uninitialised Weapon instance\n");
        particles.push_back(*new Particle());
        particles.back().init(screenManager, location);
    }

    void update(coords newloc) {
        location = newloc;
	    particles.remove_if(Particle::removalCheck);
        if (!particles.empty()) {
            for (auto &particle : particles) {
                particle.reDraw();
            }

        }
    }

    list <Particle> particles;
};


#endif //COURSEWORK_WEAPON_H
