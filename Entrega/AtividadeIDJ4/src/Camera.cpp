/*
 * Camera.cpp
 *
 *  Created on: 16 de jul. de 2022
 *      Author: newlo
 */

#include "Camera.h"

Camera::Camera() {
	// TODO Auto-generated constructor stub
	this->focus=nullptr;
	this->pos=Vec2(0,0);
	this->speed=Vec2(0,0);
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}
void Camera::Follow (GameObject* newFocus){
	this->focus=newFocus;
}
void Camera::Unfollow (){
	this->focus=nullptr;
}
void Camera::Update (float dt,int width, int height){
	if(this->focus!=nullptr) {
			this->pos.x=(width/2)-this->focus->box.x;
			this->pos.y=(height/2)-this->focus->box.y;
	}else{
		if(InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY) or InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY)){
			this->pos.x=this->pos.x+dt;
		}
		if(InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY) or InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY)){
			this->pos.x=this->pos.x-dt;
		}
		if(InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY) or InputManager::GetInstance().KeyPress(UP_ARROW_KEY)){
			this->pos.y=this->pos.y+dt;
		}
		if(InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY) or InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY)){
			this->pos.y=this->pos.y-dt;
		}
	}
}
