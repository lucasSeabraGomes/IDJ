/*
 * Resources.h
 *
 *  Created on: 7 de jul. de 2022
 *      Author: newlo
 */

#ifndef SRC_RESOURCES_H_
#define SRC_RESOURCES_H_
#include <iostream>
using namespace std;
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "SDL_include.h"
#include <stdlib.h>
#include <unordered_map>
class Resources {
public:
	Resources();
	virtual ~Resources();
	SDL_Texture* GetImage( std::string file,SDL_Renderer* render);
	void ClearImages ();
	Mix_Music*  GetMusic( std::string file);
	void ClearMusics ();
	Mix_Chunk* GetSound ( std::string file);
	void  ClearSounds ();
private:
	std::unordered_map<std::string, SDL_Texture*> imageTable;
	std::unordered_map<std::string, Mix_Music*> musicTable;
	std::unordered_map<std::string, Mix_Chunk*> soundTable;
};

#endif /* SRC_RESOURCES_H_ */
