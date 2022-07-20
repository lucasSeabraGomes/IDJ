/*
 * GameObject.cpp
 *
 *  Created on: 2 de jul. de 2022
 *      Author: newlo
 */

#include "GameObject.h"

GameObject::GameObject() {
	// TODO Auto-generated constructor stub
	this->isDead= false;
}

GameObject::~GameObject() {
	  for(int i=0;i<int(this->componentes.size());i++){
		   this->componentes[i]->~Component();
	  }
	  if(this->componentes.size()>0){
		  this->componentes.clear();
	  }
	// TODO Auto-generated destructor stub
}

void GameObject::Update(float dt){
	  for(int i=0;i<int(this->componentes.size());i++){
		   this->componentes[i]->Update(dt);
	  }
}

void GameObject::Render(SDL_Renderer* render,Vec2 camera ){
	  for(int i=0;i<int(this->componentes.size());i++){
		   this->componentes[i]->Render(render,camera );
	  }
}
void GameObject::RequestDelete(){
	this->isDead=true;
}
void GameObject::AddComponent(Component* cpt){
	this->componentes.push_back(cpt);
}
bool GameObject::IsDead(){
	return this->isDead;
}
void GameObject::RemoveComponent(Component* cpt){
		for(int i=0;i<int(this->componentes.size());i++){
				if(this->componentes[i]==cpt){
					this->componentes[i]->~Component();
					this->componentes.erase(this->componentes.begin()+i);
				}
			  }
}
Component* GameObject::GetComponent(string type){
	for(int i=0;i<int(this->componentes.size());i++){
			if(this->componentes[i]->Is(type)){
				return this->componentes[i];
			}
		  }
	return nullptr;
}
