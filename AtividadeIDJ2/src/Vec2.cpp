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
Vec2::Vec2(int x,int y) {
	// TODO Auto-generated constructor stub
	this->x=x;
	this->y=y;

}

Vec2::~Vec2() {
	// TODO Auto-generated destructor stub
}

Vec2 Vec2::GetRotated(float ang){
	this->x=this->x *cos(ang)- y*sin(ang);
	this->x=this->y *cos(ang)- x*sin(ang);
	return *this;
}
Vec2 Vec2::Soma(float x, float y){
	this->x=this->x+x;
	this->y=this->y+y;
	return *this;
}
