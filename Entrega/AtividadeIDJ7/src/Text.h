/*
 * Text.h
 *
 *  Created on: 5 de set. de 2022
 *      Author: newlo
 */

#ifndef SRC_TEXT_H_
#define SRC_TEXT_H_
#include "Component.h"
enum TextStyle {
	SOLID,
	SHADED,
	BLENDED
};
class Text: public Component {
public:
	Text();
	Text(GameObject* associated ,string fontFile , int  fontSize , TextStyle  style , string  text ,  SDL_Color color);
	virtual ~Text();
	void Render(SDL_Renderer* render,Vec2 camera );
	void Update(float dt);
	bool Is(string tipo);
	void SetText (string text ) ;
	void SetColor (SDL_Color color  ) ;
	void SetStyle (TextStyle style  ) ;
	void SetFontFile (string fontFile) ;
	void SetFontSize (int fontSize ) ;
private:
	void RemakeTexture () ;
	TTF_Font* font;
	SDL_Texture* texture;
	string text;
	TextStyle style;
	string fontFile;
	int fontSize;
	SDL_Color color;
	bool invisivel;
	float MilsecondsToChange;
};

#endif /* SRC_TEXT_H_ */
