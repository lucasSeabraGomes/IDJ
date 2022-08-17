/*
 * PenguinBody.h
 *
 *  Created on: 8 de ago. de 2022
 *      Author: newlo
 */
#include "PenguinCannon.h"
#ifndef SRC_PENGUINBODY_H_
#define SRC_PENGUINBODY_H_

class PenguinBody:public Component  {
public:
	PenguinBody();
	virtual ~PenguinBody();
	PenguinBody (GameObject* associated);
	void Start();
	void Update ( float dt);
	void Render(SDL_Renderer* render,Vec2 camera );
	bool Is(string tipo);
	static PenguinBody* player;
	void NotifyCollision(GameObject*other);
private:
	GameObject* pcannon;
	float maxSpeed;
	float minSpeed;
	float linearSpeed;
	float angle;
	int hp;
};

#endif /* SRC_PENGUINBODY_H_ */
