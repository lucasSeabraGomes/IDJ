/*
 * Alien.cpp
 *
 *  Created on: 27 de jul. de 2022
 *      Author: newlo
 */

#include "Alien.h"
#include "Game.h"
Alien::Alien() {
	// TODO Auto-generated constructor stub

}
Alien::Alien(GameObject* associated ,int nMinions, Resources* recursos  ){
	this->associated=associated;
	Component* sprite= new Sprite("alien.png",Game::GetInstance().GetRenderer(),this->associated,recursos);
	this->associated->box.h=sprite->GetHeight();
	this->associated->box.w=sprite->GetWidth();
	this->associated->box.x=512;
	this->associated->box.y=300;
	sprite->SetClip(0, 0, this->associated->box.w, this->associated->box.h);
	associated->AddComponent(sprite);
	this->speed=Vec2( 500, 0 );
	this->hp=50;
	this->minionSpam=nMinions;
	this->associated->GetComponent("Sprite")->SetScaleX(1, 1);
}
Alien::~Alien() {
	// TODO Auto-generated destructor stub
	for(int i=0;i<int(this->minionArray.size());i++){
		this->minionArray[i]->RequestDelete();
	}
	if(this->minionArray.size()>0){
		this->minionArray.clear();
	}
}

void Alien::Start(){
	//adiciona minions
	for(int i=0;i<minionSpam;i++){
		this->minionArray.push_back(new GameObject());
		float angulo=(360/5)*i;
		Component* minion= new Minion(this->minionArray[i],this->associated,Game::GetInstance().recursos,angulo*PI / 180.0);
		this->minionArray[i]->AddComponent(minion);
		float size=rand() % 50 + 100;
		this->minionArray[i]->GetComponent("Sprite")->SetScaleX(size/100, size/100);
		Game::GetInstance().GetState()->AddObjectPtr(this->minionArray[i]);
	}
	this->started=true;
}
void Alien::Render(SDL_Renderer* render,Vec2 camera ){

}

void Alien::Update(float dt){
	if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) ){
		this->taskQueue.push(Action (SHOOT , InputManager::GetInstance().GetMouseX()-Game::GetInstance().camera->pos.x ,InputManager::GetInstance().GetMouseY()-Game::GetInstance().camera->pos.y  ));

	};
	if(InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON) ){
		this->taskQueue.push(Action (MOVE , InputManager::GetInstance().GetMouseX()-Game::GetInstance().camera->pos.x ,InputManager::GetInstance().GetMouseY()-Game::GetInstance().camera->pos.y  ));
	};
	if(this->taskQueue.size()>0){
		if(this->taskQueue.front().type==SHOOT){
			int shoter=0;
			int distance=3000;
			for(int i=0;i<int(this->minionArray.size());i++){
				if(Vec2(this->minionArray[i]->box.x,this->minionArray[i]->box.y).GetDistance(this->taskQueue.front().pos)<=distance){
					distance=Vec2(this->minionArray[i]->box.x,this->minionArray[i]->box.y).GetDistance(this->taskQueue.front().pos);
					shoter=i;
				}
			}
			this->minionArray[shoter]->GetComponent("Minion")->Shoot(this->taskQueue.front().pos);
			this->taskQueue.front().~Action();
			this->taskQueue.pop();
		}
		else if(this->taskQueue.front().type==MOVE){
			if(this->associated->box.Contains(this->taskQueue.front().pos.x, this->taskQueue.front().pos.y)){
				this->taskQueue.front().~Action();
				this->taskQueue.pop();
			}
			else{
				Vec2 move= Vec2( 500, 0 ).GetRotated(this->associated->box.GetCenter().GetAngle(this->taskQueue.front().pos) );
				Vec2 objPos = (move*(dt/1000)).Subtract(this->associated->box.x,this->associated->box.y );
				this->associated->box.x=objPos.x;
				this->associated->box.y=objPos.y;
			}
		}
	};
	//faz o alien rodar
	this->associated->angleDeg=this->associated->angleDeg-1;
	if(this->associated->angleDeg<-360){
		this->associated->angleDeg=this->associated->angleDeg+360;
	}
	if(this->hp<=0){
		this->associated->RequestDelete();
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
