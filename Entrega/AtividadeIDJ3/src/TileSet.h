/*
 * TileSet.h
 *
 *  Created on: 8 de jul. de 2022
 *      Author: newlo
 */

#ifndef TILESET_H_
#define TILESET_H_
#include "Sprite.h"

class TileSet {
public:
	TileSet();
	TileSet(int tileWidth , int tileHeight,std::string file,SDL_Renderer* render,Resources* recursos);
	virtual ~TileSet();
	void RenderTile(int index,float x,float y,SDL_Renderer* render);
	int GetTileWidth ();
	int GetTileHeight();
private:
	Sprite* tileSet;
	int rows ;
	int columns;
	int tileWidth;
	int tileHeight;
};

#endif /* TILESET_H_ */
