/*
 * PenguinCannon.cpp
 *
 *  Created on: 8 de ago. de 2022
 *      Author: newlo
 */

#include "PenguinCannon.h"
#include "Game.h"
PenguinCannon::PenguinCannon() {
	// TODO Auto-generated constructor stub

}
PenguinCannon::PenguinCannon(GameObject* associated,GameObject* penguinBody) {
	// TODO Auto-generated constructor stub
	this->associated=associated;
	this->pbody=penguinBody;
	this->angle=0;
	this->started=false;
	Component* sprite= new Sprite("cubngun.png",Game::GetInstance().GetRenderer(),this->associated,Game::GetInstance().recursos);
	this->associated->box.h=sprite->GetHeight();
	this->associated->box.w=sprite->GetWidth();
	Vec2 centro=this->pbody->box.GetCenter();
	this->associated->box.x=centro.x-(this->associated->box.w/2);
	this->associated->box.y=centro.y-(this->associated->box.h/2);
	sprite->SetClip(0, 0, this->associated->box.w, this->associated->box.h);
	associated->AddComponent(sprite);
	Component* colider=new Collider(associated);
	associated->AddComponent(colider);
	this->timer=Timer();
}

PenguinCannon::~PenguinCannon() {
	// TODO Auto-generated destructor stub
	this->associated=nullptr;
	this->pbody=nullptr;
}

bool PenguinCannon::Is(string tipo){
	if(tipo.compare("PenguinCannon")){
			return false;
		}else{
			return true;
		}
}
void PenguinCannon::Update ( float dt){
	this->timer.Update(dt);
	PenguinBody* body=(PenguinBody*)this->pbody->GetComponent("PenguinBody");
	if(body!=nullptr){
		if(PenguinBody::player==nullptr){
			this->associated->RequestDelete();
		}
	}else{
		this->associated->RequestDelete();
	}
	Vec2 mouse=Vec2(InputManager::GetInstance().GetMouseX()-Game::GetInstance().camera->pos.x,InputManager::GetInstance().GetMouseY()-Game::GetInstance().camera->pos.y);
	Vec2 centro=this->pbody->box.GetCenter();
	this->associated->box.x=centro.x-(this->associated->box.w/2);
	this->associated->box.y=centro.y-(this->associated->box.h/2);
	this->angle=this->associated->box.GetCenter().GetAngle(mouse);
	this->associated->angleDeg=double((this->angle*180/3.14)+180);
	if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) and this->timer.Get()>=1000 ){
		this->Shoot();
		this->timer.Restart();
	};
}
void PenguinCannon::Render(SDL_Renderer* render,Vec2 camera ){

}
void PenguinCannon::Shoot (){
	GameObject* shoot= new GameObject();
	Component* bulet= new Bullet(shoot,this->angle  , 250, 10,300, "penguinbullet.png",4,false);
	shoot->AddComponent(bulet);
	shoot->angleDeg=double(angle*180/3.14)+180;
	Game::GetInstance().GetState()->AddObjectPtr(shoot);
	Vec2 pos=Vec2(this->associated->box.w/2,0).GetRotated(this->angle).Subtract(this->associated->box.GetCenter().x,this->associated->box.GetCenter().y);
	shoot->box.x=pos.x-20;
	shoot->box.y=pos.y-5;
}
