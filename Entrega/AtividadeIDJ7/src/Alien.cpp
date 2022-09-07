/*
 * Alien.cpp
 *
 *  Created on: 27 de jul. de 2022
 *      Author: newlo
 */

#include "Alien.h"
#include "Game.h"
#include "PenguinBody.h"
int Alien::alienCount=0;
Alien::Alien() {
	// TODO Auto-generated constructor stub

}
Alien::Alien(GameObject* associated ,int nMinions, Resources* recursos  ){
	this->associated=associated;
	Component* sprite= new Sprite("alien.png",Game::GetInstance()->GetRenderer(),this->associated,recursos);
	this->associated->box.h=sprite->GetHeight();
	this->associated->box.w=sprite->GetWidth();
	this->associated->box.x=512;
	this->associated->box.y=300;
	sprite->SetClip(0, 0, this->associated->box.w, this->associated->box.h);
	associated->AddComponent(sprite);
	this->speed=Vec2( 500, 0 );
	this->hp=50;
	this->minionSpam=nMinions;
	Component* colider=new Collider(associated);
	associated->AddComponent(colider);
	Alien::alienCount=Alien::alienCount+1;
	this->restTimer=Timer();
	this->restTimer.Restart();
	this->state=MOVE;
}
Alien::~Alien() {
	// TODO Auto-generated destructor stub
	for(int i=0;i<int(this->minionArray.size());i++){
		this->minionArray[i]->RequestDelete();
	}
	if(this->minionArray.size()>0){
		this->minionArray.clear();
	}
	Alien::alienCount=Alien::alienCount-1;
}

void Alien::Start(){
	//adiciona minions
	for(int i=0;i<minionSpam;i++){
		this->minionArray.push_back(new GameObject());
		float angulo=(360/5)*i;
		Component* minion= new Minion(this->minionArray[i],this->associated,Game::GetInstance()->recursos,angulo*PI / 180.0);
		this->minionArray[i]->AddComponent(minion);
		float size=rand() % 50 + 100;
		this->minionArray[i]->GetComponent("Sprite")->SetScaleX(size/100, size/100);
		Game::GetInstance()->GetState()->AddObjectPtr(this->minionArray[i]);
	}
	this->started=true;
}
void Alien::Render(SDL_Renderer* render,Vec2 camera ){

}

void Alien::Update(float dt){
	if(this->state==SHOOT){
		//atualiza a localização do player para atirar na posição mais atual
		if(PenguinBody::player!=nullptr){
			if(PenguinBody::player->associated!=nullptr){
				this->destination=PenguinBody::player->associated->box.GetCenter();
			}
		}
		int shoter=0;
		int distance=3000;
		for(int i=0;i<int(this->minionArray.size());i++){
			if(Vec2(this->minionArray[i]->box.x,this->minionArray[i]->box.y).GetDistance(this->destination)<=distance){
				distance=Vec2(this->minionArray[i]->box.x,this->minionArray[i]->box.y).GetDistance(this->destination);
				shoter=i;
			}
		}
		this->minionArray[shoter]->GetComponent("Minion")->Shoot(this->destination);
		this->state=MOVE;
		this->restTimer.Restart();
	}
	if(this->state==MOVE ){
		//descansa e atualiza a localização do player
		if(this->restTimer.Get()<1000){
			if(PenguinBody::player!=nullptr){
				if(PenguinBody::player->associated!=nullptr){
					this->destination=PenguinBody::player->associated->box.GetCenter();
				}
			}
			this->restTimer.Update(dt);
		}else{
			//muda o status de mover para atirar
			if(this->associated->box.Contains(this->destination.x, this->destination.y)){
				this->state=SHOOT;
				this->restTimer.Restart();
			}
			else{
				Vec2 move= Vec2( 200, 0 ).GetRotated(this->associated->box.GetCenter().GetAngle(this->destination) );
				Vec2 objPos = (move*(dt/1000)).Subtract(this->associated->box.x,this->associated->box.y );
				this->associated->box.x=objPos.x;
				this->associated->box.y=objPos.y;
			}
		}
	}

	//faz o alien rodar
	this->associated->angleDeg=this->associated->angleDeg-1;
	if(this->associated->angleDeg<-360){
		this->associated->angleDeg=this->associated->angleDeg+360;
	}
	if(this->hp<=0){
		this->associated->RequestDelete();
		GameObject* explosao=new GameObject();
		Component* sprite= new Sprite("aliendeath.png",Game::GetInstance()->GetRenderer(),explosao,Game::GetInstance()->recursos,4,250,1);
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

bool Alien::Is(string tipo){
	if(tipo.compare("Alien")){
			return false;
		}else{
			return true;
		}
}
bool Alien::Damage(int damage){
	this->hp=this->hp-damage;
	if(this->hp<=0){
		return true;
	}
	else {
		return false;
	}
}
void Alien::NotifyCollision(GameObject*other){
	Bullet* bulet=(Bullet*)other->GetComponent("Bullet");
		if(bulet!=nullptr){
			if(!bulet->targetsPlayer){
				this->hp=this->hp-bulet->GetDamage();
				bulet->associated->RequestDelete();
			}
		}
}
