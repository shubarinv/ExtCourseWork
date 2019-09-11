//
// Created by vhundef on 26.06.19.
//

#ifndef COURSEWORK_EVENTMANAGER_H
#define COURSEWORK_EVENTMANAGER_H

#include <SDL/SDL_events.h>
#include <string>

using namespace std;
class EventManager {


private:
    SDL_Event event{};
public:
    SDL_Event getEvent() {
        event.type = '\0';
        SDL_PollEvent(&event);

        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            event.type = SDL_QUIT; // So that app will close on ESC btn press

        return event;
    }

    /**
 * @brief turns SDL_Event to String
 **/
    static string eventToStr(char param) {
        string str;
        char alphabet[] = {"qwertyuiopasdfghjklzxcvbnm[];./,'-=+1234567890"};
        for (char i : alphabet) {
            if (param == i) str += i;
        }
        return str;
    }

};


#endif //COURSEWORK_EVENTMANAGER_H