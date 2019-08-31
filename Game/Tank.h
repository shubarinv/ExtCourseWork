//
// Created by vhundef on 26.06.19.
//

#ifndef COURSEWORK_PLAYER_H
#define COURSEWORK_PLAYER_H


#include "GameObject.h"
#include "ScreenManager.h"
#include "Weapon.h"
#include "MapManager.h"

class Tank : GameObject {
private:
    int health{0}, movementDirection{0}, movementSpeed{0};
    ScreenManager *screenManager = nullptr;
    int score{0};
    SDL_Rect body{};
    MapManager *mapManager;
public:
    Weapon weapon;

    explicit Tank(ScreenManager *screenMgr, MapManager *mpManager) {
        screenManager = screenMgr;
        health = 100;
        score = 0;
        movementDirection = randIntInRange(-2, -1);
        movementSpeed = 0;
        mapManager = mpManager;

        // loc on map spawn
        body.x = 55;
        body.y = 55;
        body.h = 42;
        body.w = body.h;

        location.x1 = body.x;
        location.x2 = body.x + body.w;
        location.y1 = body.y;
        location.y2 = body.y + body.h;

        weapon.init(screenManager);
        weapon.location = this->location;
        cout << "Spawned tank(" << this << ")" << endl;
    }

    int checkIfCanGo(int deltaLoc) {
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
        if (mapManager->checkforCollision(tmpCoords))
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
        return !mapManager->checkforCollision(tmpCoords, true);

    }

    void updateLocation() {
        if ((movementDirection == 1 || movementDirection == -1) &&
            checkIfCanGo(movementDirection * movementSpeed) != 0) {
            location.x1 += movementDirection * movementSpeed;
            location.x2 = location.x1 + body.w;
        } else if (checkIfCanGo(movementDirection / -2 * movementSpeed) != 0) {
            location.y1 += movementDirection / -2 * movementSpeed;
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
     * @param direction -1=left ; 1=right ; 2=up ; -2=down
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
        cout << "Tank(" << this << ") HP changed to:" << getHealth() << endl;
    }

    int getHealth() {
        return health;
    }

    static bool removalCheck(const Tank &tank) {
        return tank.health <= 0;
    }

    int getMovementSpeed() const {
        return movementSpeed;
    }

    void setMovementSpeed(int mvSpeed) {
        movementSpeed = mvSpeed;
    }

    coords location{1, 1, 1, 1};

};


#endif //COURSEWORK_PLAYER_H
