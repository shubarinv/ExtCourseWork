//
// Created by vhundef on 25.06.19.
//

#ifndef COURSEWORK_SCREENMANAGER_H
#define COURSEWORK_SCREENMANAGER_H

#include <SDL/SDL.h>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <SDL/SDL_draw.h>

using namespace std;

class ScreenManager {

private:
    Sint16 max_x{1280}, max_y{720}; ///< @var max_x- Screen width. @var max_y screen height.
    SDL_Surface *mainSurface;
public:

    ScreenManager() { ///< @brief Trying to init SDL
        mainSurface = SDL_SetVideoMode(max_x, max_y, 16, SDL_ANYFORMAT | SDL_DOUBLEBUF);
        if (!mainSurface) {
            throw runtime_error("ScreenManager: Failed to init SDL\n" + (string) SDL_GetError());
        }
        SDL_WM_SetCaption("Курсовая rev 2.0 ", nullptr);
    }
    void changeResolution(int width,int height){
	    mainSurface = SDL_SetVideoMode(width, height, 16, SDL_ANYFORMAT | SDL_DOUBLEBUF);
	    if (!mainSurface) {
		    throw runtime_error("ScreenManager: Failed to init SDL\n" + (string) SDL_GetError());
	    }
    }
    void updateScreen() {
        SDL_UpdateRect(mainSurface, 0, 0, max_x, max_y);
    }

    ~ScreenManager() {
        SDL_FreeSurface(mainSurface);
        SDL_Quit();
    }

    // === GETTERS AND SETTERS ====

    SDL_Surface *
    getMainSurface() const { ///<@brief returns pointer to surface that contains every single thing on screen
        return mainSurface;
    }

    Sint16 getScreenWidth() {
        return max_x;
    }

    Sint16 getScreenHeight() {
        return max_y;
    }

    /**
     * @brief Draws a rectangle
     * @param x - Horizontal location of upper left conner of the rect ,that you want to draw
     * @param y - Vertical Location of upper left conner of the rect ,that you want to draw
     * @param width - width of the rect you want to draw
     * @param height - height of the rect you want to draw
     * */
    void draw_Rect(int x, int y, int width, int height, int color) {
        Draw_FillRect(mainSurface, static_cast<Sint16>(x), static_cast<Sint16>(y),
                      static_cast<Uint16>(width), static_cast<Uint16>(height), color);
    }
};


#endif //COURSEWORK_SCREENMANAGER_H
