/*
 * Face.h
 *
 *  Created on: 2 de jul. de 2022
 *      Author: newlo
 */
#include "Sound.h"
#include "Component.h"
#ifndef SRC_FACE_H_
#define SRC_FACE_H_

class Face:public Component {
public:
	Face(GameObject* associated );
	virtual ~Face();
	bool Damage(int damage);
	void Upadate(float dt);
	void Render(SDL_Renderer* render);
	bool Is(string tipo);
private:
	int hitpoints;
};

#endif /* SRC_FACE_H_ */
