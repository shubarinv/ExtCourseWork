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

        int pathL{0}, pathR{0}, pathU{0}, pathD{0}, i = 1;

        if (canGo.left)
            while (controlledTank->checkIfCanGo(-pathL * 50, -1)) {
                pathL++;
            }
        cout << "L " << pathL << endl;

        if (canGo.right)
            while (controlledTank->checkIfCanGo(pathR * 50, 1)) {
                pathR++;
            }
        cout << "R " << pathR << endl;

        if (canGo.up)
            while (controlledTank->checkIfCanGo(-pathU * 50, 2)) {
                pathU++;
            }
        cout << "U " << pathU << endl;

        if (canGo.down)
            while (controlledTank->checkIfCanGo(pathD * 50, -2)) {
                pathD++;
            }
        cout << "D " << pathD << endl;


        if (pathL > pathR && pathL > pathD && pathL > pathU) {
            if (canGoPrev.chosenOption == 1 && canGo.right) {
                canGo.chosenOption = 1;
                return 1;
            }
            canGo.chosenOption = -1;
            return -1;
        }
        if (pathR > pathL && pathR > pathD && pathR > pathU) {
            if (canGoPrev.chosenOption == -1 && canGo.left) {
                canGo.chosenOption = -1;
                return -1;
            }
            canGo.chosenOption = 1;
            return 1;
        }
        if (pathD > pathR && pathL > pathD && pathD > pathU) {
            if (canGoPrev.chosenOption == 2 && canGo.up) {
                canGo.chosenOption = 2;
                return 2;
            }
            canGo.chosenOption = -2;
            return -2;

        }
        if (pathU > pathR && pathU > pathD && pathL > pathU) {
            if (canGoPrev.chosenOption == -2 && canGo.down) {
                canGo.chosenOption = -2;
                return -2;
            }
            canGo.chosenOption = 2;
            return 2;

        } else {
            if (canGo.left && !canGo.right && !canGo.up && !canGo.down) {
                canGo.chosenOption = -1;
                return -1;
            }
            if (canGo.right && !canGo.left && !canGo.up && !canGo.down) {
                canGo.chosenOption = 1;
                return 1;
            }
            if (canGo.up && !canGo.left && !canGo.right && !canGo.down) {
                canGo.chosenOption = 2;
                return 2;
            }
            if (canGo.down && !canGo.up && !canGo.left && !canGo.right) {
                canGo.chosenOption = -2;
                return -2;
            } else {
                canGo.chosenOption = canGoPrev.chosenOption;
                return canGoPrev.chosenOption;
            }
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
