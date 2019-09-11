//
// Created by vhundef on 26.08.2019.
//

#ifndef NEWCOURSEWORK_WALL_H
#define NEWCOURSEWORK_WALL_H


#include <SDL/SDL_video.h>
#include "GameObject.h"
#include "ScreenManager.h"

class Wall : GameObject {
private:
    int hp{100};
public:
    [[nodiscard]] int getHp() const {
        return hp;
    }

private:
    SDL_Rect block{};
    ScreenManager *screenManager{};
public:
    explicit Wall(ScreenManager *screenMgr, bool isLimiter) {
        block.h = 50;
        block.w = block.h;
        screenManager = screenMgr;
        if (isLimiter) hp = 1000000000;
    }

    void reDraw() {
        if (hp > 100) {
            SDL_FillRect(screenManager->getMainSurface(), &block, 0x7E2F13);
        } else {
            SDL_FillRect(screenManager->getMainSurface(), &block, 0x8D3516);
        }
    }

    void setHp(int deltaHP) {
        hp += deltaHP;
    }

    void setLocation(int x, int y) {
        if (x * block.h <= screenManager->getScreenWidth() && x * block.h >= 0 &&
            y * block.h <= screenManager->getScreenHeight() &&
            y * block.h >= 0) {
            block.x = x * block.h;
            block.y = y * block.h;
            //    cout << "WALL(" << this << ")->SetLocation X:" << x << " Y:" << y << " OK" << endl;
        } else
            cout << "WALL(" << this << ")->SetLocation Unable to set location, coords out of bounds " << "X:" << x
                 << "Y:" << y << endl;
    }

    int getSize() { return block.w; }

    int getX() { return block.x; }

    int getY() { return block.y; }


};


#endif //NEWCOURSEWORK_WALL_H
