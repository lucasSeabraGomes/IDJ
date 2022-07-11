/*
 * Music.cpp
 *
 *  Created on: 21 de jun. de 2022
 *      Author: newlo
 */

#include "Music.h"

Music::Music() {
	this->music=nullptr;
}
Music::Music(std::string file,Resources* recursos) {
	// TODO Auto-generated constructor stub
	this->music=nullptr;
	this->Open(file,recursos);
}


bool Music::IsOpen (){
	if(this->music==nullptr){
		return false;
	}else{
		return true;
	}
}
void Music::Stop(int msToStop){
	Mix_FadeOutMusic(msToStop);
}
Music::~Music() {
	if(this->music!=nullptr){
		this->music=nullptr;
	}
	free(this);
}

void Music::Play(int times){
	if(this->IsOpen()){
		Mix_PlayMusic(this->music,times);
		cout<<"tocando musica\n";
	}
}

void Music::Open(std::string file,Resources* recursos){
	this->music = recursos->GetMusic(file);
}
