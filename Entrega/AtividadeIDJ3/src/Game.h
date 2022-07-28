/*
 * Game.h
 *
 *  Created on: 16 de jun. de 2022
 *      Author: newlo
 */
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "SDL_include.h"
#include "State.h"

#ifndef GAME_H_
#define GAME_H_

class Game {
private:
	string title;
	int width ;
	int height ;
	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Game (string title , int width, int height );
	State* state;
public:
	virtual ~Game();
	void Run();
	SDL_Renderer* GetRenderer ();
	static Game& GetInstance ();
	State& GetState ();
};

#endif /* GAME_H_ */
