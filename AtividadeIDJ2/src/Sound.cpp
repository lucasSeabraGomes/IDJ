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
	this->MaxPlays=1;
}
Sound::Sound(string file,GameObject* associated) {
	// TODO Auto-generated constructor stub
	this->chunk=nullptr;
	this->Open(file);
	this->associated=associated;
	this->MaxPlays=1;
}
Sound::~Sound() {
	if(this->chunk!=nullptr){
		 Mix_FreeChunk(this->chunk);
		 this->chunk=nullptr;
	}
	// TODO Auto-generated destructor stub
}
void Sound::Play(int times){
	if(this->MaxPlays>0){
		this->MaxPlays=this->MaxPlays-1;
		this->chanel=Mix_PlayChannel(-1,this->chunk,times);
	}
}
void Sound::Stop(){
	Mix_HaltChannel(this->chanel);
}
void Sound::Open(string file) {
	this->chunk=Mix_LoadWAV(file.c_str());
	if(this->chunk==nullptr){
		cout<<"erro ao abrir som"<<SDL_GetError();
	}
}
bool Sound::Is(string type){
	if(type.compare("Sound")){
		return false;
	}
	else{
		return true;
	}
}
bool Sound::IsPlaying(){
	if(Mix_Playing(this->chanel)){
		return true;
	}else{
		return false;
	}
}
