/*
 * Thread.cpp
 *
 *  Created on: Jul 29, 2020
 *      Author: OS1
 */

#include "Thread.h"
#include "Timer.h"
#include "PCB.h"
#include "lckdef.h"
#include <stdlib.h>
#include "Schedule.h"

Thread::Thread(StackSize stackSize, Time timeSlice) {
	lock;
	myPCB = new PCB(this, stackSize, timeSlice);
	unlock;
}

Thread::~Thread() {
	lock;
	//waitToComplete();
	if(myPCB!= NULL) delete myPCB;
	unlock;
}

ID Thread::getID() {
	return myPCB->getID();
}

ID Thread::getRunningId() {
	return PCB::running->getID();
}

Thread* Thread::getThreadById(ID id) {
	return PCB::getById(id);
}

void dispatch() {	// prekid od tajmera
	lock;
	timerDispatch();
	unlock;
}

void Thread::start() {
	lock;
	myPCB->state = PCB::READY;	// nit je spremna za izvrsavanje
	myPCB->stackCreate();	// kreiranje steka za nit

	if(this != PCB::idle)
		Scheduler::put((PCB*)myPCB);	// smestamo nit u rasporedjivac
	unlock;
}

void Thread::waitToComplete() {
	lock;

	if(this == PCB::idle) { unlock; return; }	// ako je nit na koju cekamo "zaludna nit", ne cekamo njen zavrsetak
	if(myPCB == (PCB*)PCB::running) { unlock; return; } // ako running nit za sebe samu poziva waitToComplete()
	if(myPCB->state == PCB::TERMINETED) { unlock; return; } // ako je nit zavrsila poso

	// u svim ostalim slucajevima running nit se smesta u red blokiranih niti i ceka na zavresetak niti ciju waitToComplete metodu je pozvala

	//printf("---- Wait() -----;\n");
	myPCB->waitToComplete();


//	timerWait();	// da bi promenili promenili kontekst i oduzeli procesor trenutno izvrsavanoj niti
					// posto ona ceka na waitToComplete metodu neke niti tj. da druga nit zavrsi posao
	unlock;
}
