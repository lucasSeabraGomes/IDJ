/*
 * InputManager.h
 *
 *  Created on: 13 de jul. de 2022
 *      Author: newlo
 */
#define LEFT_ARROW_KEY    SDLK_LEFT
#define RIGHT_ARROW_KEY   SDLK_RIGHT
#define UP_ARROW_KEY      SDLK_UP
#define DOWN_ARROW_KEY    SDLK_DOWN
#define ESCAPE_KEY        SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#define SPACE_KEY 		  SDLK_SPACE

#ifndef SRC_INPUTMANAGER_H_
#define SRC_INPUTMANAGER_H_
#include <iostream>
using namespace std;
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "SDL_include.h"
#include <stdlib.h>
#include <unordered_map>

class InputManager {
public:
	static InputManager& GetInstance();
	void  Update () ;
	bool KeyPress(int key);
	bool KeyRelease(int key);
	bool IsKeyDown(int key);
	bool MousePress(int button);
	bool MouseRelease(int button);
	bool IsMouseDown(int button);
	int GetMouseX();
	int GetMouseY();
	bool QuitRequested ();
	virtual ~InputManager();
	InputManager();
private:
	bool mouseState[6];
	int mouseUpdate[6];
	bool quitRequested;
	int updateCounter;
	int mouseX;
	int mouseY;
	bool keyState[416];
	int keyUpdate[416];
};

#endif /* SRC_INPUTMANAGER_H_ */
