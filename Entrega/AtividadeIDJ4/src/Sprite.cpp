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
Sprite::Sprite(string file,SDL_Renderer* render,GameObject* associated,Resources* recursos) {
	// TODO Auto-generated constructor stub
	this->texture=nullptr;
	this->height=0;
	this->width=0;
	this->associated=associated;
	this->Open(file,render,recursos);
	SDL_QueryTexture(this->texture, NULL, NULL, &this->width, &this->height);
}
Sprite::~Sprite() {
	if(this->texture!=nullptr){
		this->texture=nullptr;
	}
	free(this);

}

void Sprite::Open(string file,SDL_Renderer* render,Resources* recursos){
	this->texture=recursos->GetImage(file, render);
}
void Sprite::SetClip(int x, int y ,   int w, int h){
	this->clipRect.h=h;
	this->clipRect.w=w;
	this->clipRect.x=x;
	this->clipRect.y=y;
}
void Sprite::Render(SDL_Renderer* render,Vec2 camera){
	SDL_Rect dstrect;
	dstrect.h=this->associated->box.h;
	dstrect.w=this->associated->box.w;
	dstrect.x=this->associated->box.x+camera.x;
	dstrect.y=this->associated->box.y+camera.y;
	if(SDL_RenderCopy(render,this->texture,&this->clipRect,&dstrect)<0){
		 SDL_Log("Unable to render: %s", SDL_GetError());
	}
}
void Sprite::Render(SDL_Renderer* render,SDL_Rect dstrect){
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
