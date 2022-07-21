/*
 * Vec2.h
 *
 *  Created on: 2 de jul. de 2022
 *      Author: newlo
 */

#ifndef SRC_VEC2_H_
#define SRC_VEC2_H_
#include <cmath>
class Vec2 {
public:
	Vec2();
	Vec2(int x,int y);
	virtual ~Vec2();
	int x;
	int y;
	Vec2 GetRotated(float ang);
	Vec2 Soma(float x, float y);
};

#endif /* SRC_VEC2_H_ */
