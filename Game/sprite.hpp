//
// Created by vhundef on 15.09.2019.
//

#ifndef TANKSCOURSEWORKRD_SPRITE_HPP
#define TANKSCOURSEWORKRD_SPRITE_HPP


#include <SDL/SDL_video.h>
#include <string>
#include <SDL/SDL_image.h>
#include <iostream>
#include "drawable_object.hpp"
#include "game_object.hpp"

using namespace std;

class Sprite : virtual protected DrawableObject, virtual protected GameObject {
protected:
	string fileName;
	SDL_Rect objBody;

	void drawImage() {
		SDL_Surface *image = IMG_Load(fileName.c_str());
		if (image == nullptr) {
			cout << "Error drawImage " + (string) IMG_GetError() << endl;
			screenManager->draw_Rect(objBody.x, objBody.y, 32, 32, 0x6a0dad);
		}
		SDL_BlitSurface(image, nullptr, screenManager->getMainSurface(), &objBody);
	}

	void redraw() override {
		if (isOnScreen) {
			drawImage();
		} else {
			cout << "Cannot redraw(" << this << ") obj is not on screen" << endl;
		}
	}
};


#endif //TANKSCOURSEWORKRD_SPRITE_HPP
