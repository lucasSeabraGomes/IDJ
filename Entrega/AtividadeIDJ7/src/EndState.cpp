/*
 * EndState.cpp
 *
 *  Created on: 18 de ago. de 2022
 *      Author: newlo
 */

#include "EndState.h"
#include "StageState.h"
#include "Game.h"
#include "GameData.h"
#include "TitleState.h"
EndState::EndState() {
	// TODO Auto-generated constructor stub

}

EndState::~EndState() {
	// TODO Auto-generated destructor stub
}

void EndState::LoadAssets(){
	//define e faz com que o background cubra toda a tela
	this->objectArray.push_back(std::make_shared<GameObject>());
	this->objectArray[0]->box.x=0;
	this->objectArray[0]->box.y=0;
	this->objectArray[0]->box.w=Game::GetInstance()->width;
	this->objectArray[0]->box.h=Game::GetInstance()->height;
	Component* bg=new Sprite (this->objectArray[0].get());
	if(GameData::playerVictory){
		bg->Open("win.jpg",Game::GetInstance()->GetRenderer(),Game::GetInstance()->recursos);
		this->music.Open("endStateWin.ogg",Game::GetInstance()->recursos);
	}else{
		bg->Open("lose.jpg",Game::GetInstance()->GetRenderer(),Game::GetInstance()->recursos);
		this->music.Open("endStateLose.ogg",Game::GetInstance()->recursos);
	}

	this->music.Play(-1);
	bg->SetClip(0, 0, Game::GetInstance()->width, Game::GetInstance()->height);
	this->objectArray[0]->AddComponent(bg);
	//gera texto
	this->objectArray.push_back(std::make_shared<GameObject>());
	this->objectArray[1]->box.x=300;
	this->objectArray[1]->box.y=400;
	SDL_Color color= SDL_Color();
	color.a=255;
	color.b=0;
	color.g=0;
	color.r=0;
	Component* text=new Text (this->objectArray[1].get(),"Call me maybe.ttf",24,SOLID,"Pressione espaco para jogar novamente e esc para sair",color);
	this->objectArray[1]->AddComponent(text);
}
void EndState::Update(float dt){
	Game::GetInstance()->camera->pos.x=0;
	Game::GetInstance()->camera->pos.y=0;
	InputManager::GetInstance().Update();
	//fecha o jogo se escape for pressionado ou alt f4 ou o x da janela
	if(InputManager::GetInstance().QuitRequested() or InputManager::GetInstance().KeyPress(SDLK_ESCAPE) ){
		this->quitRequested=true;
	}
	if(InputManager::GetInstance().KeyPress(SPACE_KEY)){
		this->popRequested=true;
		Game::GetInstance()->Push(new TitleState());
	}
	this->objectArray[1]->Update(dt);
}
void EndState::Pause (){

}
void EndState::Resume (){

}
void EndState::Start(){
	if(started){
		return;
	}
	this->LoadAssets();
	this->StartArray();
	started=true;
}
void EndState::Render (){
	this->RenderArray();
}
