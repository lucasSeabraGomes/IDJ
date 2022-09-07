/*
 * Vec2.h
 *
 *  Created on: 2 de jul. de 2022
 *      Author: newlo
 */

#ifndef SRC_VEC2_H_
#define SRC_VEC2_H_
#include <cmath>
#include <math.h>
#define PI 3.14159265
class Vec2 {
public:
	Vec2();
	Vec2(float x,float y);
	virtual ~Vec2();
	float x;
	float y;
	Vec2 GetRotated(float ang);
	Vec2 Soma(float x, float y);
	Vec2 Subtract(float x, float y);
	float GetAngle(Vec2 comparativo);
	float GetDistance(Vec2 comparativo);
	Vec2 operator+(const Vec2& rhs) const {
	  return Vec2(x + rhs.x, y + rhs.y);
	 }

	Vec2 operator-(const Vec2& rhs) const {
	    return Vec2(x - rhs.x, y - rhs.y);
	 }

	 Vec2 operator*(const float rhs) const {
	    return Vec2(x * rhs, y * rhs);
	 }
};

#endif /* SRC_VEC2_H_ */
