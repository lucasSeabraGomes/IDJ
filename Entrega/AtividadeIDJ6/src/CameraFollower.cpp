/*
 * CameraFollower.cpp
 *
 *  Created on: 16 de jul. de 2022
 *      Author: newlo
 */

#include "CameraFollower.h"
#include "GameObject.h"
CameraFollower::CameraFollower() {
	// TODO Auto-generated constructor stub

}
CameraFollower::CameraFollower(GameObject* go) {
	// TODO Auto-generated constructor stub
	this->associated=go;
}
CameraFollower::~CameraFollower() {
	// TODO Auto-generated destructor stub
}
bool CameraFollower::Is(string tipo){
	if(tipo.compare("CameraFollower")){
			return false;
		}else{
			return true;
		}
}
void CameraFollower::Update(float dt){

}
void CameraFollower::Render(SDL_Renderer* render,Vec2 camera){
		if(this->associated!=nullptr){
			this->associated->box.x=-camera.x;
			this->associated->box.y=-camera.y;
			this->associated->GetComponent("Sprite")->Render(render,camera);
		}
}
