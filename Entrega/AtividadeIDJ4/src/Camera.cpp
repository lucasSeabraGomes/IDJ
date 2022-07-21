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
void Camera::Update (float dt,int width, int height,InputManager manager){
	int oldx,oldy;
	if(this->focus!=nullptr) {
		oldx=this->focus->box.x;
		oldy=this->focus->box.y;
		this->focus->box.x=(width/2)-(this->focus->box.w/2);
		this->focus->box.y=(height/2)-(this->focus->box.h/2);
		pos.x=pos.x+this->focus->box.x-oldx;
		pos.y=pos.y+this->focus->box.y-oldy;
	}
	if(manager.IsKeyDown(LEFT_ARROW_KEY) or manager.KeyPress(LEFT_ARROW_KEY)){
		this->pos.x=this->pos.x+dt;
	}
	if(manager.IsKeyDown(RIGHT_ARROW_KEY) or manager.KeyPress(RIGHT_ARROW_KEY)){
		this->pos.x=this->pos.x-dt;
	}
	if(manager.IsKeyDown(UP_ARROW_KEY) or manager.KeyPress(UP_ARROW_KEY)){
		this->pos.y=this->pos.y+dt;
	}
	if(manager.IsKeyDown(DOWN_ARROW_KEY) or manager.KeyPress(DOWN_ARROW_KEY)){
		this->pos.y=this->pos.y-dt;
	}
}
