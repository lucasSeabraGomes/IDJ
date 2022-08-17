/*
 * Action.cpp
 *
 *  Created on: 28 de jul. de 2022
 *      Author: newlo
 */

#include "Action.h"

Action::Action() {
	// TODO Auto-generated constructor stub

}

Action::~Action() {
	// TODO Auto-generated destructor stub
}

Action::Action (ActionType type , float x ,float y ){
	this->type=type;
	this->pos=Vec2(x,y);
}
