//
// Created by vhundef on 26.06.19.
//

#ifndef COURSEWORK_PLAYER_H
#define COURSEWORK_PLAYER_H


#include "GameObject.h"
#include "ScreenManager.h"
#include "Weapon.h"

class Tank : GameObject {
private:
    int health{0}, movementDirection{0}, movementSpeed{0};
    ScreenManager *screenManager = nullptr;
    int score{0};
    SDL_Rect body{};
public:
    Weapon weapon;

    explicit Tank(ScreenManager *screenMgr) {
        screenManager = screenMgr;
        health = 100;
        movementDirection = 0;
        movementSpeed = 1;
        body.x = location.x1;
        body.y = location.y1;

        weapon.init(screenManager);
        weapon.location = this->location;

        score = 0;
    }

    int checkIfCanGo(int deltaLoc, bool xAxis) {
        if (xAxis) {
            if (location.x1 + deltaLoc < 0 || location.x2 + deltaLoc > screenManager->getScreenWidth()) return 0;
        } else {
            if (location.y1 + deltaLoc < 0 || location.y2 + deltaLoc > screenManager->getScreenHeight()) return 0;
        }
        return deltaLoc;
    }

    void updateLocation() {
        if (movementDirection == 1 || movementDirection == -1) {
            location.x1 += checkIfCanGo(movementDirection * movementSpeed, true);
            location.x2 = location.x1 + body.w;
        } else {
            location.y1 += checkIfCanGo(movementDirection / -2 * movementSpeed, false);
            location.y2 = location.y1 + body.h;
        }
    }

    void reDraw() {
        if (health > 0) {
            updateLocation();
            body.x = location.x1;
            body.y = location.y1;
            switch (movementDirection) {
                case -1:
                    screenManager->drawImage("../Game/Sprites/Tank_L.png", &body);
                    break;
                case 1:
                    screenManager->drawImage("../Game/Sprites/Tank_R.png", &body);
                    break;
                case -2:
                    screenManager->drawImage("../Game/Sprites/Tank_D.png", &body);
                    break;
                case 2:
                    screenManager->drawImage("../Game/Sprites/Tank_U.png", &body);
                    break;
                default:
                    break;

            }
            weapon.update(location, movementDirection);
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
