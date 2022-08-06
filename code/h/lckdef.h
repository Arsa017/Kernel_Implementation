/*
 * lckdef.h
 *
 *  Created on: Aug 5, 2020
 *      Author: OS1
 */

#ifndef OSPROJ_LCKDEF_H_
#define OSPROJ_LCKDEF_H_
#include "timer.h"

// kriticne sekcije
// omogucene su ugnjezdenje petlje
// ? zabrana preotimanja bez zabrane prekida

#define lock  asm pushf;  \
              asm cli;

#define unlock asm popf;

#define lockF lockFlag--;

#define unlockF lockFlag++;\
	if((dispatchFlag == 1) && (lockFlag == 1))\
	dispatch();


#endif /* OSPROJ_LCKDEF_H_ */
