/*
 * Timer.cpp
 *
 *  Created on: 12 de ago. de 2022
 *      Author: newlo
 */

#include "Timer.h"

Timer::Timer() {
	// TODO Auto-generated constructor stub
	this->time=0;

}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

float Timer::Get(){
	return this->time;
}
void  Timer::Update(float dt ){
	this->time=this->time+dt;
}
void  Timer::Restart(){
	this->time=0;
}
