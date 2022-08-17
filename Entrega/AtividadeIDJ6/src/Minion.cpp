/*
 * Minion.cpp
 *
 *  Created on: 27 de jul. de 2022
 *      Author: newlo
 */

#include "Minion.h"
#include "Game.h"
Minion::Minion() {
	// TODO Auto-generated constructor stub

}
Minion::Minion (GameObject* associated, GameObject* alienCenter,Resources* recursos , float arcOffsetDeg){
	this->associated=associated;
	this->alienCenter=alienCenter;
	this->arc=arcOffsetDeg;
	Vec2 center=this->alienCenter->box.GetCenter();
	Vec2 pos=Vec2(100,0).GetRotated(arcOffsetDeg).Subtract(center.x,center.y);
	this->associated->box.x=center.x+200;
	this->associated->box.y=center.y;
	Component* sprite= new Sprite("minion.png",Game::GetInstance().GetRenderer(),this->associated,recursos);
	this->associated->box.h=sprite->GetHeight();
	this->associated->box.w=sprite->GetWidth();
	sprite->SetClip(0, 0, this->associated->box.w, this->associated->box.h);
	associated->AddComponent(sprite);
	Component* colider=new Collider(associated);
	associated->AddComponent(colider);
}
Minion::~Minion() {
	// TODO Auto-generated destructor stub
}

void Minion::Render(SDL_Renderer* render,Vec2 camera ){

}
void Minion::Update(float dt){
	this->arc=this->arc+0.05;
	if(this->arc>360){
		this->arc=this->arc-360;
	}
	Vec2 center=this->alienCenter->box.GetCenter();;
	Vec2 pos=Vec2(100,0).GetRotated(this->arc).Soma(center.x-(this->associated->box.w/2),center.y-(this->associated->box.h/2));
	this->associated->box.x=pos.x;
	this->associated->box.y=pos.y;
	//faz o minion rodar
	this->associated->angleDeg=double((this->associated->box.GetCenter().GetAngle(center)*180/PI)-90);
	if(this->alienCenter->IsDead()){
		GameObject* explosao=new GameObject();
		Component* sprite= new Sprite("miniondeath.png",Game::GetInstance().GetRenderer(),explosao,Game::GetInstance().recursos,4,250,1);
		explosao->box.h=sprite->GetHeight();
		explosao->box.w=sprite->GetWidth();
		explosao->box.x=this->associated->box.x;
		explosao->box.y=this->associated->box.y;
		sprite->SetClip(0, 0, explosao->box.w, explosao->box.h);
		explosao->AddComponent(sprite);
		Game::GetInstance().GetState()->AddObjectPtr(explosao);
	}
}

bool Minion::Is(string tipo){
	if(tipo.compare("Minion")){
			return false;
		}else{
			return true;
		}
}
void Minion::Shoot(Vec2 target){

	float angle=Vec2(this->associated->box.x,this->associated->box.y).GetAngle(target);
	GameObject* shoot= new GameObject();
	shoot->box.x=this->associated->box.x;
	shoot->box.y=this->associated->box.y;
	Component* bulet= new Bullet(shoot, angle , 250, 10,400, "minionbullet2.png",3);
	shoot->AddComponent(bulet);
	shoot->angleDeg=double(angle*180/3.14)+180;
	Game::GetInstance().GetState()->AddObjectPtr(shoot);
}
