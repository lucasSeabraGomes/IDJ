/*
 * State.h
 *
 *  Created on: 21 de jun. de 2022
 *      Author: newlo
 */

#include <iostream>
using namespace std;
#include "Music.h"
#include "Sprite.h"
#include <memory>
#include <iomanip>
#include "GameObject.h"
#include "Face.h"
#include "SDL_events.h"
#include "Sound.h"
#include "Resources.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"

#ifndef STATE_H_
#define STATE_H_

class State {
private:
	Music music;
	bool quitRequested;
	std::vector<GameObject*> objectArray ;
	Resources* recursos;
public:
	State();
	virtual ~State();
	bool QuitRequested ();
	void LoadAssets(SDL_Renderer* render,int w, int h);
	void Update(float dt,SDL_Renderer* render) ;
	void Render(SDL_Renderer* render);
	void AddObject(int mouseX,int mouseY,SDL_Renderer* render);
	Camera* camera;

};

#endif /* STATE_H_ */
