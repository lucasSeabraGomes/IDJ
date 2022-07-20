/*
 * TileMap.cpp
 *
 *  Created on: 8 de jul. de 2022
 *      Author: newlo
 */

#include "TileMap.h"
#include <fstream>

TileMap::TileMap() {
	// TODO Auto-generated constructor stub

}
TileMap::TileMap( GameObject* associated, std::string file,TileSet* tileSet){
	this->tileSet=tileSet;
	this->associated=associated;
	this->Load(file);
}
TileMap::~TileMap() {
	// TODO Auto-generated destructor stub
}
void  TileMap::Load( std::string file){
	cout<<"teste";
	   int valores[3];
	   FILE * arquivo;
	    char base[20];
	    char converter[3][3];
	    arquivo = fopen(file.c_str(), "r");
	    fgets(base, 20, arquivo);
	    int aux=0;
	    int aux2=0;
	    int aux3;
	    for(int i=0;base[i]!='\n' and i<20;i++){
	    	if(base[i]==','){
	    		valores[aux]=atoi(converter[aux]);
	    		aux++;
	    		aux3=aux2;
	    		aux2=0;
	    	}
	    	else{
	    		converter[aux][aux2]=base[i];
	    		aux2++;
	    	}
	    }
	    char* cMap;
	    cMap=(char*)malloc(valores[0]*(aux3+1)*sizeof(char));
	    char numeros[3];
	    while(!feof(arquivo)){
	    	fgets(cMap, valores[0]*(aux3+1)*sizeof(char), arquivo);
	    	aux2=0;
	    	for(unsigned int i=0;cMap[i]!='\n' and i<valores[0]*(aux3+1)*sizeof(char);i++){
	    	    	if(cMap[i]==','){
	    	    		this->tileMatrix.push_back(atoi(numeros));
	    	    		aux2=0;
	    	    	}
	    	    	else{
	    	    		numeros[aux2]=cMap[i];
	    	    		aux2++;
	    	    	}
	    	    }
	    }
	    this->mapWidth=valores[0];
	    this->mapHeight=valores[1];
		this->mapDepth=valores[2];
	    free(cMap);
	    fclose(arquivo);
}
void TileMap::SetTileSet( TileSet* tileSet){
	this->tileSet=tileSet;
}
void TileMap::Render(SDL_Renderer* render,Vec2 camera){
	for(int i=0;i<this->mapDepth;i++){
		this->RenderLayer(render, i, camera.x*(i+1), camera.y*(i+1));
	}
}


int TileMap::GetWidth  (){
	return this->mapWidth;
}
int TileMap::GetHeight  (){
	return this->mapHeight;
}
int TileMap::GetDepth  (){
	return this->mapDepth;
}
int TileMap::At(int x,int y,int z){
	return ((this->mapWidth*y)+x)+(z*this->mapHeight*this->mapWidth);
}
void TileMap::RenderLayer(SDL_Renderer* render,int layer, int cameraX,int cameraY){
	int index=layer*this->mapHeight*this->mapWidth;
	int i=0;
	int j=0;
	while(index<(layer+1)*this->mapHeight*this->mapWidth){
		this->tileSet->RenderTile(this->tileMatrix[index], i*64+cameraX, j*64+cameraY, render);
		index++;
		i++;
		if(i==25){
			j++;
			i=0;
		}
	}
}
