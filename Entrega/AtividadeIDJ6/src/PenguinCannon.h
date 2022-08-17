/*
 * PenguinCannon.h
 *
 *  Created on: 8 de ago. de 2022
 *      Author: newlo
 */
#include "Bullet.h"
#include "Timer.h"
#ifndef SRC_PENGUINCANNON_H_
#define SRC_PENGUINCANNON_H_

class PenguinCannon:public Component   {
public:
	PenguinCannon();
	PenguinCannon(GameObject* associated,GameObject* penguinBody);
	virtual ~PenguinCannon();
	void Update ( float dt);
	void Render(SDL_Renderer* render,Vec2 camera );
	bool Is(string tipo);
	void  Shoot ();
private:
	Timer timer;
	GameObject* pbody;
	float angle;
};

#endif /* SRC_PENGUINCANNON_H_ */
