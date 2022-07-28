/*
 * Sprite.h
 *
 *  Created on: 21 de jun. de 2022
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
#include "Component.h"




#ifndef SPRITE_H_
#define SPRITE_H_
class GameObject;
class Sprite: public Component{
public:
	Sprite();
	Sprite(GameObject* associated );
	Sprite(string file,SDL_Renderer* render,GameObject* associated );
	virtual ~Sprite();
	void Open(string file,SDL_Renderer* render);
	void SetClip(int x, int y ,   int w, int h);
	void Render(SDL_Renderer* render);
	int GetWidth();
	int GetHeight();
	bool IsOpen();
	bool Is(string tipo);
	void Update(float dt);
	int getW();
	int getH();
private:
	SDL_Texture* texture;
	int width;
	int height;
	SDL_Rect clipRect;
};

#endif /* SPRITE_H_ */
