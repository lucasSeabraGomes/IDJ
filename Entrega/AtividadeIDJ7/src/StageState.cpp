/*
 * StageState.cpp
 *
 *  Created on: 17 de ago. de 2022
 *      Author: newlo
 */

#include "StageState.h"
#include "Game.h"
#include "Collision.cpp"
#include "GameData.h"
#include "EndState.h"
StageState::StageState() {
	// TODO Auto-generated constructor stub

}

StageState::~StageState() {
	// TODO Auto-generated destructor stub
}
void StageState::Pause (){

}
void StageState::Resume (){

}
void StageState::Start(){
	if(started){
		return;
	}
	this->LoadAssets();
	this->StartArray();
	started=true;
}
void StageState::Render (){
	this->RenderArray();
}
void StageState::LoadAssets(){
	//define e toca a musica de fundo
	this->music.Open("stageState.ogg",Game::GetInstance()->recursos);
	this->music.Play(-1);
	SDL_Delay(33);
	//define e faz com que o background cubra toda a tela
	this->objectArray.push_back(std::make_shared<GameObject>());
	this->objectArray[0]->box.x=0;
	this->objectArray[0]->box.y=0;
	this->objectArray[0]->box.w=Game::GetInstance()->width;
	this->objectArray[0]->box.h=Game::GetInstance()->height;
	SDL_Delay(33);
	Component* bg=new Sprite (this->objectArray[0].get());
	bg->Open("ocean.jpg",Game::GetInstance()->GetRenderer(),Game::GetInstance()->recursos);
	bg->SetClip(0, 0, Game::GetInstance()->width, Game::GetInstance()->height);
	this->objectArray[0]->AddComponent(bg);
	SDL_Delay(33);
	Component* folower= new CameraFollower(this->objectArray[0].get());
	//pequeno delay para evitar bug
	SDL_Delay(33);
	this->objectArray[0]->AddComponent(folower);
	//define o tileSet e tilemap em um objeto próprio
	this->objectArray.push_back(std::make_shared<GameObject>());
	TileSet* tileset= new TileSet(64,64,"tileset.png",Game::GetInstance()->GetRenderer(),Game::GetInstance()->recursos);
	Component* Map= new TileMap(this->objectArray[1].get(),"tileMap.txt",tileset);
	this->objectArray[1]->AddComponent(Map);
	//adiciona um pinguin e seta como o foco da camera
	this->objectArray.push_back(std::make_shared<GameObject>());
	Component* penguin= new PenguinBody(this->objectArray[2].get());
	this->objectArray[2]->AddComponent(penguin);
	SDL_Delay(33);
	Game::GetInstance()->camera->Follow(this->objectArray[2].get());
	//adiciona um alien e seta como o foco da camera
		this->objectArray.push_back(std::make_shared<GameObject>());
		Component* alien= new Alien(this->objectArray[3].get(),5,Game::GetInstance()->recursos);
		this->objectArray[3]->AddComponent(alien);
		SDL_Delay(33);

}
void StageState::Update(float dt){
	InputManager::GetInstance().Update();
	//fecha o jogo se escape for pressionado ou alt f4 ou o x da janela
	if(InputManager::GetInstance().QuitRequested() ){
		this->quitRequested=true;
	}
	if(InputManager::GetInstance().KeyPress(SDLK_ESCAPE)){
		this->popRequested=true;
	}
	//adiciona pinguins

	this->UpdateArray(dt);
	Game::GetInstance()->camera->Update(dt, 1024, 600);
	for(int i=0;i<int(this->objectArray.size());i++){
		Collider* colisor1=(Collider*)(this->objectArray[i].get()->GetComponent("Collider"));
		float ang1=(float)(this->objectArray[i].get()->angleDeg*PI / 180.0);
		if(colisor1!=nullptr){
			for(int j=i+1;j<int(this->objectArray.size());j++){
				Collider* colisor2=(Collider*)(this->objectArray[j].get()->GetComponent("Collider"));
				float ang2=(float)(this->objectArray[j].get()->angleDeg*PI / 180.0);
				if(colisor2!=nullptr ){
					if(Collision::IsColliding(colisor1->Box,colisor2->Box,ang1 , ang2)){
						this->objectArray[i].get()->NotifyCollision(this->objectArray[j].get());
						this->objectArray[j].get()->NotifyCollision(this->objectArray[i].get());
					}
				}
			}
		}
	}
	//termina o jogo
	if(PenguinBody::player==nullptr){
		GameData::playerVictory=false;
		this->popRequested=true;
		Game::GetInstance()->Push(new EndState());
	}else if(Alien::alienCount==0){
		GameData::playerVictory=true;
		this->popRequested=true;
		Game::GetInstance()->Push(new EndState());
	}
}
