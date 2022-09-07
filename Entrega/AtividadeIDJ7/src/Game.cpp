/*
 * Game.cpp
 *
 *  Created on: 16 de jun. de 2022
 *      Author: newlo
 */

#include "Game.h"


Game* Game::instance;
Game::Game(string title , int width, int height ) {
	this->width=width;
	this->height=height;
	this->title=title;
	this->dt=0;
	this->frameStart=0;
	//inicializa o sdl
	if (SDL_Init(SDL_INIT_EVERYTHING ) != 0) {
	    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
	}
	//realiza outras inicializações apenas se o sdl funcionar
	else{
		int imflags=IMG_INIT_JPG  |  IMG_INIT_PNG  |  IMG_INIT_TIF;
		int iminitted=IMG_Init(imflags);
		if((iminitted&imflags) != imflags) {
		    printf("IMG_Init: Failed to init required jpg and png support!\n");
		    printf("IMG_Init: %s\n", IMG_GetError());
		    // handle error
		}
		int flags=MIX_INIT_OGG|MIX_INIT_MOD;
		//inicializa o mix sdl
	   int initted=Mix_Init(flags);
	   if((initted&flags) != flags) {
	       printf("Mix_Init: Falha ao inicializar o suporte necessário para ogg e mod!\n");
	       printf("Mix_Init: %s\n", Mix_GetError());
	       // trata o erro
	   }else
	   {
		   //inicializa o audio
		   if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)!= 0) {
			   printf("Mix_OpenAudio error: %s\n", Mix_GetError());
		   }
		   else
		   {
		   		cout<<"audio inicializado com sucesso\n";
		   }
		   //aloca 2 sons simultaneos
		   Mix_AllocateChannels(32);
	   }
	   //inicializa janela
	   this->window = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_INPUT_GRABBED);
	   if(this->window ==nullptr ){
		   printf("Falha ao inicializar janela!\n");
	   }
	   else{
		   //caso a janela esteja funcionando inicializa render
		   this->renderer = SDL_CreateRenderer(this->window ,-1, SDL_RENDERER_ACCELERATED);
		   if(this->renderer ==nullptr ){
	   		   printf("Falha ao inicializar render!\n");
	   	   }
		   else
		   {
			   cout<<"video inicializado com sucesso\n";
		   }
	   }
	}
	 TTF_Init();
	this->recursos=new Resources();
	this->input= &InputManager::GetInstance();
	//inicializa state
	this->camera=new Camera();
	this->storedState=nullptr;
	this->gameData=GameData();
}

Game::~Game() {

	if(this->stateStack.size()>0){
			  this->stateStack.clear();
		  }
	this->storedState=nullptr;
		if(this->camera!=nullptr){
			this->camera->~Camera();
			this->camera=nullptr;
		}

		if(this->input!=nullptr){
			this->input->~InputManager();
			this->input=nullptr;
		}
	   if(this->recursos!=nullptr){
			this->recursos->~Resources();
			this->recursos=nullptr;
		}
	   TTF_Quit();
	   if(this->renderer!=nullptr){
		   SDL_DestroyRenderer(this->renderer);
		   this->renderer=nullptr;
	   }
	   if(this->window!=nullptr){
		   SDL_DestroyWindow(this->window);
		   this->window=nullptr;
	   }
	   Mix_CloseAudio();
	   Mix_Quit();
	   IMG_Quit();
	   SDL_Quit();
	   cout<<"fechando jogo\n";
}

Game* Game::GetInstance (){
	if(Game::instance==nullptr){
		cout<<"Novo jogo\n";
		Game::instance = new Game("Lucas Seabra Gomes Oliveira170039951",1024,600);
	    }
	return Game::instance;
}
void  Game::Push ( State* state){
	this->storedState=state;
}
SDL_Renderer* Game::GetRenderer (){
	return this->renderer;
}
State* Game::GetState (){
	State* retorno= this->stateStack[this->stateStack.size()-1].get();
	return retorno;
}
void Game::Run(){
	State* inicial=new TitleState();
	this->stateStack.push_back(std::shared_ptr<State>(inicial));
	this->GetState ()->Start();
	while(!this->GetState ()->QuitRequested()or this->stateStack.size()==0){
			this->CalculateDeltaTime();
			this->GetState ()->Update(this->GetDeltaTime());
			this->GetState ()->Render();
			SDL_RenderPresent(this->GetRenderer());
			if(this->GetState ()->PopRequested()){
				this->stateStack.erase(this->stateStack.end());
			}
			if(this->storedState!=nullptr){
				this->stateStack.push_back(std::shared_ptr<State>(this->storedState));
				this->GetState ()->Start();
				this->storedState=nullptr;
			}

			SDL_Delay(33);
		}

}
void Game::CalculateDeltaTime(){
	int time=(int)SDL_GetTicks ();
	this->dt=(time-this->frameStart);
	this->frameStart=time;
}
float Game::GetDeltaTime(){
	return this->dt;
}