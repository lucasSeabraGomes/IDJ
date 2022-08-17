/*
 * InputManager.cpp
 *
 *  Created on: 13 de jul. de 2022
 *      Author: newlo
 */

#include "InputManager.h"
InputManager::InputManager() {
	// TODO Auto-generated constructor stub
	this->updateCounter=0;
	for(int i=0;i<6;i++){
		this->mouseState[i]={false};
		this->mouseUpdate[i]=0;
	}
	for(int i=0;i<416;i++){
		this->keyUpdate[i]=0;
		this->keyState[i]=false;
	}
	this->quitRequested=false;
}

InputManager::~InputManager() {
	// TODO Auto-generated destructor stub
}

InputManager& InputManager::GetInstance(){
	static InputManager* instance=new InputManager();
	return *instance;
}
void  InputManager::Update (){
	SDL_Event event;
	SDL_GetMouseState(&this->mouseX, &this->mouseY);
	this->updateCounter=this->updateCounter+1;
	int key;
	int button;
	while (SDL_PollEvent(&event)) {
			// Se o evento for quit, setar a flag para terminação
			if(event.type == SDL_QUIT) {
				this->quitRequested = true;
			}
			if(event.type == SDL_MOUSEBUTTONDOWN and event.key.repeat!=1){
				button=event.button.button;
				this->mouseState[button]=true;
				this->mouseUpdate[button]=this->updateCounter;
			}
			if(event.type == SDL_MOUSEBUTTONUP and event.key.repeat!=1){
				button=event.button.button;
				this->mouseState[button]=false;
				this->mouseUpdate[button]=this->updateCounter;
			}
			if( event.type == SDL_KEYDOWN and event.key.repeat!=1){
				if(event.key.keysym.sym>=0x40000000){
					key=event.key.keysym.sym-0x3FFFFF81;
				}
				else{
					key=event.key.keysym.sym;
				}
				this->keyState[key]=true;
				this->keyUpdate[key]=this->updateCounter;
			}
			if( event.type == SDL_KEYUP and event.key.repeat!=1){
				if(event.key.keysym.sym>=0x40000000){
							key=event.key.keysym.sym-0x3FFFFF81;
				}
				else{
					key=event.key.keysym.sym;
				}
				this->keyState[key]=false;
				this->keyUpdate[key]=this->updateCounter;
			}
	}
}
int InputManager::GetMouseX(){
	return this->mouseX;
}
int InputManager::GetMouseY(){
	return this->mouseY;
}
bool InputManager::KeyPress(int key){
	if(key>=0x40000000){
		key=key-0x3FFFFF81;
	}
	if(this->updateCounter==this->keyUpdate[key] and this->keyState[key]){
		return true;
	}
	else{
		return false;
	}
}
bool InputManager::KeyRelease(int key){
	if(key>=0x40000000){
		key=key-0x3FFFFF81;
	}
	if(this->updateCounter==this->keyUpdate[key] and !this->keyState[key]){
		return true;
	}
	else{
		return false;
	}
}
bool InputManager::IsKeyDown(int key){
	if(key>=0x40000000){
		key=key-0x3FFFFF81;
	}
	if(this->updateCounter!=this->keyUpdate[key] and this->keyState[key]){
		return true;
	}
	else{
		return false;
	}
}
bool InputManager::MousePress(int button){
	if(this->mouseState[button] and this->mouseUpdate[button]==this->updateCounter){
		return true;
	}
	else{
		return false;
	}
}
bool InputManager::MouseRelease(int button){
	if(!this->mouseState[button] and this->mouseUpdate[button]==this->updateCounter){
		return true;
	}
	else{
		return false;
	}
}
bool InputManager::IsMouseDown(int button){
	if(this->mouseState[button] and this->mouseUpdate[button]!=this->updateCounter){
		return true;
	}
	else{
		return false;
	}
}
bool InputManager::QuitRequested (){
	return this->quitRequested;
}
