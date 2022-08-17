/*
 * Alien.h
 *
 *  Created on: 27 de jul. de 2022
 *      Author: newlo
 */

#ifndef SRC_ALIEN_H_
#define SRC_ALIEN_H_
#include "Minion.h"
#include "Action.h"
class Alien:public Component {
public:
	Alien();
	Alien(GameObject* associated ,int nMinions ,Resources* recursos );
	void Start();
	void Render(SDL_Renderer* render,Vec2 camera );
	void Update(float dt);
	bool Is(string tipo);
	bool Damage(int damage);
	virtual ~Alien();

private:
	Vec2 speed;
	int hp;
	int minionSpam;
	std::vector< GameObject* >minionArray ;
	std::queue<Action> taskQueue;
};

#endif /* SRC_ALIEN_H_ */
