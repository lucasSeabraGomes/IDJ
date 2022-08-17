/*
 * Collider.cpp
 *
 *  Created on: 10 de ago. de 2022
 *      Author: newlo
 */

#include "Collider.h"
#include "Game.h"
Collider::Collider(GameObject* associated ,Vec2 scale ,Vec2 offset ) {
	// TODO Auto-generated constructor stub
	this->associated=associated;
	this->scale=scale;
	this->offset=offset;
}

Collider::~Collider() {
	// TODO Auto-generated destructor stub
}

void Collider::Update ( float dt){
	this->Box=this->associated->box;
	this->Box.w=this->associated->box.w*this->scale.x;
	this->Box.h=this->associated->box.h*this->scale.y;
	this->Box.x=this->associated->box.x-((this->Box.w/2)-(this->associated->box.w/2))+this->offset.x;
	this->Box.y=this->associated->box.y-((this->Box.h/2)-(this->associated->box.h/2))+this->offset.y;

}
void Collider::Render(SDL_Renderer* render,Vec2 camera ){

	/*Vec2 center( this->Box.GetCenter() );
	SDL_Point points[5];

	Vec2 point = (Vec2(this->Box.x, this->Box.y) - center).GetRotated( this->associated->angleDeg/(180/PI) )
					+ center + camera;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};

	point = (Vec2(this->Box.x + this->Box.w, this->Box.y) - center).GetRotated( associated->angleDeg/(180/PI) )
					+ center + camera;
	points[1] = {(int)point.x, (int)point.y};

	point = (Vec2(this->Box.x + this->Box.w, this->Box.y + this->Box.h) - center).GetRotated( associated->angleDeg/(180/PI) )
					+ center + camera;
	points[2] = {(int)point.x, (int)point.y};

	point = (Vec2(this->Box.x, this->Box.y + this->Box.h) - center).GetRotated( associated->angleDeg/(180/PI) )
					+ center + camera;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);*/

}
bool Collider::Is(string tipo){
	if(tipo.compare("Collider")){
			return false;
		}else{
			return true;
		}
}
void Collider::SetScale (Vec2 scale ){
	this->scale=scale;
}
void Collider::SetOffset (Vec2 offset ) {
	this->offset=offset;
}
void Collider::NotifyCollision(GameObject*other){

}
