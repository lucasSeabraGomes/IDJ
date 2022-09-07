/*
 * Text.cpp
 *
 *  Created on: 5 de set. de 2022
 *      Author: newlo
 */

#include "Text.h"
#include "GameObject.h"
#include "Game.h"
Text::Text() {
	// TODO Auto-generated constructor stub
}
Text::Text(GameObject* associated ,string fontFile , int  fontSize , TextStyle  style , string  text ,  SDL_Color color){
	this->fontFile=fontFile;
	this->fontSize=fontSize;
	this->style=style;
	this->text=text;
	this->color=color;
	this->font=TTF_OpenFont (fontFile.c_str(), fontSize);
	this->texture=nullptr;
	this->associated=associated;
	this->RemakeTexture();
	this->MilsecondsToChange=1000;
	this->invisivel=false;
}

Text::~Text() {
	// TODO Auto-generated destructor stub
	if(this->texture!=nullptr){
		SDL_DestroyTexture(this->texture);
		this->texture=nullptr;
	}
}
void Text::RemakeTexture () {
	if(this->texture!=nullptr){
		SDL_DestroyTexture(this->texture);
		this->texture=nullptr;
	}
	if(this->style==SOLID){
		SDL_Surface* surface= TTF_RenderText_Solid(this->font, this->text.c_str(), this->color);
		this->texture=SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(), surface);
		SDL_FreeSurface(surface);
	}
	if(this->style==SHADED){
		SDL_Surface* surface=TTF_RenderText_Shaded(this->font, this->text.c_str(),this->color, SDL_Color());
		this->texture=SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(), surface);
		SDL_FreeSurface(surface);
	}
	if(this->style==BLENDED){
		SDL_Surface* surface=TTF_RenderText_Blended(this->font, this->text.c_str(),this->color);
		this->texture= SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(), surface);
		SDL_FreeSurface(surface);
	}
	if(this->texture!=nullptr){
		SDL_QueryTexture(this->texture, NULL, NULL, &this->associated->box.w,&this->associated->box.h);
	}
}
void Text::SetFontFile (string fontFile) {
	TTF_CloseFont (this->font);
	this->font=nullptr;
	this->fontFile=fontFile;
	this->font=TTF_OpenFont (fontFile.c_str(), fontSize);
	this->RemakeTexture();
}
void Text::SetText (string text ) {
	this->text=text;
	this->RemakeTexture();
}
void Text::SetColor (SDL_Color color  ) {
	this->color=color;
	this->RemakeTexture();
}
void Text::SetStyle (TextStyle style  ) {
	this->style=style;
	this->RemakeTexture();
}
void Text::SetFontSize (int fontSize )  {
	this->fontSize=fontSize;
	this->font=TTF_OpenFont (fontFile.c_str(), fontSize);
	this->RemakeTexture();
}
void Text::Render(SDL_Renderer* render,Vec2 camera ){
	SDL_Rect clip=SDL_Rect();
	SDL_Rect sdlrect=SDL_Rect();
	clip.x=0;
	clip.y=0;
	clip.h=this->associated->box.h;
	clip.w=this->associated->box.w;


	sdlrect.x=this->associated->box.x;
	sdlrect.y=this->associated->box.y;
	sdlrect.h=this->associated->box.h;
	sdlrect.w=this->associated->box.w;
	if(this->texture!=nullptr and !invisivel){
		if(SDL_RenderCopy(render,this->texture,&clip,&sdlrect)<0){
			 SDL_Log("Unable to render: %s", SDL_GetError());
		}
	}
}
void Text::Update(float dt){
 this->MilsecondsToChange=this->MilsecondsToChange-dt;
 if(this->MilsecondsToChange<0){
	 if(this->invisivel){
		 this->invisivel=false;
	 }else{
	 	this->invisivel=true;
	 }
	 this->MilsecondsToChange=1000;
 }
}
bool Text::Is(string tipo){
	if(tipo.compare("Text")){
		return false;
	}
	else {
		return true;
	}
}
