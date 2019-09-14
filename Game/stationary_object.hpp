//
// Created by vhundef on 14.09.2019.
//

#ifndef NEWCOURSEWORK_STATIONARY_OBJECT_HPP
#define NEWCOURSEWORK_STATIONARY_OBJECT_HPP


#include "GameObject.h"

class StationaryObject: virtual public GameObject {
protected:
	bool destructible{false};

};


#endif //NEWCOURSEWORK_STATIONARY_OBJECT_HPP
