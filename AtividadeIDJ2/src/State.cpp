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
}
//seta a musica da tela e o background na janela de w=width e h=heigth
void State::LoadAssets(SDL_Renderer* render,int w, int h){
	//define e toca a musica de fundo
	this->music.Open("C:/Users/newlo/eclipse-workspace/AtividadeIDJ2/src/stageState.ogg");
	this->music.Play(-1);
	//define e faz com que o background cubra toda a tela
	this->objectArray.push_back(new GameObject());
	this->objectArray[0]->box.x=0;
	this->objectArray[0]->box.y=0;
	this->objectArray[0]->box.w=w;
	this->objectArray[0]->box.h=h;
	Component* bg=new Sprite (this->objectArray[0]);
	bg->Open("C:/Users/newlo/eclipse-workspace/AtividadeIDJ2/src/ocean.jpg",render);
	bg->SetClip(0, 0, w, h);
	this->objectArray[0]->AddComponent(bg);

	GameObject* ob=new GameObject();
	this->objectArray.push_back(ob);
	ob->box.x=200;
	ob->box.y=200;
	Component* sprite= new Sprite("C:/Users/newlo/eclipse-workspace/AtividadeIDJ2/src/penguinface.png",render,ob);
	this->objectArray[this->objectArray.size()-1]->box.h= sprite->getH();
	this->objectArray[this->objectArray.size()-1]->box.w= sprite->getW();
	sprite->SetClip(0, 0, this->objectArray[this->objectArray.size()-1]->box.w, this->objectArray[this->objectArray.size()-1]->box.h);
	Component* face = new Face(ob);
	this->objectArray[this->objectArray.size()-1]->AddComponent(sprite);
	this->objectArray[this->objectArray.size()-1]->AddComponent(face);
	cout<<"criando pinguin\n";

	ob=new GameObject();
		this->objectArray.push_back(ob);
		ob->box.x=500;
		ob->box.y=200;
		sprite= new Sprite("C:/Users/newlo/eclipse-workspace/AtividadeIDJ2/src/penguinface.png",render,ob);
		this->objectArray[this->objectArray.size()-1]->box.h= sprite->getH();
		this->objectArray[this->objectArray.size()-1]->box.w= sprite->getW();
		sprite->SetClip(0, 0, this->objectArray[this->objectArray.size()-1]->box.w, this->objectArray[this->objectArray.size()-1]->box.h);
		face = new Face(ob);
		this->objectArray[this->objectArray.size()-1]->AddComponent(sprite);
		this->objectArray[this->objectArray.size()-1]->AddComponent(face);
		cout<<"criando pinguin\n";
}
void State::Update(float dt,SDL_Renderer* render){
	this->Input( render);
	for(int i=0;i<int(this->objectArray.size());i++){
			if(this->objectArray[i]->IsDead()){
				this->objectArray.erase(this->objectArray.begin()+i);
			}
		}
}
void State::Render (SDL_Renderer* render){
	for(int i=0;i<int(this->objectArray.size());i++){
		this->objectArray[i]->Render(render);
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
		Component* sprite= new Sprite("C:/Users/newlo/eclipse-workspace/AtividadeIDJ2/src/penguinface.png",render,ob);
		this->objectArray[this->objectArray.size()-1]->box.h= sprite->getH();
		this->objectArray[this->objectArray.size()-1]->box.w= sprite->getW();
		sprite->SetClip(0, 0, this->objectArray[this->objectArray.size()-1]->box.w, this->objectArray[this->objectArray.size()-1]->box.h);
		Component* face = new Face(ob);
		this->objectArray[this->objectArray.size()-1]->AddComponent(sprite);
		this->objectArray[this->objectArray.size()-1]->AddComponent(face);
		cout<<"criando pinguin\n";
}



void State::Input(SDL_Renderer* render) {
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}

		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i];
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if(go->box.Contains( (float)mouseX, (float)mouseY ) ) {
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
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos = Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ).Soma( mouseX, mouseY );
				AddObject((int)objPos.x, (int)objPos.y,render);
			}
		}
	}
}
