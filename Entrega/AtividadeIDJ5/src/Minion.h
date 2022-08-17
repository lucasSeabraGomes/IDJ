/*
 * Minion.h
 *
 *  Created on: 27 de jul. de 2022
 *      Author: newlo
 */

#ifndef SRC_MINION_H_
#define SRC_MINION_H_
#include "Bullet.h"
class Minion:public Component {
public:
	Minion();
	Minion (GameObject* associated, GameObject* alienCenter,Resources* recursos , float arcOffsetDeg=0);
	void Render(SDL_Renderer* render,Vec2 camera );
	void Update(float dt);
	bool Is(string tipo);
	void Shoot(Vec2 target);
	virtual ~Minion();
private:
	GameObject* alienCenter;
	float arc;
};

#endif /* SRC_MINION_H_ */
