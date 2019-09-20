//
// Created by vhundef on 15.09.2019.
//

#ifndef TANKSCOURSEWORKRD_DRAWABLE_OBJECT_HPP
#define TANKSCOURSEWORKRD_DRAWABLE_OBJECT_HPP


#include "ScreenManager.h"
#include "game_object.hpp"

class DrawableObject : public virtual GameObject {
protected:
	ScreenManager *screenManager{};

	virtual void redraw() {
		return;
	}
};


#endif //TANKSCOURSEWORKRD_DRAWABLE_OBJECT_HPP
