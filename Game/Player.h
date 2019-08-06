//
// Created by vhundef on 26.06.19.
//

#ifndef COURSEWORK_PLAYER_H
#define COURSEWORK_PLAYER_H

#include "Ship.h"

class Player : public Ship {
private:
    int money{0};
    int bodyColor = 0x727272;

public:
    explicit Player(ScreenManager *screenMgr) {
        screenManager = screenMgr;
        health = 100;
        movementDirection = 1;
        movementSpeed = 1;
        body.w = 90;
        body.h = 35;
        body.x = 100;
        body.y = screenMgr->getScreenHeight() - 50;
        SDL_FillRect(screenMgr->getMainSurface(), &body, bodyColor);
        location.x1 = body.x;
        location.x2 = body.x + body.w;
        location.y1 = body.y;
        location.y2 = location.y1 + body.h;

        weapon.init(screenManager, false);
        weapon.location = this->location;
        hitLoc = new int[health / 20]{-1};
        money = 0;
    }

    void reDraw() {
        if (health > 0) {
            updateLocation();
            body.x = location.x1;
            location.x2=location.x1+body.w;
            SDL_FillRect(screenManager->getMainSurface(), &body, bodyColor);
            weapon.update(location);
        }
    }

    /**
     * @param direction -1=left ; 1=right
     **/
    void setMovementDirection(int direction) {
        movementDirection = direction;
    }

    int getMoney() {
        return money;
    }

    void shoot() {
        weapon.shoot();
    }

    SDL_Rect body{};
};


#endif //COURSEWORK_PLAYER_H
