/*
 * EndState.h
 *
 *  Created on: 18 de ago. de 2022
 *      Author: newlo
 */

#ifndef SRC_ENDSTATE_H_
#define SRC_ENDSTATE_H_
#include "State.h"
#include "Text.h"
class EndState:public State  {
public:
	EndState();
	virtual ~EndState();
	void LoadAssets();
	void Update(float dt) ;
	void Render();
	void Start();
	void Pause ();
	void Resume ();
};

#endif /* SRC_ENDSTATE_H_ */
