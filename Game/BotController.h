//
// Created by vhundef on 28.08.2019.
//

#ifndef NEWCOURSEWORK_BOTCONTROLLER_H
#define NEWCOURSEWORK_BOTCONTROLLER_H


#include <chrono>
#include <ctime>
#include "Tank.h"

class BotController {
private:
    struct whereCanGo {
        bool left{};
        bool right{};
        bool up{};
        bool down{};
        int chosenOption{0};
    } canGo;
    int stopThreshold{0}, leftToGo{0};
    time_t prevTime;
    GameObject::coords prevLocation;

    void get_Direction() {
        int tmp = GameObject::randIntInRange(1, 4);
        canGo.left = controlledTank->checkIfCanGo(-20, -1);
        canGo.right = controlledTank->checkIfCanGo(20, 1);
        canGo.up = controlledTank->checkIfCanGo(-20, 2);
        canGo.down = controlledTank->checkIfCanGo(20, -2);
        if (!canGo.left && !canGo.right && !canGo.up && !canGo.down) canGo.chosenOption = 0;
        if (!canGo.left && !canGo.right && !canGo.up && canGo.down) canGo.chosenOption = -2;
        if (!canGo.left && !canGo.right && canGo.up && !canGo.down) canGo.chosenOption = 2;
        if (!canGo.left && canGo.right && !canGo.up && !canGo.down) canGo.chosenOption = 1;
        if (canGo.left && !canGo.right && !canGo.up && !canGo.down) canGo.chosenOption = -1;
        if (!canGo.left && !canGo.right && canGo.up && canGo.down) {
            if (tmp > 2) {
                canGo.chosenOption = 2;
            } else canGo.chosenOption = -2;
        }
        if (!canGo.left && canGo.right && !canGo.up && canGo.down) {
            if (tmp > 2) {
                canGo.chosenOption = 1;
            } else canGo.chosenOption = -2;
        }
        if (!canGo.left && canGo.right && canGo.up && !canGo.down) {
            if (tmp > 2) {
                canGo.chosenOption = 1;
            } else canGo.chosenOption = 2;
        }
        if (canGo.left && !canGo.right && !canGo.up && canGo.down) {
            if (tmp > 2) {
                canGo.chosenOption = -1;
            } else canGo.chosenOption = -2;
        }
        if (canGo.left && !canGo.right && canGo.up && !canGo.down) {
            if (tmp > 2) {
                canGo.chosenOption = -1;
            } else canGo.chosenOption = 2;
        }
        if (canGo.left && canGo.right && !canGo.up && !canGo.down) {
            if (tmp > 2) {
                canGo.chosenOption = -1;
            } else canGo.chosenOption = 1;
        }
        if (!canGo.left && canGo.right && canGo.up && canGo.down) {
            tmp = GameObject::randIntInRange(1, 3);
            if (tmp == 1) {
                canGo.chosenOption = 1;
            } else if (tmp == 2)
                canGo.chosenOption = 2;
            else canGo.chosenOption = -2;
        }
        if (canGo.left && !canGo.right && canGo.up && canGo.down) {
            tmp = GameObject::randIntInRange(1, 3);
            if (tmp == 1) {
                canGo.chosenOption = -1;
            } else if (tmp == 2)
                canGo.chosenOption = 2;
            else canGo.chosenOption = -2;
        }
        if (canGo.left && canGo.right && !canGo.up && canGo.down) {
            tmp = GameObject::randIntInRange(1, 3);
            if (tmp == 1) {
                canGo.chosenOption = 1;
            } else if (tmp == 2)
                canGo.chosenOption = -1;
            else canGo.chosenOption = -2;
        }
        if (canGo.left && canGo.right && canGo.up && !canGo.down) {
            tmp = GameObject::randIntInRange(1, 3);
            if (tmp == 1) {
                canGo.chosenOption = 1;
            } else if (tmp == 2)
                canGo.chosenOption = -1;
            else canGo.chosenOption = 2;
        }
        if (canGo.left && canGo.right && canGo.up && canGo.down) {
            tmp = GameObject::randIntInRange(1, 4);
            if (tmp == 1) {
                canGo.chosenOption = 1;
            } else if (tmp == 2)
                canGo.chosenOption = -1;
            else if (tmp == 3) canGo.chosenOption = 2;
            else canGo.chosenOption = -2;
        }
        cout << "Will go" << canGo.chosenOption << endl;
        get_purposedMovement();
    }

    void get_purposedMovement() {
        if (get_Distance() > 1)
            stopThreshold = GameObject::randIntInRange(2, get_Distance());
        cout << "For " << stopThreshold << endl;
    }

    int get_Distance() {
        int tmp{0};
        switch (canGo.chosenOption) {
            case -1:
                while (controlledTank->checkIfCanGo(-tmp * 50, -1)) {
                    tmp++;
                }
                break;
            case 1:
                while (controlledTank->checkIfCanGo(tmp * 50, 1)) {
                    tmp++;
                }
                break;
            case -2:
                while (controlledTank->checkIfCanGo(-tmp * 50, 2)) {
                    tmp++;
                }
                break;
            case 2:
                while (controlledTank->checkIfCanGo(tmp * 50, -2)) {
                    tmp++;
                }
                break;
            default:
                cout << "canGoChosenOption not set" << endl;
        }
        return tmp;
    }

    ScreenManager *screenManager;

public:
    BotController(Tank *ctrledTank, ScreenManager *screenMgr) {
        controlledTank = ctrledTank;
        controlledTank->setMovementSpeed(1);
        screenManager = screenMgr;
    }

    Tank *controlledTank;

    int makeMovementDecision() {
        leftToGo = abs(stopThreshold - get_Distance());
        //cout << "Left to go: " << leftToGo << endl;
        if (leftToGo == 0) {
            get_Direction();
        }
        if (prevLocation.x1 == controlledTank->location.x1 && prevLocation.y1 == controlledTank->location.y1) {
            cout << "Stuck? left to go: " << leftToGo << endl;
            get_Direction();
        }
        prevLocation = controlledTank->location;
        return canGo.chosenOption;

    }

    void moveTank() {
        controlledTank->setMovementDirection(makeMovementDecision());
    }

/*  GameObject::coords getBotCoords(){
      return controlledTank.location;
  }*/

    void shootPlayer(GameObject::coords loc) {
        c2AABB obj, wallR;
        time_t tmp;
        time(&tmp);
        if (abs(tmp - prevTime) >= 1) {
            obj.min = c2V(loc.x1, loc.y1);
            obj.max = c2V(loc.x2, loc.y2);
            if (canGo.up) {
                wallR.min = c2V(controlledTank->location.x1, 0);
                wallR.max = c2V(controlledTank->location.x2, controlledTank->location.y1);
                if (c2AABBtoAABB(obj, wallR) != 0) { // UP
                    controlledTank->weapon.update(controlledTank->location, 2);
                    controlledTank->weapon.shoot();
                    prevTime = tmp;

                    return;
                }
            }
            if (canGo.down) {
                wallR.min = c2V(controlledTank->location.x1, controlledTank->location.y2);
                wallR.max = c2V(controlledTank->location.x2, screenManager->getScreenHeight());
                if (c2AABBtoAABB(obj, wallR) != 0) { // Down
                    controlledTank->weapon.update(controlledTank->location, -2);
                    controlledTank->weapon.shoot();
                    prevTime = tmp;
                    return;
                }
            }
            if (canGo.left) {
                wallR.min = c2V(0, controlledTank->location.y1);
                wallR.max = c2V(controlledTank->location.x1, controlledTank->location.y2);
                if (c2AABBtoAABB(obj, wallR) != 0) { // Left
                    controlledTank->weapon.update(controlledTank->location, -1);
                    controlledTank->weapon.shoot();
                    prevTime = tmp;
                    return;
                }
            }
            if (canGo.right) {
                wallR.min = c2V(controlledTank->location.x1, controlledTank->location.y1);
                wallR.max = c2V(screenManager->getScreenWidth(), controlledTank->location.y2);
                if (c2AABBtoAABB(obj, wallR) != 0) { // Right
                    controlledTank->weapon.update(controlledTank->location, 1);
                    controlledTank->weapon.shoot();
                    prevTime = tmp;
                    return;
                }
            }
        }
    }

    static bool removalCheck(const BotController &botController) {
        return botController.controlledTank->getHealth() <= 0;
    }
};


#endif //NEWCOURSEWORK_BOTCONTROLLER_H
