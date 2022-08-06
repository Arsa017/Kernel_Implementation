/*
 * KernelEv.cpp
 *
 *  Created on: Oct 3, 2020
 *      Author: OS1
 */

#include "KernelEv.h"
#include "iostream.h"

// kreiranje dogadjaja za zadati ulaz u tabeli prekidnih rutina
KernelEv::KernelEv(IVTNo ivtNo_) {
	lock

	this->value = 0;
	this->ivtNo = ivtNo_;
	IVTEntry::events[ivtNo_]=this;
	this->myPCB = (PCB*) PCB::running;
	this->blck=0;
//	IVTEntry::events[ivtNo_]=this;
	// cuvamo staru prekidnu rutinu i podmecemo svoju
	#ifndef BCC_BLOCK_IGNORE
	this->oldRout = getvect(ivtNo_);
	setvect(ivtNo_, IVTEntry::routines[ivtNo_]);
	#endif
	unlock
}

KernelEv::~KernelEv() {
	lock
	IVTEntry::events[this->ivtNo]=0;
	// restauriramo staru prekidnu rutinu
	#ifndef BCC_BLOCK_IGNORE
	setvect(ivtNo, oldRout);
	#endif
	unlock
}

// opracija signal() deblokira nit blokiranu na dogadjaju
// ovu operaciju poziva prekidna rutina koja je vezana za isti ulaz kao i dogadjaj
void KernelEv::signal() {
	lock
	if(blck==0) {
		value=1;
	} else {
		blck->state=PCB::READY;
		Scheduler::put((PCB*)blck);
		blck=0;
		timerDispatch(); // ekskluzivna promena konteksta, dispatchFlag = 1;
	}
	unlock
}

// operacija wait() blokira pozivajucu nit
void KernelEv::wait() {
	lock
	// ako je running nit kreator dogadjaja
	if(myPCB == PCB::running) {
		if(value == 0) {
			myPCB->state = PCB::BLOCKED;
			blck=myPCB; // pamtimo ko je kreator dogadjaja
		//	timerDispatch();
			timerWait();
		}
		if(value == 1)
			value = 0;
	}
	unlock
}


