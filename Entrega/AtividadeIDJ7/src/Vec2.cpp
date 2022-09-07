/*
 * Vec2.cpp
 *
 *  Created on: 2 de jul. de 2022
 *      Author: newlo
 */

#include "Vec2.h"

Vec2::Vec2() {
	// TODO Auto-generated constructor stub

}
Vec2::Vec2(float x,float y) {
	// TODO Auto-generated constructor stub
	this->x=x;
	this->y=y;

}

Vec2::~Vec2() {
	// TODO Auto-generated destructor stub
}

Vec2 Vec2::GetRotated(float ang){
	float x=this->x;
	this->x=this->x *cos(ang)- y*sin(ang);
	this->y=this->y *cos(ang)+ x*sin(ang);
	return *this;
}
Vec2 Vec2::Soma(float x, float y){
	this->x=this->x+x;
	this->y=this->y+y;
	return *this;
}
Vec2 Vec2::Subtract(float x, float y){
	this->x=x-this->x;
	this->y=y-this->y;
	return *this;
}
float Vec2::GetAngle(Vec2 comparativo){
	x=this->x-comparativo.x;
	y=this->y-comparativo.y;
	return atan2 (y,x) ;
}
float Vec2::GetDistance(Vec2 comparativo){
	return sqrt(((this->x-comparativo.x)*(this->x-comparativo.x))+((this->y-comparativo.y)*(this->y-comparativo.y)));
}
