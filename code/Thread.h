/*
 * Thread.h
 *
 *  Created on: Jul 29, 2020
 *      Author: OS1
 */

#ifndef _thread_h_
#define _thread_h_

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms
typedef int ID;

class PCB; // Kernel's implementation of user's thread

class Thread {

public:
	void start();	// +
	void waitToComplete(); // +
	virtual ~Thread();	// +

	ID getID(); // +
	static ID getRunningId(); // +
	static Thread* getThreadById(ID id);	// +

protected:
	friend class PCB;
	friend class Idle;
	Thread(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	virtual void run() {};	// metoda koju nit izvrsava dok radi

private:
	PCB* myPCB;
};

void dispatch();

#endif
