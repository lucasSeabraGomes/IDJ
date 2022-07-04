/*
 * Component.cpp
 *
 *  Created on: 2 de jul. de 2022
 *      Author: newlo
 */

#include "Component.h"
#include "GameObject.h"

Component::Component( ) {
	// TODO Auto-generated constructor stub
}
Component::Component(GameObject* associated ) {
	// TODO Auto-generated constructor stub
	this->associated=associated;
}
Component::~Component() {
	// TODO Auto-generated destructor stub
}
void Component::Render(SDL_Renderer* render){

}

void Component::Update(float dt){

}
bool Component::Is(string tipo){
	return false;
}
void Component::Open(string file,SDL_Renderer* render){

}
void Component::SetClip(int x, int y ,   int w, int h){

}
bool Component::Damage(int damage){
	return false;
}
int Component::getW(){
	return 0;
}
int Component::getH(){
	return 0;
}
