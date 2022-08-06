#ifndef _KerSem_
#define _KerSem_

#include "List.h"
#include "lckdef.h"
#include "PCB.h"
#include "Thread.h"
#include "SCHEDULE.h"

typedef unsigned int Time;
class Semaphore;

class TimeoutElem {
public:
	PCB* blokiranaNit;
	Time vremeBlokiranja;

	TimeoutElem(PCB* nit, Time vreme) {
		this->blokiranaNit = nit;
		this->vremeBlokiranja = vreme;
		//printf("--- Kreira objekat ---\n");
		//asm cli
	}
};

class KernelSem {
public:
	KernelSem(Semaphore* sem_, int init);
	~KernelSem();

	int wait(Time maxTimeToWait);
	int signal(int n=0);

	int val() const;

	static void azurirajTimeoutListu();

//private:
	Semaphore* sem;
	volatile int value;
	Lista* blockList;
	Lista* timeoutList;
	static Lista* semList;
};

#endif

