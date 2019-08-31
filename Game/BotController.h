//
// Created by vhundef on 28.08.2019.
//

#ifndef NEWCOURSEWORK_BOTCONTROLLER_H
#define NEWCOURSEWORK_BOTCONTROLLER_H


#include "Tank.h"

class BotController {
private:
    struct whereCanGo {
        bool left;
        bool right;
        bool up;
        bool down;
        int chosenOption{0};
    } canGo, canGoPrev;
public:
    BotController(Tank *ctrledTank) {
        controlledTank = ctrledTank;
        controlledTank->setMovementSpeed(1);
    }

    Tank *controlledTank;

    int makeMovementDecision() {
        canGoPrev = canGo;
        canGo.left = controlledTank->checkIfCanGo(-20, -1);
        canGo.right = controlledTank->checkIfCanGo(20, 1);
        canGo.up = controlledTank->checkIfCanGo(-20, 2);
        canGo.down = controlledTank->checkIfCanGo(20, -2);
        cout << "-------------------------------------" << endl;
        cout << "Can Go Left:" << canGo.left << " Right:" << canGo.right << " Up:" << canGo.up << " Down:" << canGo.down
             << endl;

        if (canGo.right && canGoPrev.chosenOption != -1) {
            if (canGo.down && GameObject::randIntInRange(1, 2) == 1) {
                cout << "Going down" << endl;
                canGo.chosenOption = -2;
                return -2;
            } else if (canGo.up && GameObject::randIntInRange(1, 2) == 1) {
                cout << "Going up" << endl;
                canGo.chosenOption = 2;
                return 2;
            }
            cout << "Going right" << endl;
            canGo.chosenOption = 1;
            return 1;
        }
        if (canGo.left && canGoPrev.chosenOption != 1) {
            if (canGo.down && GameObject::randIntInRange(1, 2) == 1) {
                cout << "Going down" << endl;
                canGo.chosenOption = -2;
                return -2;
            } else if (canGo.up && GameObject::randIntInRange(1, 2) == 1) {
                cout << "Going up" << endl;
                canGo.chosenOption = 2;
                return 2;
            }
            cout << "Going left" << endl;
            canGo.chosenOption = -1;
            return -1;
        }
        if (canGo.down && canGoPrev.chosenOption != 2) {
            if (canGo.right && GameObject::randIntInRange(1, 2) == 1) {
                cout << "Going right" << endl;
                canGo.chosenOption = 1;
                return 1;
            } else if (canGo.left && GameObject::randIntInRange(1, 2) == 1) {
                cout << "Going left" << endl;
                canGo.chosenOption = -1;
                return -1;
            }
            cout << "Going down" << endl;
            canGo.chosenOption = -2;
            return -2;
        }
        if (canGo.up && canGoPrev.chosenOption != -2) {
            if (canGo.right && GameObject::randIntInRange(1, 2) == 1) {
                cout << "Going right" << endl;
                canGo.chosenOption = 1;
                return 1;
            } else if (canGo.left && GameObject::randIntInRange(1, 2) == 1) {
                cout << "Going left" << endl;
                canGo.chosenOption = -1;
                return -1;
            }
            cout << "Going up" << endl;
            canGo.chosenOption = 2;
            return 2;
        }
        if (canGo.left) {
            cout << "Going left_G" << endl;
            canGo.chosenOption = -1;
            return -1;
        } else if (canGo.right) {
            cout << "Going right_G" << endl;
            canGo.chosenOption = 1;
            return 1;
        } else if (canGo.up) {
            cout << "Going up_G" << endl;
            canGo.chosenOption = 2;
            return 2;
        } else if (canGo.down) {
            cout << "Going down_G" << endl;
            canGo.chosenOption = -2;
            return -2;
        } else {
            cout << "How the hell??" << endl;
            return 1;
        }

    }

    void moveTank() {
        controlledTank->setMovementDirection(makeMovementDecision());
    }

    /*  GameObject::coords getBotCoords(){
          return controlledTank.location;
      }*/
};


#endif //NEWCOURSEWORK_BOTCONTROLLER_H
