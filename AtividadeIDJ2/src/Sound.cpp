/*
 * Sound.cpp
 *
 *  Created on: 2 de jul. de 2022
 *      Author: newlo
 */

#include "Sound.h"
#include "GameObject.h"
Sound::Sound(GameObject* associated) {
	// TODO Auto-generated constructor stub
	this->chunk=nullptr;
	this->associated=associated;
}
Sound::Sound(string file,GameObject* associated) {
	// TODO Auto-generated constructor stub
	this->chunk=nullptr;
	this->Open(file);
	this->associated=associated;
}
Sound::~Sound() {
	if(this->chunk!=nullptr){
		 Mix_FreeChunk(this->chunk);
		 this->chunk=nullptr;
	}
	// TODO Auto-generated destructor stub
}
void Sound::Play(int times){
	Mix_PlayChannel(this->chanel,this->chunk,times);
}
void Sound::Stop(){
	Mix_HaltChannel(this->chanel);
}
void Sound::Open(string file) {
	this->chunk=Mix_LoadWAV(file.c_str());
}
bool Sound::Is(string type){
	return type.compare("Sound");
}
