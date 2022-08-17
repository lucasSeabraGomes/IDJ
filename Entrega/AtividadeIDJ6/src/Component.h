/*
 * Component.h
 *
 *  Created on: 4 de jul. de 2022
 *      Author: newlo
 */
#include <iostream>
using namespace std;
#include <stdlib.h>
#include "Resources.h"
#include "Vec2.h"
#include <memory>
#include <iomanip>
#include <vector>
#include <queue>
#include "InputManager.h"
#ifndef SRC_COMPONENT_H_
#define SRC_COMPONENT_H_
class GameObject;
class Component {
public:
	Component();
	virtual ~Component();
	Component(GameObject* associated );
	void virtual Render(SDL_Renderer* render,Vec2 camera );
	void virtual Update(float dt);
	void virtual Update(float dt,Vec2 camera );
	bool virtual Is(string tipo);
	void virtual Open(string file,SDL_Renderer* render,Resources* recursos);
	void virtual SetClip(int x, int y ,   int w, int h);
	bool virtual Damage(int damage);
	int virtual GetWidth();
	int virtual GetHeight();
	GameObject* associated;
	void virtual Start();
	bool started;
	void virtual Shoot(Vec2 target);
	Vec2 virtual GetScale ();
	void virtual SetScaleX (float scaleX,float  scaleY);
	void virtual NotifyCollision(GameObject*other);
};

#endif /* SRC_COMPONENT_H_ */
