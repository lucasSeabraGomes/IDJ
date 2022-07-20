/*
 * GameObject.h
 *
 *  Created on: 2 de jul. de 2022
 *      Author: newlo
 */

#include "Component.h"
#include <vector>
#include "Rect.h"
#ifndef SRC_GAMEOBJECT_H_
#define SRC_GAMEOBJECT_H_
class GameObject {
public:
	GameObject();
	virtual ~GameObject();
	void Update(float dt);
	void Render(SDL_Renderer* render,Vec2 camera );
	bool IsDead();
	void RequestDelete();
	void AddComponent(Component* cpt);
	void RemoveComponent(Component* cpt);
	Component* GetComponent(string type);
	Rect box;
private:
	std::vector <Component*> componentes;
	bool isDead;
};

#endif /* SRC_GAMEOBJECT_H_ */
