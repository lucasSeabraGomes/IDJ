/*
 * Action.h
 *
 *  Created on: 28 de jul. de 2022
 *      Author: newlo
 */

#ifndef SRC_ACTION_H_
#define SRC_ACTION_H_
#include "Vec2.h"
enum ActionType{
		MOVE,
		SHOOT
};
class Action {
public:
	Action();
	virtual ~Action();
	Action (ActionType type , float x ,float y );
	ActionType type;
	Vec2 pos;
};
#endif /* SRC_ACTION_H_ */
