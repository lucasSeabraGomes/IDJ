/*
 * CameraFollower.h
 *
 *  Created on: 16 de jul. de 2022
 *      Author: newlo
 */

#ifndef SRC_CAMERAFOLLOWER_H_
#define SRC_CAMERAFOLLOWER_H_
#include "Component.h"
class CameraFollower: public Component {
public:
	CameraFollower();
	CameraFollower(GameObject* go);
	virtual ~CameraFollower();
	void Update(float dt);
	void Render(SDL_Renderer* render,Vec2 camera);
	bool Is(string tipo);
};

#endif /* SRC_CAMERAFOLLOWER_H_ */
