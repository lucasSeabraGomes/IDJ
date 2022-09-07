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
#include "PenguinBody.h"
#ifndef STATE_H_
#define STATE_H_

class State {
protected:
	bool quitRequested;
	bool popRequested;
	std::vector<std::shared_ptr<GameObject>> objectArray ;
	bool started;
	Music music;
public:
	State();
	virtual ~State();
	bool QuitRequested ();
	void virtual LoadAssets();
	void virtual Update(float dt) ;
	void virtual Render();
	void virtual Start();
	void virtual Pause ();
	void virtual Resume ();
	std::weak_ptr< GameObject > GetObjectPtr(GameObject* go);
	std::weak_ptr< GameObject > AddObjectPtr(GameObject* go);
	void StartArray ();
	void UpdateArray ( float dt);
	void RenderArray ();

	bool PopRequested ();
};

#endif /* STATE_H_ */
