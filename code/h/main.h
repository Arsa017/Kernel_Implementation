/*

int syncPrintf(const char *format, ...)
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
*/

/*

#include <iostream.h>
#include <stdlib.h>
#include <assert.h>

#include "bounded.h"
#include "intLock.h"
#include "keyevent.h"
#include "user.h"
//#include "Event.h"
//#include "Semaphor.h"
#include "Thread.h"
#include "PCB.h"
#include "Timer.h"
#include "Idle.h"
#include "lckdef.h"
#include <DOS.H>
#include <STDIO.H>
#include <STDARG.H>
#include <stdlib.h>
//#include "Semaphor.h"
#include "Event.h"
#include "IVTEntry.h"
#include "KernelEv.h"




int main(int argc, char* argv[]) {
	timerInic();
	PCB::idle->start();
	userMain(argc, argv);
	timerRestore();
	return 0;
}



*/


//#endif /* OSPROJ_MAIN_H_ */


