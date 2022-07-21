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
Sound::Sound(string file,GameObject* associated,Resources* recursos) {
	// TODO Auto-generated constructor stub
	this->chunk=nullptr;
	this->Open(file,recursos);
	this->associated=associated;
}
Sound::~Sound() {
	if(this->chunk!=nullptr){
		 this->chunk=nullptr;
	}
	// TODO Auto-generated destructor stub
}
void Sound::Play(int times){
		this->chanel=Mix_PlayChannel(-1,this->chunk,times);
}
void Sound::Stop(){
	Mix_HaltChannel(this->chanel);
}
void Sound::Open(string file,Resources* recursos) {
	this->chunk=recursos->GetSound(file);
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
