/*
 * Bullet.cpp
 *
 *  Created on: 1 de ago. de 2022
 *      Author: newlo
 */

#include "Bullet.h"
#include "Game.h"
Bullet::Bullet() {
	// TODO Auto-generated constructor stub

}

Bullet::Bullet(GameObject* associated,  float  angle , float  speed, int damage,float maxDistance,    std::string      sprite) {
	// TODO Auto-generated constructor stub
	this->associated=associated;
	this->damage=damage;
	this->distanceLeft=maxDistance;
	this->speed=speed;
	this->angle=angle;
	Component* image= new Sprite(sprite,Game::GetInstance().GetRenderer(),this->associated,Game::GetInstance().recursos);
	SDL_QueryTexture(Game::GetInstance().recursos->GetImage(sprite, Game::GetInstance().GetRenderer()),  NULL, NULL, &this->associated->box.w, &this->associated->box.h);
	image->SetClip(0, 0, this->associated->box.w, this->associated->box.h);
	associated->AddComponent(image);
}
Bullet::~Bullet() {
	// TODO Auto-generated destructor stub
}

void Bullet::Render(SDL_Renderer* render,Vec2 camera ){

}
void Bullet::Update(float dt){
	Vec2 Move=Vec2(this->speed,0).GetRotated(this->angle)*(dt/1000);
	Vec2 objPos = Move.Subtract(this->associated->box.x,this->associated->box.y );
	this->distanceLeft=this->distanceLeft-Vec2(this->associated->box.x,this->associated->box.y ).GetDistance(objPos);
	this->associated->box.x=objPos.x;
	this->associated->box.y=objPos.y;
	if(this->distanceLeft<=0){
		this->associated->RequestDelete();
	}
}
bool Bullet::Is(string tipo){
	if(tipo.compare("Bullet")){
			return false;
		}else{
			return true;
		}
}
int Bullet::GetDamage (){
	return this->damage;
}
