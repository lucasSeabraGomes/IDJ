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
Music::Music(std::string file) {
	// TODO Auto-generated constructor stub
	this->music=nullptr;
	this->Open(file);
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
		Mix_FreeMusic(this->music);
		this->music=nullptr;
		cout<<"fechando musica\n";
	}
	free(this);
}

void Music::Play(int times){
	if(this->IsOpen()){
		Mix_PlayMusic(this->music,times);
		cout<<"tocando musica\n";
	}
}

void Music::Open(std::string file){
	Mix_Music* temp =Mix_LoadMUS(file.c_str());
	if(temp==nullptr){
			SDL_Log("Erro ao abrir musica: %s", SDL_GetError());
		}
	else{
		cout<<"musica aberta com sucesso\n";
		this->music=temp;
	}
}
