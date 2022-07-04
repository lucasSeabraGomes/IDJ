/*
 * Game.cpp
 *
 *  Created on: 16 de jun. de 2022
 *      Author: newlo
 */

#include "Game.h"


Game* Game::instance=nullptr;

Game::Game(string title , int width, int height ) {
	this->width=width;
	this->height=height;
	this->title=title;
	//inicializa o sdl
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
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
	   this->window = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,0);
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
	//inicializa state
	this->state=new State();
	this->state->LoadAssets(this->GetRenderer(),width,height);
	this->Run(0);
}

Game::~Game() {

	   if(this->state!=nullptr){
		   cout<<"removendo state\n";
		   this->state->~State();
		   this->state=nullptr;
	   }
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
	   free(this);
}

Game& Game::GetInstance (){
	if(Game::instance==nullptr){
		cout<<"Novo jogo\n";
		Game::instance = new Game("Lucas Seabra Gomes Oliveira170039951",1024,600);
	    }
	else{
		cout<<"jogo verificado com sucesso\n";
	}
	return *Game::instance;
}
SDL_Renderer* Game::GetRenderer (){
	return this->renderer;
}
State& Game::GetState (){
	return *this->state;
}
void Game::Run(int i){
	this->state->Update(0,this->GetRenderer());
	this->state->Render(this->GetRenderer());
    SDL_RenderPresent(this->GetRenderer());
	if(i>100 or this->state->QuitRequested()){
		return;
	}else
	{
		this->Run(i+1);
	}
	SDL_Delay(33);
}
