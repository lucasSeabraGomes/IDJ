/*
 * Rect.cpp
 *
 *  Created on: 2 de jul. de 2022
 *      Author: newlo
 */

#include "Rect.h"

Rect::Rect() {
	// TODO Auto-generated constructor stub

}

Rect::~Rect() {
	// TODO Auto-generated destructor stub
}
bool Rect::Contains(float X, float Y){
	if(this->x<X and this->y<Y and (this->x + this->w)>X and (this->y+ this->h)>Y){
		return true;
	}
	else{
		return false;
	}
}
