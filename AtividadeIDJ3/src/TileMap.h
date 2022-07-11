/*
 * TileMap.h
 *
 *  Created on: 8 de jul. de 2022
 *      Author: newlo
 */

#ifndef SRC_TILEMAP_H_
#define SRC_TILEMAP_H_
#include "TileSet.h"
#include <vector>
#include <stdio.h>
#include <conio.h>
class TileMap:public Component {
public:
	TileMap();
	TileMap( GameObject* associated, std::string file,TileSet* tileSet);
	virtual ~TileMap();
	void  Load( std::string file);
	void SetTileSet( TileSet* tileSet);
	int At(int x,int y,int z);
	void Render(SDL_Renderer* render);
	void RenderLayer(SDL_Renderer* render,int layer, int cameraX,int cameraY);
	int GetWidth  ();
	int GetHeight ();
	int GetDepth  ();
private:
	std::vector<int> tileMatrix;
	TileSet* tileSet;
	int mapWidth;
	int mapHeight;
	int mapDepth;
};

#endif /* SRC_TILEMAP_H_ */
