/*
 * Resources.cpp
 *
 *  Created on: 7 de jul. de 2022
 *      Author: newlo
 */

#include "Resources.h"

Resources::Resources() {
	// TODO Auto-generated constructor stub

}

Resources::~Resources() {
	this->ClearImages();
	this->ClearMusics();
	this->ClearSounds();
	// TODO Auto-generated destructor stub
}

SDL_Texture* Resources::GetImage( std::string file,SDL_Renderer* render){
	 std::unordered_map<std::string, SDL_Texture*>::const_iterator got = this->imageTable.find (file);
	 if ( got == this->imageTable.end() ){
		 SDL_Texture* temporario =IMG_LoadTexture(render, file.c_str() );
		 if (temporario==nullptr) {
		 		    SDL_Log("Erro ao abrir imagem: %s", SDL_GetError());
		 		    return nullptr;
		 		}
		 	else{
		 		cout<<"textura criada\n";
		 		this->imageTable.insert({file,temporario});
		 		return temporario;
		 	}
	 }
	 else{
		 cout<<"textura verificada\n";
		 return got->second;
	 }
}
Mix_Music* Resources::GetMusic( std::string file){
	 std::unordered_map<std::string, Mix_Music*>::const_iterator got = this->musicTable.find (file);
	 if ( got == this->musicTable.end() ){
		 Mix_Music* temporario=Mix_LoadMUS(file.c_str());
		 if (temporario==nullptr) {
		 		    SDL_Log("Erro ao abrir imagem: %s", SDL_GetError());
		 		    return nullptr;
		 		}
		 	else{
		 		this->musicTable.insert({file,temporario});
		 		return temporario;
		 	}
	 }
	 else{
		 return got->second;
	 }
}
Mix_Chunk* Resources::GetSound ( std::string file){
	 std::unordered_map<std::string, Mix_Chunk*>::const_iterator got = this->soundTable.find (file);
	 if ( got == this->soundTable.end() ){
		 Mix_Chunk* temporario=Mix_LoadWAV(file.c_str());
		 if (temporario==nullptr) {
		 		    SDL_Log("Erro ao abrir imagem: %s", SDL_GetError());
		 		    return nullptr;
		 		}
		 	else{
		 		this->soundTable.insert({file,temporario});
		 		return temporario;
		 	}
	 }
	 else{
		 return got->second;
	 }
}
void Resources::ClearImages (){
	for (auto& it: this->imageTable) {
		    // Do stuff
		cout<<"textura fechada com sucesso\n";
		SDL_DestroyTexture(it.second);
		}
	this->imageTable.clear();
}
void Resources::ClearMusics (){
	for (auto& it: this->musicTable) {
			    // Do stuff
		cout<<"musica fechada com sucesso\n";
			Mix_FreeMusic(it.second);
			}
		this->musicTable.clear();
}
void Resources::ClearSounds (){
	for (auto& it: this->soundTable) {
			    // Do stuff
		cout<<"som fechado com sucesso\n";
			Mix_FreeChunk(it.second);
			}
		this->soundTable.clear();
}
