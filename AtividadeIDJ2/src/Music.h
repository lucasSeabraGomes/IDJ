/*
 * Music.h
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


#ifndef MUSIC_H_
#define MUSIC_H_

class Music {
public:
	Music();
	virtual ~Music();
	Music( std::string file);
	void Play(int times);
	void Stop(int msToStop);
	void Open(std::string file);
	bool IsOpen ();
private:
	Mix_Music* music;
};

#endif /* MUSIC_H_ */
