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
#include "GameData.h"

#include "StageState.h"
#include "TitleState.h"
#ifndef GAME_H_
#define GAME_H_

class Game {
private:
	string title;

	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Game (string title , int width, int height );
	int frameStart;
	float dt;
	std::vector<std::shared_ptr<State>>  stateStack;
	State* storedState;
	GameData gameData;
public:
	Resources* recursos;
	int width ;
	int height ;
	Camera* camera;
	InputManager* input;
	void CalculateDeltaTime();
	float GetDeltaTime();
	virtual ~Game();
	void Run();
	SDL_Renderer* GetRenderer ();
	static Game* GetInstance ();
	State* GetState ();
	void  Push ( State* state);
};

#endif /* GAME_H_ */
