/*
 * Rect.h
 *
 *  Created on: 2 de jul. de 2022
 *      Author: newlo
 */

#ifndef SRC_RECT_H_
#define SRC_RECT_H_

class Rect {
public:
	Rect();
	virtual ~Rect();
	int x;
	int y;
	int w;
	int h;
	bool Contains(float X, float Y);
};

#endif /* SRC_RECT_H_ */
