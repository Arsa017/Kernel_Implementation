/*
 * PCB.h
 *
 *  Created on: Jul 29, 2020
 *      Author: OS1
 */

#ifndef OSPROJ_PCB_H_
#define OSPROJ_PCB_H_

#include "Thread.h"
#include "Idle.h"
#include "List.h"
#include "dos.h"
#include "Timer.h"
#include "lckdef.h"
#include "SCHEDULE.h"
#include <stdlib.h>


//typedef int NULL = 0;



class PCBelem {
public:
	Thread* t;
	ID id;

	PCBelem(Thread* t_, ID id_) {	// konstruktor
		this->t = t_;
		this->id = id_;
	}
};

class PCB {
public:
	PCB();
	PCB(Thread* t, StackSize stackSize, Time timeSlice);
	~PCB();

	unsigned int* stack;
	volatile unsigned int bp;
	volatile unsigned int ss;
	volatile unsigned int sp;
	unsigned int timeSlice;
//	Time passedTime;	// koliko dugo se nit izvrsava

	int blockFlag; // za niti koje su vremenski blokirane na semaforu

	StackSize stackSize;
	static const int NEW, READY, BLOCKED, TERMINETED;	// moguca stanja niti, blocked stanje i u slucaju da nit spava
	volatile int state;	// stanje trenutne niti
	Thread* myThread; // moja nit

	static PCB* running;
	static int nID;		// jedinstveni celobrojni identifikator
	ID id;
	/*volatile*/ static Idle* idle; // neaktivna nit

	const int getID() const { return id; }
	void stackCreate();		// inicijalizacija steka
	static void wrapper();	// f-ja nad kojom se nit izvrsava
	static Thread* start;	// globalni pokazivac na nit

	static Lista* PCBlista; // staticka lista svih PCB-ova;

	static Thread* getById(ID id); // dohvatanje niti za zadati ID
	void waitToComplete();

	/*static*/ Lista* waitToCompleteList;

};

#endif /* OSPROJ_PCB_H_ */
