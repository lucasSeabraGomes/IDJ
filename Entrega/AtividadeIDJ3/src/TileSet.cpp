/*
 * TileSet.cpp
 *
 *  Created on: 8 de jul. de 2022
 *      Author: newlo
 */

#include "TileSet.h"

TileSet::TileSet(int tileWidth , int tileHeight,std::string file,SDL_Renderer* render,Resources* recursos) {

	// TODO Auto-generated constructor stub
	this->tileHeight=tileHeight;
	this->tileWidth=tileWidth;
	this->tileSet=new Sprite(file,render,nullptr,recursos);
	this->columns=(this->tileSet->GetWidth()/(this->tileWidth));
	this->rows=(this->tileSet->GetHeight()/(this->tileHeight));
}

TileSet::~TileSet() {
	if(this->tileSet!=nullptr){
		this->tileSet->~Sprite();
		this->tileSet=nullptr;
	}
	// TODO Auto-generated destructor stub
}
 int TileSet::GetTileWidth(){
	 return this->tileWidth;
 }
 int TileSet::GetTileHeight(){
 	 return this->tileHeight;
  }
 void TileSet::RenderTile(int index,float x,float y,SDL_Renderer* render){
	 if(index<=(this->rows*this->columns)-1){
		index=index-1;
		if(index<0){
			index=(this->rows*this->columns)-1;
		}
		SDL_Rect dstrect;
		dstrect.h=this->tileHeight;
		dstrect.w=this->tileWidth;
		dstrect.x=x;
		dstrect.y=y;
		int tileRow,tileColum;
		tileRow=index/this->columns;
		tileColum=index%this->columns;
		this->tileSet->SetClip((tileColum*this->tileWidth), (tileRow*this->tileHeight), this->tileWidth, this->tileHeight);
		this->tileSet->Render(render, dstrect);
	 }
 }
