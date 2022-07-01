/*
 * State.h
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
#include "Music.h"
#include "Sprite.h"
#include <stdlib.h>

#ifndef STATE_H_
#define STATE_H_

class State {
private:
	Sprite bg;
	Music music;
	bool quitRequested;
public:
	State();
	virtual ~State();
	bool QuitRequested ();
	void LoadAssets(SDL_Renderer* render,int w, int h);
	void Update(float dt) ;
	void Render(SDL_Renderer* render);
};

#endif /* STATE_H_ */
