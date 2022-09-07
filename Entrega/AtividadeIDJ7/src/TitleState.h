/*
 * TitleState.h
 *
 *  Created on: 17 de ago. de 2022
 *      Author: newlo
 */

#ifndef SRC_TITLESTATE_H_
#define SRC_TITLESTATE_H_
#include "State.h"
#include "Text.h"
class TitleState:public State {
public:
	TitleState();
	virtual ~TitleState();
	void LoadAssets();
	void Update(float dt) ;
	void Render();
	void Start();
	void Pause ();
	void Resume ();
};

#endif /* SRC_TITLESTATE_H_ */
