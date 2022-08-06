/*
 * Timer.cpp
 *
 *  Created on: Aug 1, 2020
 *      Author: OS1
 */

#include "Timer.h"
#include "PCB.h"
#include "Schedule.h"
#include "Thread.h"
#include "lckdef.h"
#include "dos.h"
//#include "main.h"
#include "KernSem.h"
#include <stdlib.h>
#include<stdio.h>
#include <iostream.h>

typedef void interrupt (*pInterrupt)(...); // potpis interrupt rutine za rad sa setvect() i getvect()

volatile unsigned tbp;
volatile unsigned tss;
volatile unsigned tsp;
volatile unsigned cntr = 1;
volatile unsigned lockFlag = 1;		// softLock = lockFlag
// 0 za 55 ms i prekid od tajmera,  1 za dispatch()-eksplicitna promena konteksta, 2 za waitToComplete()
volatile int dispatchFlag = 0;


pInterrupt oldTimerISR;

#include <DOS.H>
#include <STDIO.H>
#include <STDARG.H>

int syncPrintf2(const char *format, ...)
{
	int res;
	va_list args;
	lock;
		va_start(args, format);
	res = vprintf(format, args);
	va_end(args);
	unlock;
		return res;
}



void interrupt timer(...) {

	if(dispatchFlag == 0 && cntr >0) cntr--; // smanjujemo brojac posto je stigao prekid od tajmera

	if(dispatchFlag == 0) {		// ako nije eksplicitno zahtevana promena konteksta onda zovemo staru prekidnu rutinu
		KernelSem::azurirajTimeoutListu();
	}


	// dispatchFlag != 0 -> context_switch_on_demand
	if(dispatchFlag != 0 || (cntr == 0 && PCB::running->timeSlice !=0  /*&& lockFlag==1*/)) {	// ako je isteklo vreme za izvrsavanje niti ili ako je dispatchFlag != 0
			//if(lockFlag == 1 ) {
			//	dispatchFlag = 0;

				asm {
						//mov tbp, bp
						mov tss, ss
						mov tsp, sp
						mov tbp, bp
					}
				//PCB::running->bp = tbp;
				PCB::running->ss = tss;
				PCB::running->sp = tsp;
				PCB::running->bp = tbp;

				// U rasporedjivac ne sme da se nadje "zaludna" nit, nit koja je zavrsena kao ni nit koja ceka na waitToComplete() neke druge niti
				if (PCB::running != PCB::idle->getPCB() &&  PCB::running->state!=PCB::TERMINETED && PCB::running->state!=PCB::BLOCKED && dispatchFlag != 2) {
					Scheduler::put((PCB*)PCB::running);
				}
	/*		//	lock
				//cout << "==== PUCA promena konteksta ===" << endl;
				//unlock
				// ako je lista spremnih niti u rasporedjivacu prazna, onda running treba da pokazuje na "zaludnu nit"
	*/			//PCB::running = (PCB*)Scheduler::get();

				if((PCB::running = (PCB*)Scheduler::get()) == 0/* PCB::running == 0*/) {
		//			lock
		//			cout << "=== Idle nit ===" << endl;
		//			unlock
					PCB::running = (PCB*)PCB::idle->getPCB();
				//	PCB::idle->start();
				}

			/*	// kad running pokazuje na Idle nit, kako da po ubacivanju u Scheduler povratimo kontekst te ubacene niti

				// sada running pokazuje na novu nit koja ce se izvrsavati pa restauriramo njen kontekst

			*/	//cout << "==== PUCA promena konteksta ===" << endl;

				//tbp = PCB::running->bp;
				tss = PCB::running->ss;
				tsp = PCB::running->sp;
				tbp = PCB::running->bp;
				cntr = PCB::running->timeSlice; // podesimo novu vrednost brojaca

				asm {
						//mov bp, tbp
						mov ss, tss
						mov sp, tsp
						mov tbp, bp
				}
				//dispatchFlag = 0;

			//} else
			//dispatchFlag = 1;
	}

	if(dispatchFlag == 0) {		// ako nije eksplicitno zahtevana promena konteksta onda zovemo staru prekidnu rutinu

		tick();  				// f-ja se poziva kada pristigne prekid od hardverskog casovnika na svakih 55ms
	//	cout << "==== tick() === " << endl;
	//	asm int 60h;
	//	KernelSem::azurirajTimeoutListu();
		asm int 60h;
	//	asm int 60h; // pozivanje stare prekidne rutine se
		// mora obaviti na svakih 55ms
	} else
		dispatchFlag = 0; // --> mora da se obrise flag !!!!
}

void timerInic() {

	lock;
#ifndef BCC_BLOCK_IGNORE	 // F-je iz zaglavlja dos.h
	oldTimerISR = getvect(0x8);	 // pamtim staru rutinu

	setvect(0x8, timer);			 // postavlja novu rutinu
	setvect(0x60, oldTimerISR);	 // postavlja staru rutinu na ulaz 60h

#endif

	unlock;
}

void timerRestore() {
	lock;
#ifndef BCC_BLOCK_IGNORE
	setvect(0x8, oldTimerISR);	// restaurira staru prekidnu rutinu u ulaz 8h
#endif
	unlock;
}

void timerDispatch() {
	lock;
	dispatchFlag = 1;	// "svestan" (eksplicitan) zahtev za promenu konteksta kojem odgovara vrednost flega = 1
	asm int 08h;
	unlock;
}

void timerWait() {
//	lock;
	dispatchFlag = 2;	// vrednost flega odgovara vrednosti za promenu konteksta pri pozivu f-je waitToComplete()
	asm int 08h;
//	unlock;
}


//void tick() {}
