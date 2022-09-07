/*
 * StageState.h
 *
 *  Created on: 17 de ago. de 2022
 *      Author: newlo
 */

#ifndef SRC_STAGESTATE_H_
#define SRC_STAGESTATE_H_
#include "State.h"
class StageState:public State {
public:
	StageState();
	virtual ~StageState();
	void LoadAssets();
	void Update(float dt) ;
	void Render();
	void Start();
	void Pause ();
	void Resume ();
};

#endif /* SRC_STAGESTATE_H_ */
