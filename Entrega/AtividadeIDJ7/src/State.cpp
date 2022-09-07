/*
 * State.cpp
 *
 *  Created on: 21 de jun. de 2022
 *      Author: newlo
 */

#include "State.h"
#include "Game.h"
#include "Collision.cpp"
State::State() {
	this->quitRequested=false;
	this->started=false;
	this->popRequested=false;
	this->music = Music();
}

State::~State() {
	cout<<"removendo state1\n";
	this->music.~Music();
	cout<<"removendo state2\n";
	for(int i=0;i<int(this->objectArray.size());i++){
					this->objectArray[i]->~GameObject();
	}
	cout<<"removendo state3\n";
		if(this->objectArray.size()>0){
			 this->objectArray.clear();
		}
}
//seta a musica da tela e o background na janela de w=width e h=heigth
void State::LoadAssets(){


}
void State::Pause (){

}
void State::Resume (){

}
void State::UpdateArray ( float dt){
	for(int i=0;i<int(this->objectArray.size());i++){
			this->objectArray[i]->Update(dt);

		}
		for(int i=0;i<int(this->objectArray.size());i++){
				if(this->objectArray[i]->IsDead()){
					this->objectArray[i]->~GameObject();
					this->objectArray.erase(this->objectArray.begin()+i);
				}
			}
}
void State::Update(float dt){

}


void State::RenderArray (){
	for(int i=0;i<int(this->objectArray.size());i++){
		this->objectArray[i]->Render(Game::GetInstance()->GetRenderer(),Game::GetInstance()->camera->pos);
	}
}
void State::Render (){
	this->RenderArray();
}
bool State::QuitRequested (){
	return this->quitRequested;
}

void State::StartArray (){
	for(int i=0;i<int(this->objectArray.size());i++){
		this->objectArray[i]->Start();
	}
}
void State::Start(){
	if(started){
		return;
	}
	this->LoadAssets();
	this->StartArray();
	started=true;
}
std::weak_ptr< GameObject > State::GetObjectPtr(GameObject* go){
	std::weak_ptr< GameObject > retorno;
	for(int i=0;i<int(this->objectArray.size());i++){
			if(this->objectArray[i].get()==go){
				retorno=this->objectArray[i];
			}
	}
	return retorno;
}
bool State::PopRequested (){
	return this->popRequested;
}
std::weak_ptr< GameObject > State::AddObjectPtr(GameObject* go){
	std::weak_ptr< GameObject > retorno;
	std::shared_ptr<GameObject> adicionar=std::shared_ptr<GameObject>(go);
	if(this->started){
		adicionar->Start();
	}
	this->objectArray.push_back(adicionar);
	retorno=adicionar;
	return retorno;
}
