//
// Created by vhundef on 25.06.19.
//

#ifndef COURSEWORK_SCREENMANAGER_H
#define COURSEWORK_SCREENMANAGER_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <SDL/SDL_draw.h>

using namespace std;

class ScreenManager {

private:
	Sint16 max_x{1300}, max_y{700}; ///< @var max_x- Screen width. @var max_y screen height.
	SDL_Surface *mainSurface;


	/// This is framerate cap related
	int elapsed = 0, current = 0, timeSinceSecond = 0, frames = 0, next{}; //avgFPS - Avg fps per second
	int framerate = 59;
	bool swtch = true;

	void capFPS() {
		elapsed = (int) SDL_GetTicks() - current;
		current += elapsed;
		timeSinceSecond += elapsed;
		frames++;
		if (timeSinceSecond >= 1000) {
			timeSinceSecond = 0;
			frames = 0;
		}
		next = SDL_GetTicks();
		if (next - current < 1000.0 / framerate) {
			SDL_Delay(1000.f / (float) framerate - (float) (next - current));
		}

		swtch = !swtch;
	}

public:
	void setFramerate(int purposedFPS) {
		framerate = purposedFPS;
	}

	ScreenManager() { ///< @brief Trying to init SDL
		mainSurface = SDL_SetVideoMode(max_x, max_y, 16, SDL_ANYFORMAT | SDL_DOUBLEBUF);
		if (!mainSurface) {
			throw runtime_error("ScreenManager: Failed to init SDL\n" + (string) SDL_GetError());
		}
		SDL_WM_SetCaption("Курсовая WhythefkknowsWhat rev", nullptr);
		screenUnit = max_y / 10;

		//Initialize PNG loading
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags)) {
			throw runtime_error("SDL_image could not initialize! SDL_image Error: %s\n" + (string) IMG_GetError());
		}
	}

	void changeResolution(int width, int height) {
		mainSurface = SDL_SetVideoMode(width, height, 16, SDL_ANYFORMAT | SDL_DOUBLEBUF);
		if (!mainSurface) {
			throw runtime_error("ScreenManager: Failed to init SDL\n" + (string) SDL_GetError());
		}
	}

	int screenUnit{0};

	void updateScreen() {
		SDL_UpdateRect(mainSurface, 0, 0, max_x, max_y);
		capFPS();
	}

	~ScreenManager() {
		SDL_FreeSurface(mainSurface);
		SDL_Quit();
	}

	void clearScreen() { ///<@brief Fills screen with black color
		draw_Rect(0, 0, getScreenWidth(), getScreenHeight(), 0x0);
	}

	// === GETTERS AND SETTERS ====

	[[nodiscard]] SDL_Surface *
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
