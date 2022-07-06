/*
 * Sprite.cpp
 *
 *  Created on: 21 de jun. de 2022
 *      Author: newlo
 */

#include "Sprite.h"
#include "GameObject.h"



Sprite::Sprite() {
	this->texture=nullptr;
	this->height=0;
	this->width=0;
}
Sprite::Sprite(GameObject* associated ){
		this->texture=nullptr;
		this->height=0;
		this->width=0;
		this->associated=associated;
}
Sprite::Sprite(string file,SDL_Renderer* render,GameObject* associated) {
	// TODO Auto-generated constructor stub
	this->texture=nullptr;
	this->height=0;
	this->width=0;
	this->associated=associated;
	this->Open(file,render);
}
Sprite::~Sprite() {
	if(this->texture!=nullptr){
		SDL_DestroyTexture(this->texture);
		cout<<"textura fechada com sucesso\n";
		this->texture=nullptr;
	}
	free(this);

}

void Sprite::Open(string file,SDL_Renderer* render){
	if(this->texture!=nullptr){
		SDL_DestroyTexture(this->texture);
		cout<<"textura substituida com sucesso\n";
	}
	this->texture=IMG_LoadTexture(render, file.c_str() );
	if (this->texture==nullptr) {
		    SDL_Log("Erro ao abrir imagem: %s", SDL_GetError());
		}
	else{
		SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);
		cout<<"textura aberta com sucesso\n";
	}

}
void Sprite::SetClip(int x, int y ,   int w, int h){
	this->clipRect.h=h;
	this->clipRect.w=w;
	this->clipRect.x=x;
	this->clipRect.y=y;
}
void Sprite::Render(SDL_Renderer* render){
	SDL_Rect dstrect;
	dstrect.h=this->associated->box.h;
	dstrect.w=this->associated->box.w;
	dstrect.x=this->associated->box.x;
	dstrect.y=this->associated->box.y;
	if(SDL_RenderCopy(render,this->texture,&this->clipRect,&dstrect)<0){
		 SDL_Log("Unable to render: %s", SDL_GetError());
	}
}
int Sprite::GetWidth(){
	return this->width;
}
int Sprite::GetHeight(){
	return this->height;
}
bool Sprite::IsOpen(){
	return this->texture!=nullptr;
}
bool Sprite::Is(string tipo){
	if(tipo.compare("Sprite")){
		return false;
	}
	else {
		return true;
	}
}
void Sprite::Update(float dt){

}
int Sprite::getW(){
	return this->width;
}
int Sprite::getH(){
	return this->height;
}
