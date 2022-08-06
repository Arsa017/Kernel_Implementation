/*
 * Timer.h
 *
 *  Created on: Aug 1, 2020
 *      Author: OS1
 */

#ifndef OSPROJ_TIMER_H_
#define OSPROJ_TIMER_H_

#include "lckdef.h"
#include "dos.h"
#include "Thread.h"
//#include "KernSem.h"

class KernelSem;

void interrupt timer(); // prekidna rutina za tajmer

void timerInic();	// inicijalizacija i restauracija prekidne rutine
void timerRestore();// u tabeli prekidnih rutina

void timerDispatch();
void timerWait();

extern volatile int dispatchFlag;
extern volatile unsigned lockFlag;

void tick();
#endif /* OSPROJ_TIMER_H_ */
