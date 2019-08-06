//
// Created by vhundef on 25.06.19.
//

#ifndef COURSEWORK_GAMEOBJECT_H
#define COURSEWORK_GAMEOBJECT_H


#include <random>

class GameObject {
public:
    bool initialsed{false};
    struct coords {
        int x1, x2;
        int y1, y2;
    };
    coords location;
    bool canBeRemoved=true;
    bool shouldBeRemoved=false;

    int randIntInRange(int min, int max) {
        std::random_device rd;     // only used once to initialise (seed) engine
        std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
        std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased

        auto random_integer = uni(rng);
        return random_integer;
    }
};


#endif //COURSEWORK_GAMEOBJECT_H
