//
// Created by vhundef on 14.09.2019.
//

#ifndef NEWCOURSEWORK_SPRITE_HPP
#define NEWCOURSEWORK_SPRITE_HPP


#include "drawable_object.hpp"

using namespace std;

class Sprite : protected virtual DrawableObject {
protected:
	string fileName;
	SDL_Rect objBody;

	virtual void reDraw(){
		screenManager->drawImage(fileName,&objBody);
	}
};


#endif //NEWCOURSEWORK_SPRITE_HPP
