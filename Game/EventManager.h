//
// Created by vhundef on 26.06.19.
//

#ifndef COURSEWORK_EVENTMANAGER_H
#define COURSEWORK_EVENTMANAGER_H


class EventManager {


private:
    SDL_Event event;
    int mousePosX{0}, mousePosY{0};
public:
    SDL_Event getEvent() {
        event.type = '\0';
        SDL_PollEvent(&event);
        SDL_GetMouseState(&mousePosX, &mousePosY);

        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            event.type = SDL_QUIT; // So that app will close on ESC btn press

        return event;
    }

    [[nodiscard]] int getMousePosX() const {
        return mousePosX;
    }

    [[nodiscard]] int getMousePosY() const {
        return mousePosY;
    }
};


#endif //COURSEWORK_EVENTMANAGER_H
