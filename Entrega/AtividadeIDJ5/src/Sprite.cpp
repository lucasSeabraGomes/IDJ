/*
 * Sprite.cpp
 *
 *  Created on: 21 de jun. de 2022
 *      Author: newlo
 */

#include "Sprite.h"
#include "GameObject.h"
#include "Game.h"


Sprite::Sprite() {
	this->texture=nullptr;
	this->height=0;
	this->width=0;
	this->scale=new Vec2(1,1);
}
Sprite::Sprite(GameObject* associated ):Sprite(){
		this->associated=associated;
}
Sprite::Sprite(string file,SDL_Renderer* render,GameObject* associated,Resources* recursos):Sprite() {
	// TODO Auto-generated constructor stub
	this->associated=associated;
	this->Open(file,render,recursos);
}
Sprite::~Sprite() {
	if(this->texture!=nullptr){
		this->texture=nullptr;
	}
	if(this->scale!=nullptr){
		this->scale=nullptr;
	}
	free(this);

}

void Sprite::Open(string file,SDL_Renderer* render,Resources* recursos){
	this->texture=recursos->GetImage(file, render);
	SDL_QueryTexture(this->texture, NULL, NULL, &this->width, &this->height);
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
	double ang =0;
	if(this->associated!=nullptr){
		ang=this->associated->angleDeg;
	}
	if(SDL_RenderCopyEx(render,this->texture,&this->clipRect,&dstrect,ang,nullptr,SDL_FLIP_NONE)){
		 SDL_Log("Unable to render: %s", SDL_GetError());
	}
}
void Sprite::Render(SDL_Renderer* render,SDL_Rect dstrect){
	double ang =0;
	if(this->associated!=nullptr){
		ang=this->associated->angleDeg;
	}
	if(SDL_RenderCopyEx(render,this->texture,&this->clipRect,&dstrect,ang,nullptr,SDL_FLIP_NONE)<0){
		 SDL_Log("Unable to render: %s", SDL_GetError());
	}
}
int Sprite::GetWidth(){
	return this->width*this->scale->x;
}
int Sprite::GetHeight(){
	return this->height*this->scale->y;
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
Vec2 Sprite::GetScale (){
	return *this->scale;
}
void Sprite::SetScaleX (float scaleX,float  scaleY){
	this->scale->x=scaleX;
	this->scale->y=scaleY;
	if(this->associated!=nullptr){
		this->associated->box.x=this->associated->box.x-(this->associated->box.w*(scaleX-1)/2);
		this->associated->box.y=this->associated->box.y-(this->associated->box.h*(scaleY-1)/2);
		this->associated->box.h=this->associated->box.h*scaleY;
		this->associated->box.w=this->associated->box.w*scaleX;
	}
}
