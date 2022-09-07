/*
 * PenguinBody.cpp
 *
 *  Created on: 8 de ago. de 2022
 *      Author: newlo
 */

#include "PenguinBody.h"
#include "Game.h"
PenguinBody* PenguinBody::player;
PenguinBody::PenguinBody() {
	// TODO Auto-generated constructor stub

}

PenguinBody::~PenguinBody() {
	// TODO Auto-generated destructor stub
	this->associated=nullptr;
	this->player=nullptr;
}
PenguinBody::PenguinBody (GameObject* associated){
	this->associated=associated;
	this->angle=0;
	this->hp=50;
	this->linearSpeed=0;
	this->maxSpeed=50;
	this->minSpeed=-50;
	Component* sprite= new Sprite("penguin.png",Game::GetInstance()->GetRenderer(),this->associated,Game::GetInstance()->recursos);
	this->associated->box.h=sprite->GetHeight();
	this->associated->box.w=sprite->GetWidth();
	this->associated->box.x=704;
	this->associated->box.y=640;
	sprite->SetClip(0, 0, this->associated->box.w, this->associated->box.h);
	associated->AddComponent(sprite);
	PenguinBody::player=this;
	Component* colider=new Collider(associated);
	associated->AddComponent(colider);
}
bool PenguinBody::Is(string tipo){
	if(tipo.compare("PenguinBody")){
			return false;
		}else{
			return true;
		}
}
void PenguinBody::Update ( float dt){
	if(InputManager::GetInstance().IsKeyDown(SDLK_a) or InputManager::GetInstance().KeyPress(SDLK_a)or InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY) or InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY)){
		this->angle=this->angle-10;
		this->associated->angleDeg=double(this->angle);
		if(this->angle<0){
			this->angle=this->angle+360;
		}
	}
	if(InputManager::GetInstance().IsKeyDown(SDLK_d) or InputManager::GetInstance().KeyPress(SDLK_d)or InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY) or InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY)){
		this->angle=this->angle+10;
		this->associated->angleDeg=double(this->angle);
		if(this->angle>360){
			this->angle=this->angle-360;

		}
	}
	if(this->linearSpeed<=this->maxSpeed and(InputManager::GetInstance().IsKeyDown(SDLK_w) or InputManager::GetInstance().KeyPress(SDLK_w)or InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY) or InputManager::GetInstance().KeyPress(UP_ARROW_KEY))){
		this->linearSpeed=this->linearSpeed+1;
	}
	if(this->linearSpeed>=this->minSpeed and(InputManager::GetInstance().IsKeyDown(SDLK_s) or InputManager::GetInstance().KeyPress(SDLK_s)or InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY) or InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY))){
		this->linearSpeed=this->linearSpeed-1;
	}
	Vec2 pos=Vec2(this->linearSpeed,0).GetRotated(this->angle*PI / 180.0).Soma(this->associated->box.x, this->associated->box.y);
	this->associated->box.x=pos.x;
	this->associated->box.y=pos.y;
	if(this->associated->box.x<0 ){
			this->associated->box.x=0;
		}if(this->associated->box.x>1280){
			this->associated->box.x=1280;
		}
		if(this->associated->box.y>1280){
				this->associated->box.y=1280;
		}
		if(this->associated->box.y<0 ){
			this->associated->box.y=0;
		}
	if(this->hp<=0){
		Game::GetInstance()->camera->Unfollow();
		this->associated->RequestDelete();
		PenguinBody::player=nullptr;
		//gera a explosão
		GameObject* explosao=new GameObject();
		Component* sprite= new Sprite("penguindeath.png",Game::GetInstance()->GetRenderer(),explosao,Game::GetInstance()->recursos,5,200,1);
		explosao->box.h=sprite->GetHeight();
		explosao->box.w=sprite->GetWidth();
		explosao->box.x=this->associated->box.x;
		explosao->box.y=this->associated->box.y;
		sprite->SetClip(0, 0, explosao->box.w, explosao->box.h);
		explosao->AddComponent(sprite);
		Component* sound= new Sound("boom.wav",explosao,Game::GetInstance()->recursos);
		explosao->AddComponent(sound);
		((Sound*)sound)->Play(0);
		Game::GetInstance()->GetState()->AddObjectPtr(explosao);
	}
}
void PenguinBody::Render(SDL_Renderer* render,Vec2 camera ){

}
void PenguinBody::Start(){
	//inicializa o canon
	this->pcannon=new GameObject();
	Component* canon=new PenguinCannon(this->pcannon,associated);
	this->pcannon->AddComponent(canon);
	Game::GetInstance()->GetState()->AddObjectPtr(this->pcannon);
}
void PenguinBody::NotifyCollision(GameObject*other){
	Bullet* bulet=(Bullet*)other->GetComponent("Bullet");
	if(bulet!=nullptr){
		if(bulet->targetsPlayer){
			this->hp=this->hp-bulet->GetDamage();
			bulet->associated->RequestDelete();
		}
	}
}
