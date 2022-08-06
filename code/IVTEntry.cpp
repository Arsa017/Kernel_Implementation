#include "IVTEntry.h"
#include "KernelEv.h"
#include "dos.h"
#include <iostream.h>

KernelEv* IVTEntry::events[256] = {0};
pInterrupt IVTEntry::routines[256] = {0};

IVTEntry::IVTEntry(IVTNo ivtNo_, pInterrupt intr) {
	this->ivtNo = ivtNo_;
	IVTEntry::routines[ivtNo_] = intr;
}

IVTEntry::~IVTEntry() {
	// proveriti; mozda nije potrebno
//	IVTEntry::events[this->ivtNo]->~KernelEv();
//	IVTEntry::routines[this->ivtNo]=0;
}

// kada se prekidna rutina pozove ona poziva signal() za dogadjaj koji je
// vezan za taj ulaz u tabeli prekidnih rutina
void IVTEntry::signal() {
	if(IVTEntry::events[ivtNo]) {
		IVTEntry::events[ivtNo]->signal();
	} else
		cout << "=== Greska IVT signal() ===";
}

void IVTEntry::oldRoutine() {
	if(IVTEntry::events[ivtNo]) {
		IVTEntry::events[ivtNo]->oldRout();
	} else
		cout << "=== Greska IVT oldRoutine() ====";
}
