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
#include "GameObject.h"
#include "SDL_events.h"
#include "Sound.h"
#include "Resources.h"
#include "TileMap.h"
#include "Camera.h"
#include "Alien.h"
#include "CameraFollower.h"

#ifndef STATE_H_
#define STATE_H_

class State {
private:
	bool quitRequested;
	std::vector<std::shared_ptr<GameObject>> objectArray ;
	bool started;
	Music music;
public:
	State();
	virtual ~State();
	bool QuitRequested ();
	void LoadAssets(SDL_Renderer* render,int w, int h);
	void Update(float dt,SDL_Renderer* render) ;
	void Render(SDL_Renderer* render);
	std::weak_ptr< GameObject > GetObjectPtr(GameObject* go);
	std::weak_ptr< GameObject > AddObjectPtr(GameObject* go);
	void Start();

};

#endif /* STATE_H_ */
