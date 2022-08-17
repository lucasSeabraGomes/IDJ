/*
 * Sprite.h
 *
 *  Created on: 21 de jun. de 2022
 *      Author: newlo
 */

#include "Component.h"
#include "Timer.h"




#ifndef SPRITE_H_
#define SPRITE_H_
class GameObject;
class Sprite: public Component{
public:
	Sprite();
	Sprite(GameObject* associated );
	Sprite(string file,SDL_Renderer* render,GameObject* associated,Resources* recursos,int frameCount =1,float frameTime =1,float selfDestruc=-1);
	virtual ~Sprite();
	void Open(string file,SDL_Renderer* render,Resources* recursos);
	void SetClip(int x, int y ,   int w, int h);
	void Render(SDL_Renderer* render,Vec2 camera);
	void Render(SDL_Renderer* render,SDL_Rect dstrect);
	int GetWidth();
	int GetHeight();
	bool IsOpen();
	bool Is(string tipo);
	void Update(float dt);
	Vec2 GetScale ();
	void SetScaleX (float scaleX,float  scaleY);
	void SetFrame (int frame);
	void SetFrameCount  (int frameCount );
	void SetFrameTime  (int frameTime );
	int frameCount;
	Timer selfDestructCount  ;
	float secondsToSelfDestruct;
private:
	SDL_Texture* texture;
	int width;
	int height;
	SDL_Rect clipRect;
	Vec2* scale ;
	int currentFrame;
	float timeElapsed;
	float frameTime;
};

#endif /* SPRITE_H_ */
