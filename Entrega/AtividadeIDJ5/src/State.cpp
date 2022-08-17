/*
 * State.cpp
 *
 *  Created on: 21 de jun. de 2022
 *      Author: newlo
 */

#include "State.h"
#include "Game.h"
State::State() {
	this->quitRequested=false;
	this->started=false;
	this->music = Music();
}

State::~State() {
	cout<<"removendo state1\n";
	this->music.~Music();
	cout<<"removendo state2\n";
	for(int i=0;i<int(this->objectArray.size());i++){
					this->objectArray[i]->~GameObject();
	}
	cout<<"removendo state3\n";
		if(this->objectArray.size()>0){
			 this->objectArray.clear();
		}

}
//seta a musica da tela e o background na janela de w=width e h=heigth
void State::LoadAssets(SDL_Renderer* render,int w, int h){
	//define e toca a musica de fundo
	this->music.Open("stageState.ogg",Game::GetInstance().recursos);
	this->music.Play(-1);
	//define e faz com que o background cubra toda a tela
	this->objectArray.push_back(std::make_shared<GameObject>());
	this->objectArray[0]->box.x=0;
	this->objectArray[0]->box.y=0;
	this->objectArray[0]->box.w=w;
	this->objectArray[0]->box.h=h;
	Component* bg=new Sprite (this->objectArray[0].get());
	bg->Open("ocean.jpg",render,Game::GetInstance().recursos);
	bg->SetClip(0, 0, w, h);
	this->objectArray[0]->AddComponent(bg);
	Component* folower= new CameraFollower(this->objectArray[0].get());
	this->objectArray[0]->AddComponent(folower);
	//define o tileSet e tilemap em um objeto próprio
	this->objectArray.push_back(std::make_shared<GameObject>());
	TileSet* tileset= new TileSet(64,64,"tileset.png",render,Game::GetInstance().recursos);
	Component* Map= new TileMap(this->objectArray[1].get(),"tileMap.txt",tileset);
	this->objectArray[1]->AddComponent(Map);
	//adiciona um alien e seta como o foco da camera
	this->objectArray.push_back(std::make_shared<GameObject>());
	Component* alien= new Alien(this->objectArray[2].get(),5,Game::GetInstance().recursos);
	this->objectArray[2]->AddComponent(alien);
	Game::GetInstance().camera->Follow(this->objectArray[2].get());

}


void State::Update(float dt,SDL_Renderer* render){
	InputManager::GetInstance().Update();
	//fecha o jogo se escape for pressionado ou alt f4 ou o x da janela
	if(InputManager::GetInstance().QuitRequested() or InputManager::GetInstance().KeyPress(SDLK_ESCAPE) or InputManager::GetInstance().IsKeyDown(SDLK_ESCAPE)){
		this->quitRequested=true;
	}
	//adiciona pinguins

	for(int i=0;i<int(this->objectArray.size());i++){
		this->objectArray[i]->Update(dt);
	}
	for(int i=0;i<int(this->objectArray.size());i++){
			if(this->objectArray[i]->IsDead()){
				this->objectArray[i]->~GameObject();
				this->objectArray.erase(this->objectArray.begin()+i);
			}
		}
	Game::GetInstance().camera->Update(dt, 1024, 600);
}



void State::Render (SDL_Renderer* render){
	for(int i=0;i<int(this->objectArray.size());i++){
		this->objectArray[i]->Render(render,Game::GetInstance().camera->pos);
	}
}
bool State::QuitRequested (){
	return this->quitRequested;
}


void State::Start(){
	if(started){
		return;
	}
	this->LoadAssets(Game::GetInstance().GetRenderer(), 1024, 600);
	for(int i=0;i<int(this->objectArray.size());i++){
		this->objectArray[i]->Start();
	}
	started=true;
}
std::weak_ptr< GameObject > State::GetObjectPtr(GameObject* go){
	std::weak_ptr< GameObject > retorno;
	for(int i=0;i<int(this->objectArray.size());i++){
			if(this->objectArray[i].get()==go){
				retorno=this->objectArray[i];
			}
	}
	return retorno;
}

std::weak_ptr< GameObject > State::AddObjectPtr(GameObject* go){
	std::weak_ptr< GameObject > retorno;
	std::shared_ptr<GameObject> adicionar=std::shared_ptr<GameObject>(go);
	if(this->started){
		adicionar->Start();
	}
	this->objectArray.push_back(adicionar);
	retorno=adicionar;
	return retorno;
}
