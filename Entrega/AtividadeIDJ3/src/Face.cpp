/*
 * Face.cpp
 *
 *  Created on: 2 de jul. de 2022
 *      Author: newlo
 */

#include "Face.h"
#include "GameObject.h"

Face::Face(GameObject* associated ) {
	// TODO Auto-generated constructor stub
	this->hitpoints=30;
	this->associated=associated;
}

Face::~Face() {
	// TODO Auto-generated destructor stub
}

bool Face::Damage(int damage){
	this->hitpoints=this->hitpoints-damage;
	if(this->hitpoints<=0){
		this->associated->RequestDelete();
		Sound* sound=(Sound*)this->associated->GetComponent("Sound");
		sound->Play(1);
		return true;
	}
	else {
		return false;
	}
}
bool Face::Is(string tipo){
	if(tipo.compare("Face")){
		return false;
	}else{
		return true;
	}
}
void Face::Upadate(float dt){

}
void Face::Render(SDL_Renderer* render){

}
