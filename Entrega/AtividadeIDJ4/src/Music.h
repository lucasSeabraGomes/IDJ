/*
 * Music.h
 *
 *  Created on: 21 de jun. de 2022
 *      Author: newlo
 */

#include <stdlib.h>
#include "Resources.h"


#ifndef MUSIC_H_
#define MUSIC_H_

class Music {
public:
	Music();
	virtual ~Music();
	Music( std::string file,Resources* recursos);
	void Play(int times);
	void Stop(int msToStop);
	void Open(std::string file,Resources* recursos);
	bool IsOpen ();
private:
	Mix_Music* music;
};

#endif /* MUSIC_H_ */
