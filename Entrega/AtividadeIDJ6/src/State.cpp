/*
 * State.cpp
 *
 *  Created on: 21 de jun. de 2022
 *      Author: newlo
 */

#include "State.h"
#include "Game.h"
#include "Collision.cpp"
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
void State::LoadAssets(){
	//define e toca a musica de fundo
	this->music.Open("stageState.ogg",Game::GetInstance().recursos);
	this->music.Play(-1);
	//define e faz com que o background cubra toda a tela
	this->objectArray.push_back(std::make_shared<GameObject>());
	this->objectArray[0]->box.x=0;
	this->objectArray[0]->box.y=0;
	this->objectArray[0]->box.w=Game::GetInstance().width;
	this->objectArray[0]->box.h=Game::GetInstance().height;
	Component* bg=new Sprite (this->objectArray[0].get());
	bg->Open("ocean.jpg",Game::GetInstance().GetRenderer(),Game::GetInstance().recursos);
	bg->SetClip(0, 0, Game::GetInstance().width, Game::GetInstance().height);
	this->objectArray[0]->AddComponent(bg);
	Component* folower= new CameraFollower(this->objectArray[0].get());
	this->objectArray[0]->AddComponent(folower);
	SDL_Delay(33);
	//define o tileSet e tilemap em um objeto próprio
	this->objectArray.push_back(std::make_shared<GameObject>());
	TileSet* tileset= new TileSet(64,64,"tileset.png",Game::GetInstance().GetRenderer(),Game::GetInstance().recursos);
	Component* Map= new TileMap(this->objectArray[1].get(),"tileMap.txt",tileset);
	this->objectArray[1]->AddComponent(Map);
	//adiciona um pinguin e seta como o foco da camera
	this->objectArray.push_back(std::make_shared<GameObject>());
	Component* penguin= new PenguinBody(this->objectArray[2].get());
	this->objectArray[2]->AddComponent(penguin);
	Game::GetInstance().camera->Follow(this->objectArray[2].get());
	//adiciona um alien e seta como o foco da camera
		this->objectArray.push_back(std::make_shared<GameObject>());
		Component* alien= new Alien(this->objectArray[3].get(),5,Game::GetInstance().recursos);
		this->objectArray[3]->AddComponent(alien);

}


void State::Update(float dt){
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
}



void State::Render (){
	for(int i=0;i<int(this->objectArray.size());i++){
		this->objectArray[i]->Render(Game::GetInstance().GetRenderer(),Game::GetInstance().camera->pos);
	}
}
bool State::QuitRequested (){
	return this->quitRequested;
}


void State::Start(){
	if(started){
		return;
	}
	this->LoadAssets();
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
