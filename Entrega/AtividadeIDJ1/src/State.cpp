/*
 * State.cpp
 *
 *  Created on: 21 de jun. de 2022
 *      Author: newlo
 */

#include "State.h"

State::State() {
	this->quitRequested=false;
	this->music =  Music();
	this->bg= Sprite();
	cout<<"criando state\n";
}

State::~State() {
	cout<<"removendo state1\n";
	this->bg.~Sprite();
	cout<<"removendo state2\n";
	this->music.~Music();
	cout<<"removendo state3\n";
	free(this);
}
//seta a musica da tela e o background na janela de w=width e h=heigth
void State::LoadAssets(SDL_Renderer* render,int w, int h){
	//define e toca a musica de fundo
	this->music.Open("stageState.ogg");
	this->music.Play(-1);
	//define e faz com que o background cubra toda a tela
	this->bg.Open("ocean.jpg",render);
	this->bg.SetClip(0, 0, w, h);
}
void State::Update(float dt){
	this->quitRequested=SDL_QuitRequested();
}
void State::Render (SDL_Renderer* render){

		this->bg.Render(0, 0,render);
}
bool State::QuitRequested (){
	return this->quitRequested;
}
