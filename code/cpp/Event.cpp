#include "Event.h"
#include "KernelEv.h"
#include "IVTEntry.h"
#include "lckdef.h"

Event::Event(IVTNo ivtNo) {
	lock
	myImpl = new KernelEv(ivtNo);
	unlock
}

Event::~Event() {
	lock
	delete myImpl;
	unlock
}

void Event::signal() {
	lock
	myImpl->signal();
	unlock
}

void Event::wait() {
	lock
	myImpl->wait();
	unlock
}
