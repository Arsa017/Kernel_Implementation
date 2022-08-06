
#ifndef _KernelEv_h
#define _KernelEv_h

#include "Event.h"
#include "IVTEntry.h"
#include "PCB.h"
#include "Timer.h"
#include "lckdef.h"

class KernelEv {
public:
	KernelEv(IVTNo ivtNo_);
	~KernelEv();

	void signal();
	void wait();

	pInterrupt oldRout;

	PCB* myPCB; // nit koja je napravila event
	PCB* blck;	// pomocna nit
	IVTNo ivtNo;

private:
	int value; // vrednost binarnog semafora
};

#endif
