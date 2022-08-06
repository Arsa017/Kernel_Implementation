/*
 * Idle.h
 *
 *  Created on: Aug 1, 2020
 *      Author: OS1
 */

#ifndef OSPROJ_IDLE_H_
#define OSPROJ_IDLE_H_

#include "Thread.h"

class Idle : public Thread {
public:
	friend class Thread;
	Idle();
	virtual void run();
	PCB* getPCB();
	//virtual ~Idle();
};

#endif /* OSPROJ_IDLE_H_ */
