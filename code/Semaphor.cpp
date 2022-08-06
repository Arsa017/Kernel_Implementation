#include "Semaphor.h"
#include "KernSem.h"
#include "lckdef.h"

Semaphore::Semaphore(int init) {
	lock
	myImpl = new KernelSem(this, init);
	unlock
}

Semaphore::~Semaphore() {
	lock
	delete myImpl/*->~KernelSem()*/;
	unlock
}

int Semaphore::wait(Time maxTimeToWait) {
	lock
	//printf("---- 0 -----;\n");
	int ret = myImpl->wait(maxTimeToWait);
	unlock
	return ret ;
}

int Semaphore::signal(int n) {
	lock
	int ret = myImpl->signal(n);
	unlock
	return ret;
}

int Semaphore::val() const {
	return myImpl->val();
}
