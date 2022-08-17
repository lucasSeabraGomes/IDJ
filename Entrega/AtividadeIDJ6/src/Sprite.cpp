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
	this->timeElapsed=0;
	this->secondsToSelfDestruct=-1;
	this->selfDestructCount=Timer();
}
Sprite::Sprite(GameObject* associated ):Sprite(){
		this->associated=associated;
}
Sprite::Sprite(string file,SDL_Renderer* render,GameObject* associated,Resources* recursos,int frameCount,float frameTime,float selfDestruc):Sprite() {
	// TODO Auto-generated constructor stub
	this->associated=associated;
	this->frameCount=frameCount;
	this->frameTime=frameTime;
	this->currentFrame=0;
	this->Open(file,render,recursos);
	this->secondsToSelfDestruct=selfDestruc;
	this->selfDestructCount=Timer();
	this->selfDestructCount.Restart();
}
Sprite::~Sprite() {
	if(this->texture!=nullptr){
		this->texture=nullptr;
	}
	if(this->scale!=nullptr){
		this->scale=nullptr;
	}

}

void Sprite::Open(string file,SDL_Renderer* render,Resources* recursos){
	this->texture=recursos->GetImage(file, render);
	SDL_QueryTexture(this->texture, NULL, NULL, &this->width, &this->height);
	if(this->frameCount>1){
		this->width=(this->width)/(this->frameCount);
	}
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
	if(SDL_RenderCopy(render,this->texture,&this->clipRect,&dstrect)<0){
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
	this->timeElapsed=this->timeElapsed+dt;
	if(this->frameCount>1){
		if(this->timeElapsed>this->frameTime){
			this->timeElapsed=0;
			this->currentFrame=this->currentFrame+1;
			if(this->currentFrame==this->frameCount){
				this->currentFrame=0;
			}
			this->SetClip(this->clipRect.w*this->currentFrame, this->clipRect.y, this->clipRect.w, this->clipRect.h);
		}
	}
	if(this->secondsToSelfDestruct>0){
		this->selfDestructCount.Update(dt);
		if(this->secondsToSelfDestruct*1000<=this->selfDestructCount.Get()){
			if(this->associated!=nullptr)
			{
				this->associated->RequestDelete();
			}
		}
	}
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

void Sprite::SetFrame(int frame){
	if(this->frameCount>1 and this->frameCount>=frame){
		if(this->timeElapsed>this->frameTime){
			this->currentFrame=frame;
			if(this->currentFrame==this->frameCount){
				this->currentFrame=0;
			}
			this->SetClip(this->clipRect.w*this->currentFrame, this->clipRect.y, this->clipRect.w, this->clipRect.h);
		}
	}
}

void Sprite::SetFrameCount  (int frameCount ){
	this->frameCount=frameCount;
}
void Sprite::SetFrameTime  (int frameTime ){
	this->frameTime=frameTime;
}
