/*
 * Camera.h
 *
 *  Created on: 16 de jul. de 2022
 *      Author: newlo
 */

#ifndef SRC_CAMERA_H_
#define SRC_CAMERA_H_
#include "GameObject.h"
#include "Vec2.h"
#include "InputManager.h"
class Camera {
public:
	Camera();
	virtual ~Camera();
	void Update (float dt,int width, int height,InputManager manager);
	void Follow (GameObject* newFocus);
	void Unfollow ();
	Vec2 pos;
	Vec2 speed;
private:
	GameObject* focus;
};

#endif /* SRC_CAMERA_H_ */
