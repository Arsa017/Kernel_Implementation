#ifndef _IVTEntry_h_
#define _IVTEntry_h_

#include "Event.h"
#include "iostream.h"
/*
// IVTNo je broj ulaza za koji se generisu definicije
// callold je logicka vrednost koja govori da li treba pozivati staru p. rutinu
#define PREPAREENTRY(IVTNo,callold)\
		void interrupt inter##IVTNo(...);\
		IVTEntry newEntry##IVTNo(IVTNo, inter##IVTNo);\
		void interrupt inter##IVTNo(...){\
			newEntry##IVTNo.signal();\
			if(callold==1)\
				newEntry##IVTNo.oldRoutine();\
		}\
*/
typedef void interrupt (*pInterrupt)(...);

class IVTEntry {
public:
	IVTEntry(IVTNo ivtNo_, pInterrupt intr);
	~IVTEntry();

	static pInterrupt routines[256]; // tabela prekidnih rutina
	static KernelEv* events[256];

	void oldRoutine();
	void signal();

private:
	IVTNo ivtNo; // broj ulaza u tabelu prekidnih rutina
};


// IVTNo je broj ulaza za koji se generisu definicije
// callold je logicka vrednost koja govori da li treba pozivati staru p. rutinu
#define PREPAREENTRY(IVTNo,callold)\
		void interrupt inter##IVTNo(...);\
		IVTEntry newEntry##IVTNo(IVTNo, inter##IVTNo);\
		void interrupt inter##IVTNo(...){\
			newEntry##IVTNo.signal();\
			if(callold==1)\
				newEntry##IVTNo.oldRoutine();\
		}\


#endif
