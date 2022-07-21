/*
 * Component.h
 *
 *  Created on: 4 de jul. de 2022
 *      Author: newlo
 */
#include <iostream>
using namespace std;
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "SDL_include.h"
#include <stdlib.h>
#include "Resources.h"

#ifndef SRC_COMPONENT_H_
#define SRC_COMPONENT_H_
class GameObject;
class Component {
public:
	Component();
	virtual ~Component();
	Component(GameObject* associated );
	void virtual Render(SDL_Renderer* render);
	void virtual Update(float dt);
	bool virtual Is(string tipo);
	void virtual Open(string file,SDL_Renderer* render,Resources* recursos);
	void virtual SetClip(int x, int y ,   int w, int h);
	bool virtual Damage(int damage);
	int virtual GetWidth();
	int virtual GetHeight();
	GameObject* associated;
};

#endif /* SRC_COMPONENT_H_ */
