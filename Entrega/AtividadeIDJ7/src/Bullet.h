/*
 * Bullet.h
 *
 *  Created on: 1 de ago. de 2022
 *      Author: newlo
 */

#ifndef SRC_BULLET_H_
#define SRC_BULLET_H_
#include "Collider.h"
#include "Sound.h"
class Bullet:public Component {
public:
	Bullet(GameObject* associated,  float  angle , float  speed, int damage,float maxDistance,    std::string      sprite,int frames,bool targetsPlayer=true);
	Bullet();
	virtual ~Bullet();
	void Render(SDL_Renderer* render,Vec2 camera );
	void Update(float dt);
	bool Is(string tipo);
	int GetDamage ();
	void NotifyCollision(GameObject*other);
	bool targetsPlayer;
private:
	float speed;
	float angle;
	float distanceLeft;
	int damage;
};

#endif /* SRC_BULLET_H_ */
