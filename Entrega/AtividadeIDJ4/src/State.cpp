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
	this->recursos=new Resources();
	this->input= InputManager::GetInstance();
	this->camera=new Camera();
}

State::~State() {
	cout<<"removendo state1\n";
	this->music.~Music();
	cout<<"removendo state2\n";
	for(int i=0;i<int(this->objectArray.size());i++){
					this->objectArray[i]->~GameObject();
			 }
		if(this->objectArray.size()>0){
			 this->objectArray.clear();
		}
	cout<<"removendo state3\n";
	this->recursos->~Resources();
	if(this->camera!=nullptr){
		this->camera->~Camera();
		this->camera=nullptr;
	}
}
//seta a musica da tela e o background na janela de w=width e h=heigth
void State::LoadAssets(SDL_Renderer* render,int w, int h){
	//define e toca a musica de fundo
	this->music.Open("stageState.ogg",this->recursos);
	this->music.Play(-1);
	//define e faz com que o background cubra toda a tela
	this->objectArray.push_back(new GameObject());
	this->objectArray[0]->box.x=0;
	this->objectArray[0]->box.y=0;
	this->objectArray[0]->box.w=w;
	this->objectArray[0]->box.h=h;
	Component* bg=new Sprite (this->objectArray[0]);
	bg->Open("ocean.jpg",render,this->recursos);
	bg->SetClip(0, 0, w, h);
	this->objectArray[0]->AddComponent(bg);
	Component* folower= new CameraFollower(this->objectArray[0]);
	this->objectArray[0]->AddComponent(folower);
	//define o tileSet e tilemap em um objeto próprio
	this->objectArray.push_back(new GameObject());
	TileSet* tileset= new TileSet(64,64,"tileset.png",render,this->recursos);
	Component* Map= new TileMap(this->objectArray[1],"tileMap.txt",tileset);
	this->objectArray[1]->AddComponent(Map);
}


void State::Update(float dt,SDL_Renderer* render){
	this->input.Update();
	//fecha o jogo se escape for pressionado ou alt f4 ou o x da janela
	if(this->input.QuitRequested() or this->input.KeyPress(SDLK_ESCAPE) or this->input.IsKeyDown(SDLK_ESCAPE)){
		this->quitRequested=true;
	}
	//adiciona pinguins
	if(this->input.KeyPress(SPACE_KEY)){
		Vec2 objPos = Vec2( 200, 0 ).GetRotated( -3.14159265358979323846 + 3.14159265358979323846*(rand() % 1001)/500.0 ).Soma( this->input.GetMouseX()-this->camera->pos.x, this->input.GetMouseY()-this->camera->pos.y );
		AddObject((int)objPos.x, (int)objPos.y ,render);
	}
	//apaga pinguins
	if(this->input.MousePress(LEFT_MOUSE_BUTTON ) or this->input.IsMouseDown(LEFT_MOUSE_BUTTON )){
		for(int i = objectArray.size() - 1; i >= 0; --i) {
			// Obtem o ponteiro e casta pra Face.
			GameObject* go = (GameObject*) objectArray[i];
			// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
			// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
			// ao usar get(), violamos esse princípio e estamos menos seguros.
			// Esse código, assim como a classe Face, é provisório. Futuramente, para
			// chamar funções de GameObjects, use objectArray[i]->função() direto.
			if(go->box.Contains( (float)this->input.GetMouseX()-this->camera->pos.x, (float)this->input.GetMouseY()-this->camera->pos.y ) ) {
				Face* face = (Face*)go->GetComponent( "Face" );
				if ( nullptr != face ) {
					// Aplica dano
					face->Damage(std::rand() % 10 + 10);
					// Sai do loop (só queremos acertar um)
					break;
				}
			}
		}
	}
	for(int i=0;i<int(this->objectArray.size());i++){
			if(this->objectArray[i]->IsDead()){
				cout<<"apagando pinguin";
				this->objectArray[i]->~GameObject();
				this->objectArray.erase(this->objectArray.begin()+i);
			}
		}
	this->camera->Update(dt, 1024, 600, this->input);
}



void State::Render (SDL_Renderer* render){
	for(int i=0;i<int(this->objectArray.size());i++){
		this->objectArray[i]->Render(render,this->camera->pos);
	}
}
bool State::QuitRequested (){
	return this->quitRequested;
}
void State::AddObject(int mouseX,int mouseY,SDL_Renderer* render){
	GameObject* ob=new GameObject();
		this->objectArray.push_back(ob);
		ob->box.x=mouseX;
		ob->box.y=mouseY;
		Component* sprite= new Sprite("penguinface.png",render,ob,this->recursos);
		this->objectArray[this->objectArray.size()-1]->box.h= sprite->GetHeight();
		this->objectArray[this->objectArray.size()-1]->box.w= sprite->GetWidth();
		sprite->SetClip(0, 0, this->objectArray[this->objectArray.size()-1]->box.w, this->objectArray[this->objectArray.size()-1]->box.h);
		Component* face = new Face(ob);
		Component* sound= new Sound("boom.wav",ob,this->recursos);
		this->objectArray[this->objectArray.size()-1]->AddComponent(sprite);
		this->objectArray[this->objectArray.size()-1]->AddComponent(face);
		this->objectArray[this->objectArray.size()-1]->AddComponent(sound);
}
