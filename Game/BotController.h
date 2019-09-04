//
// Created by vhundef on 28.08.2019.
//

#ifndef NEWCOURSEWORK_BOTCONTROLLER_H
#define NEWCOURSEWORK_BOTCONTROLLER_H


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
        cout<<"Will go"<<canGo.chosenOption<<endl;
        get_purposedMovement();
    }

    void get_purposedMovement() {
        stopThreshold = GameObject::randIntInRange(1, get_Distance());
        cout<<"For "<<stopThreshold<<endl;
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
                cout << "WHAT THE HELL???" << endl;
        }
        return tmp;
    }

public:
    explicit BotController(Tank *ctrledTank) {
        controlledTank = ctrledTank;
        controlledTank->setMovementSpeed(1);
    }

    Tank *controlledTank;

    int makeMovementDecision() {
        leftToGo = abs(stopThreshold - get_Distance());
        //cout << "Left to go: " << leftToGo << endl;
        if (leftToGo == 0) {
            get_Direction();
        }
        return canGo.chosenOption;

    }

    void moveTank() {
        controlledTank->setMovementDirection(makeMovementDecision());
    }

/*  GameObject::coords getBotCoords(){
      return controlledTank.location;
  }*/
};


#endif //NEWCOURSEWORK_BOTCONTROLLER_H
