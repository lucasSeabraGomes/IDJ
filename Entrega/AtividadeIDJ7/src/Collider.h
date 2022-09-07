/*
 * Collider.h
 *
 *  Created on: 10 de ago. de 2022
 *      Author: newlo
 */

#ifndef SRC_COLLIDER_H_
#define SRC_COLLIDER_H_
#include "Sprite.h"
#include "Rect.h"
class Collider:public Component {
public:
	Collider(GameObject* associated ,Vec2 scale =Vec2(1,1) ,Vec2 offset =Vec2(0,0));
	virtual ~Collider();
	Rect Box;
	void Update ( float dt);
	void Render(SDL_Renderer* render,Vec2 camera );
	bool Is(string tipo);
	void SetScale (Vec2 scale );
	void SetOffset (Vec2 offset ) ;
	void NotifyCollision(GameObject*other);
private:
	Vec2 scale;
	Vec2 offset;
};

#endif /* SRC_COLLIDER_H_ */
