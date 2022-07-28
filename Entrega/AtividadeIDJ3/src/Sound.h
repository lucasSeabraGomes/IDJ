/*
 * Sound.h
 *
 *  Created on: 2 de jul. de 2022
 *      Author: newlo
 */
#include "Music.h"
#include "Component.h"
#include "Resources.h"
#ifndef SRC_SOUND_H_
#define SRC_SOUND_H_

class Sound: public Component {
public:
	Sound(GameObject* associated);
	Sound(string file,GameObject* associated,Resources* recursos);
	virtual ~Sound();
	void Play(int times);
	void Stop();
	void Open ( string file,Resources* recursos);
	bool IsOpen ();
	bool Is(string type) ;
	bool IsPlaying();
private:
	Mix_Chunk* chunk;
	int chanel;

};

#endif /* SRC_SOUND_H_ */
