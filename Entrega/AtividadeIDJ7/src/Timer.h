/*
 * Timer.h
 *
 *  Created on: 12 de ago. de 2022
 *      Author: newlo
 */

#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_

class Timer {
public:
	Timer();
	virtual ~Timer();
	void Update(float dt );
	void Restart();
	float Get();
private:
	float time;
};

#endif /* SRC_TIMER_H_ */
