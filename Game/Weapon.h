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
    int movementDirrection{-0};
public:
    Particle() {
        bIsOnScreen = true;
        initialised = false;
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
        movementDirrection = movementDir;
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
            switch (movementDirrection) {
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
                bIsOnScreen = false;

            location.y1 = particle.y;
            location.y2 = particle.y + particle.h;
            location.x1 = particle.x;
            location.x2 = particle.x + particle.w;
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
    int facingDirrection{-0};
public:
    
    void init(ScreenManager *screenMgr) {
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
        particles.back().init(screenManager, location, facingDirrection);
    }

    void update(coords newloc, int movementDirrection) {
        location = newloc;
        facingDirrection = movementDirrection;
        particles.remove_if(Particle::removalCheck);
        if (!particles.empty()) {
            for (auto &particle : particles) {
                particle.reDraw();
            }

        }
    }

    list<Particle> particles;
};


#endif //COURSEWORK_WEAPON_H
