/*
 * main.h
 *
 *  Created on: Aug 5, 2020
 *      Author: OS1
 */

#ifndef OSPROJ_MAIN_H_
#define OSPROJ_MAIN_H_
#include <iostream.h>
#include <stdio.h>
#include "Thread.h"
#include "PCB.h"
#include "Timer.h"
#include "Idle.h"
#include "lckdef.h"
#include <DOS.H>
#include <STDIO.H>
#include <STDARG.H>
#include <stdlib.h>
#include "Semaphor.h"
#include "Event.h"
#include "IVTEntry.h"
#include "KernelEv.h"

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

/*
class TestThread : public Thread
{
public:

	TestThread(): Thread() {};
	~TestThread()
	{
		waitToComplete();
	}
protected:

	void run();

};

void TestThread::run()
{
	syncPrintf("Thread %d: loop1 starts\n", this->getID());

	for(int i=0;i<32000;i++)
	{
		for (int j = 0; j < 32000; j++);
	}

	syncPrintf("Thread %d: loop1 ends, dispatch\n", this->getID());

	dispatch();

	syncPrintf("Thread %d: loop2 starts\n", this->getID());

	for (int k = 0; k < 20000; k++);

	syncPrintf("Thread %d: loop2 ends\n", this->getID());


}

class WaitThread: public Thread
{
private:
	TestThread *t1_,*t2_;

public:
	WaitThread(TestThread *t1, TestThread *t2): Thread()
	{
		t1_ = t1;
		t2_ = t2;
	};

	~WaitThread()
		{
			waitToComplete();
		}

protected:

	void run()
	{
		syncPrintf("Starting tests...\n");
		t1_->waitToComplete();
		syncPrintf("Test 1 completed!\n");
		t2_->waitToComplete();
		syncPrintf("Test 2 completed!\n");
	}
};


*/
//----------------------------------------------------------------------

/*
class TestThread : public Thread
{
public:

	TestThread(): Thread() {};
	~TestThread()
	{
		waitToComplete();
	}
protected:

	void run();

};


void TestThread::run()
{
	syncPrintf("Thread %d: loop1 starts\n", this->getID());

	for(int i=0;i<32000;i++)
	{
		for (int j = 0; j < 32000; j++);
	}

	syncPrintf("Thread %d: loop1 ends, dispatch\n", this->getID());

	dispatch();

	syncPrintf("Thread %d: loop2 starts\n", this->getID());

	for (int k = 0; k < 20000; k++);

	syncPrintf("Thread %d: loop2 ends\n", this->getID());

}
*/

//-------------------------------------------------------------------------
/*
int userMain(int argc, char** argv)
{
	PCB::running = new PCB(0, 1024, 1);

	timerInic();
	syncPrintf("User main starts\n");
//	for(int m = 0; m<30000; m++)
//		for(int j=0; j<30000; j++);
	//asm cli;

	TestThread t1,t2,t3,t4,t5,t6;
	WaitThread w(&t1,&t2);
	t1.start();
	t2.start();
	t3.start();
	t4.start();
	t5.start();
	t6.start();
	//t3.start();
	for(int m = 0; m<30000; m++)
			for(int j=0; j<30000; j++);
	w.start();
	syncPrintf("User main ends\n");
	while(1){};
	timerRestore();
	return 16;
}

int main() {
	return userMain(0, 0);
}
*/
//----------------------------------------------------------

/*const int n = 16;

//void tick(){}

class TestThread : public Thread
{
public:

	TestThread(): Thread(4096,2) {};
	~TestThread()
	{
		waitToComplete();
	}
protected:

	void run();

};

void TestThread::run()
{

	int buffer=2;
	printf("buffer size = %d \n", buffer);

	for(int i=0;i<32000;i++)
	{
		buffer = 4096/2048;
	//	printf("buffer size = %d \n", buffer);
		for (int j = 0; j < 1024; j++)
		{
			buffer = buffer*2;
			if(buffer%2)
				buffer = 2;
		}
	}

}


int userMain(int argc, char** argv)
{
	timerInic();
	syncPrintf("Test starts: %d threads.\n",n);
	int i;
	TestThread threads[n];
	for(i=0;i<n;i++)
	{
		threads[i].start();
	}
	for(i=0;i<n;i++)
	{
		threads[i].waitToComplete();
		syncPrintf("%d. Done!\n",Thread::getThreadById(i+10)->getID());
	}
	syncPrintf("Test ends.\n");
	while(1){};
	timerRestore();
	return 0;
}
*/
//-------------------------------------------------------
/*
volatile Time ts;
int i = 0;
void tick()
{
	syncPrintf("%d. timeSlice=%d\n",++i, ts);
}

class TestThread : public Thread
{
private:
	Time myTimeSlice;
public:

	TestThread(StackSize stackSize, Time timeSlice): Thread(stackSize,timeSlice), myTimeSlice(timeSlice) {};
	~TestThread()
	{
		waitToComplete();
	}
protected:

	void run();

};

void TestThread::run()
{
	for(unsigned i=0;i<10000;i++)
	{
		for(unsigned int j=0;j<10000;j++)
		{
			ts = myTimeSlice;
		}
	}
}


int userMain(int argc, char** argv)
{
	//timerInic();
	syncPrintf("Test starts.\n");
	//for(int m=0; m<10000; m++)
	//	for(int j=0; j<10000; j++);
	TestThread t1(64,1), t2(4096,32), t3(1024,16), t4(4096,0);
	t1.start();
	t2.start();
	t3.start();
	t4.start();
	//printf("==== PUCA ====\n");
	//asm cli
	t1.waitToComplete();
	t2.waitToComplete();
	t3.waitToComplete();
	t4.waitToComplete();
	syncPrintf("Test ends.\n");
	while(1){};
	//timerRestore();
	return 0;
}
*/

//---------------------------------------------------------

/*
const int n = 10;

//void tick(){}

class TestThread : public Thread
{
public:

	TestThread(): Thread(){}
	~TestThread()
	{
		waitToComplete();
	}
protected:

	void run();

};

void TestThread::run()
{
	for(int i=0;i<32000;i++)
	{
		for(int j=0;j<16;j++){
		dispatch();
		syncPrintf("-----      ");
		}
	}
}


int userMain(int argc, char** argv)
{
	timerInic();
	for(int m=0; m<30000; m++)
		for(int j=0; j<30000; j++);
	syncPrintf("Test starts.\n");
	TestThread t[n];
	int i;
	for(i=0;i<n;i++)
	{
		t[i].start();
		printf("Nit startovna\n");
		asm cli;
	}
	for(i=0;i<n;i++)
	{
		t[i].waitToComplete();
		printf("Poziv waitToComplete()");
		asm cli;
	}
	syncPrintf("Test ends.\n");
	//while(1) {};
	timerRestore();
	return 0;
}
*/
// ---------------------------------------------------
/*
class TestThread : public Thread
{
private:
	TestThread *t;

public:

	TestThread(TestThread *thread): Thread(), t(thread){}
	~TestThread()
	{
		waitToComplete();
	}
protected:

	void run();

};

void TestThread::run()
{
	t->waitToComplete();
	printf("----waitToComplete()----\n");
	asm cli;
}


int userMain(int argc, char** argv)
{
	timerInic();
	syncPrintf("Test starts.\n");
	for(int m = 0; m<30000; m++)
		for(int n = 0; n<30000; n++);
	TestThread *t1,*t2;
	t1 = new TestThread(t2);
	t2 = new TestThread(t1);
	printf("--Niti kreirane--\n");
	asm cli;
	t1->start();
	t2->start();
	printf("---Niti zavrsile posao---");
	asm cli;
	delete t1;
	delete t2;
	syncPrintf("Test ends.\n");
	//while(1){}
	timerRestore();
	return 0;
}


int main() {
	return userMain(0, 0);
}
*/

/*

const int n = 10;
int count = 100;
Semaphore mutex(1);

int mutex_glb = 1;

void mutex_glb_wait(){
 sloop:asm{
	mov ax, 0
	xchg ax, mutex_glb
}
 if(_AX ==0){
	dispatch();
	asm jmp sloop;
 }
}


#define intLock mutex_glb_wait();
#define intUnlock mutex_glb = 1;


class BoundedBuffer {
public:

	BoundedBuffer (unsigned size);
	virtual ~BoundedBuffer ();
	int append (char);
	char take ();
	int  fullCount(){return itemAvailable.val();};    // potrebno consumeru

private:
	unsigned Size;
	Semaphore mutexa, mutext;
	Semaphore spaceAvailable, itemAvailable;
	char* buffer;
	int head, tail;

};

BoundedBuffer::BoundedBuffer (unsigned size) : Size(size),
	mutexa(1), mutext(1), spaceAvailable(size), itemAvailable(0),
	head(0), tail(0) {
		buffer = new char[size];
		if (!buffer) exit(1);
	}

BoundedBuffer::~BoundedBuffer(){
	intLock
	delete [] buffer;
	intUnlock
}

int BoundedBuffer::append (char d) {
	spaceAvailable.wait(0);
	mutexa.wait(0);
		buffer[tail] = d;
		tail = (tail+1)%Size;
	mutexa.signal(0);
	itemAvailable.signal(0);
	return 0;
}

char BoundedBuffer::take () {
	itemAvailable.wait(0);
	mutext.wait(0);
		char d = buffer[head];
		head = (head+1)%Size;
	mutext.signal(0);
	spaceAvailable.signal(0);
	return d;
}

BoundedBuffer buffer(n/2);

class Producer: public Thread
{
public:
	Producer(): Thread() {};
	~Producer()
	{
		waitToComplete();
	}

protected:
	void run()
	{
		char c;
		while(count>0)
		{
			c = 65+(rand()%25);
			buffer.append(c);
			syncPrintf("%d. Producer %d puts '%c'\n",count,Thread::getRunningId(),c);
			//printf(" mutex.wait() ----> %d \n", mutex.val( ));
			mutex.wait(0);
			//printf(" mutex.wait() ----> %d \n", mutex.val( ));
			//asm cli
			count--;
			mutex.signal(0);

		//	for(int i = 0; i<3000; i++)
		//			for(int j=0; j<3000; j++);
			//printf(" mutex.signal() ----> %d\n", mutex.val());
			//asm cli
			//exit(1);
		}
	}
};

class Consumer: public Thread
{
public:
	Consumer(): Thread() {};
	~Consumer()
	{
		waitToComplete();
	}

protected:
	void run()
	{
		char c;
		while(count>0)
		{
			c = buffer.take();
			syncPrintf("%d. Consumer %d gets '%c'\n",count,Thread::getRunningId(),c);
			mutex.wait(0);
			//printf(" mutex.wait() ----> %d \n", mutex.val( ));
			count--;
			mutex.signal(0);

		//	for(int i = 0; i<3000; i++)
			//					for(int j=0; j<3000; j++);
			//printf(" mutex.signal() ----> %d \n", mutex.val( ));
			//exit(1);
		}
	}
};

void tick(){}

int userMain(int argc, char** argv)
{
	//timerInic();
	syncPrintf("Test starts.\n");
	//PCB::idle->start();
	//for(int i = 0; i<10000; i++)
		//for(int j=0; j<10000; j++);
	Producer p;
	Consumer c;
	p.start();
	c.start();
	while(1) {};
	syncPrintf("Test ends.\n");
	//timerRestore();

	return 0;
}

*/

/*
const int n = 5;
int count = 10;

Semaphore s(2);

class TestThread : public Thread
{
public:

	TestThread(): Thread(){}
	~TestThread()
	{
		waitToComplete();
	}
protected:

	void run();

};

void TestThread::run()
{
	s.wait(0);
	printf("-- %d --\n", s.val());
	cout<<"Thread "<<getID()<<" in critical section."<<endl;
	for(unsigned int i=0;i<30000;i++)
		for(unsigned int j=0;j<30000;j++);
	s.signal(0);
	printf("--- %d ---\n", s.val());
	//asm cli;
}

//void tick(){}

int userMain(int argc, char** argv)
{
	timerInic();
	syncPrintf("Test starts.\n");
	TestThread t[n];
	int i;
	for(i=0;i<n;i++)
	{
		t[i].start();
	}
	for(i=0;i<n;i++)
	{
		t[i].waitToComplete();
	}
	syncPrintf("Test ends.\n");
	while(1) {};
	timerRestore();
	return 0;
}
*/
// ====================== test 9 ============================================

/*
const int n = 1;
int t=-1;

Semaphore s(0);

class TestThread : public Thread
{
public:

	TestThread(): Thread(){}
	~TestThread()
	{
		waitToComplete();
	}
protected:

	void run();

};

void TestThread::run()
{
	syncPrintf("Thread waits for 10 units of time...\n");
	t=0;
	s.wait(10);
	//cout << "-----------" << endl;
	syncPrintf("Thread finished.\n");
	//s.~Semaphore();
	s.signal(0);
	//delete s;
}

void tick()
{

	t++;
	if(t)
		syncPrintf("%d\n",t);
}

int userMain(int argc, char** argv)
{
	cout << "Test started!" << endl;
	timerInic();
	syncPrintf("Test starts.\n");
	PCB::idle->start();
	TestThread t[n];
	int i;
	for(i=0;i<n;i++)
	{
		t[i].start();
	}
	for(i=0;i<n;i++)
	{
		t[i].waitToComplete();
	}
	//PCB::idle->start();
	syncPrintf("Test ends.\n");
	while(1) {};
	timerRestore();
	return 0;
}

*/
//================== test 10 ==============================================
/*

int t=100;

Semaphore s(0);

class TestThread : public Thread
{
private:
	Time waitTime;

public:

	TestThread(Time WT): Thread(), waitTime(WT){
	//	cout << "!!!!!!!!!!! NIT KREIRANA !!!!!!!!!!" << endl;
	}
	~TestThread()
	{
		waitToComplete();
	}
protected:

	void run();

};

void TestThread::run()
{

	syncPrintf("Thread %d waits for %d units of time.\n",getID(),waitTime);
	int r = s.wait(waitTime);
	//s.signal(0);
	syncPrintf("Thread %d finished: r = %d\n", getID(),r);
}

void tick()
{
	//t++;
//	if(t)
	//	syncPrintf("%d\n",t);
}

int userMain(int argc, char** argv)
{
//	timerInic();
	syncPrintf("Test starts.\n");
	TestThread t1(150),t2(100),t3(300);
	t1.start();
	t2.start();
	t3.start();
//	PCB::idle->start();
	//cout << "==== Ulazi u wait ===" << endl;
	s.wait(5);
	//cout << "==== Odblokira se ===" << endl;
	s.signal(0);
	//cout << "==== Odblokira se ===" << endl;
	s.wait(0);
	s.signal(0);
	syncPrintf("Test ends.\n");
	while(1) {};
//	timerRestore();
	return 0;
}
*/


/*
// ===================== test 11 =======================

void tick()
{

//	t++;
//	if(t)
//		syncPrintf("%d\n",t);

}


#include <iostream.h>

Semaphore* mutex = 0;

class Znak : public Thread
{
public:
	Znak(char znak, int n) : Thread(), znak(znak), n(n) {}
	virtual ~Znak() { waitToComplete(); }

	void run()
	{
		for (long i = 0; i < 100000; i++)
		{

			if (mutex->wait(n)) {
				cout << znak;
				mutex->signal(0);
			}

			//if(i/4563 == 0)
			//	dispatch();

		}

		if (mutex->wait(n)) {
			cout << endl << znak << " finished" << endl;
			mutex->signal(0);
		}
	}

private:
	char znak;
	int n;

};


int userMain(int argc, char* argv[]) {
	mutex = new Semaphore(1);

	Znak* a = new Znak('a', 10);
	Znak* b = new Znak('b', 15);
	Znak* c = new Znak('c', 20);

	a->start();
	b->start();
	c->start();

	mutex->signal(0);
	a->waitToComplete();
	b->waitToComplete();
	c->waitToComplete();

	delete a;
	delete b;
	delete c;

	if (mutex->wait(1)) {
		cout << endl << "userMain finished" << endl;
		mutex->signal(0);
	}

	delete mutex;



	return 0;
}
*/

// ================= test12 =============================
/*
int t=-1;

const int n=50;

Semaphore s(1);

class TestThread : public Thread
{
private:
	Time waitTime;

public:

	TestThread(Time WT): Thread(), waitTime(WT){}
	~TestThread()
	{
		waitToComplete();
	}
protected:

	void run();

};

void TestThread::run()
{
	for(int i=0; i<10000; i++)
		for(int j=0; j<10000; j++);
	syncPrintf("Thread %d waits for %d units of time.\n",getID(),waitTime);
	int r = s.wait(waitTime);
	if(getID()%2) {
	//	printf("======== SIGNALIZIRA ===========\n");
		//asm cli;
		//syncPrintf("======== SIGNALIZIRA ===========\n");
		s.signal(0);
		syncPrintf("======== SIGNALIZIRA ===========\n");
		//printf("======== SIGNALIZIRA ===========\n");
		//asm cli
	}
	syncPrintf("Thread %d finished: r = %d\n", getID(),r);
}

void tick()
{
	//t++;
	//if(t)
	//	syncPrintf("%d\n",t);
}

int userMain(int argc, char** argv)
{

	syncPrintf("Test starts.\n");
	TestThread* t[n];
	int i;
	for(i=0;i<n;i++)
	{
		t[i] = new TestThread(5*(i+1));
		t[i]->start();
	}

	s.signal(0);
	for(i=0;i<n;i++)
	{
		t[i]->waitToComplete();
	}
	delete t;
	//for(int m = 0; m < 15000; m++)
	//	for(int k=0; k< 15000; k++);
	s.signal(0);

	syncPrintf("Test ends.\n");
//	while(1) {};

	return 0;
}

*/


//==================== test 13 ==================
/*
PREPAREENTRY(9,0);

Semaphore* mutex = 0;
Semaphore* sleepSem = 0;

void tick() {}


class Znak : public Thread
{
public:
	Znak(char znak, int n) : Thread(), znak(znak), n(n) {}
	virtual ~Znak() { waitToComplete(); }

	void run()
	{
		// for (long i = 0; i < 100000; i++)
		for (int i = 0; i < n; i++)
		{
			if (mutex->wait(1)) {
				cout << znak;
				mutex->signal();
			}

			// for (int j = 0; j < 10000; j++)
				// for (int k = 0; k < 10000; k++);
			Time sleepTime = 2 + rand() % 8;
			sleepSem->wait(sleepTime);

			// dispatch();
		}

		if (mutex->wait(1)) {
			cout << endl << znak << " finished" << endl;
			mutex->signal();
		}
	}

private:
	char znak;
	int n;

};


class Key : public Thread {
public:
	Key(int n) : Thread(), n(n) {}
	virtual ~Key() { waitToComplete(); }

	void run() {
		Event e(9);

		for (int i = 0; i < n; i++) {
			if (mutex->wait(1)) {
				cout << endl << "key waiting " << (i + 1) << endl;
				mutex->signal();
			}

			e.wait();

			if (mutex->wait(1)) {
				cout << endl << "key continue " << (i + 1) << endl;
				mutex->signal();
			}

			sleepSem->wait(1);
		}

		if (mutex->wait(1)) {
			cout << endl << "key finished" << endl;
			mutex->signal();
		}
	}

private:
	int n;

};


int userMain(int argc, char* argv[]) {
	mutex = new Semaphore(1);
	sleepSem = new Semaphore(0);

	Znak* a = new Znak('a', 10);
	Znak* b = new Znak('b', 15);
	Znak* c = new Znak('c', 20);
	Key* k = new Key(150);

	a->start();
	b->start();
	c->start();
	k->start();

	delete a;
	delete b;
	delete c;
	delete k;

	if (mutex->wait(1)) {
		cout << endl << "userMain finished-> test completed! " << endl;
		mutex->signal();
	}

	delete sleepSem;
	delete mutex;

	return 0;
}
*/


// ============================= test 14 ==========================
/*
unsigned t=18;
unsigned seconds = 5;

void secondPast()
{
	if(seconds)
		syncPrintf("%d\n",seconds);
	seconds--;
}

void tick()
{
	t--;
	if(t==0){
		t = 18;
		secondPast();
	}
}



int userMain(int argc, char** argv)
{
	syncPrintf("Starting test\n");
	while(seconds+1);
	syncPrintf("Test ends\n");
	return 0;
}


*/


// ================= test 15 =======================
/*
const int n = 4;

void tick(){}

class TestThread : public Thread
{
public:

	TestThread(): Thread(32768,2) {};
	~TestThread()
	{
		waitToComplete();
	}
protected:

	void run();

};

void TestThread::run()
{

	int buffer=2;

	for(int i=0;i<32000;i++)
	{
		buffer = 4096/2048;
		for (int j = 0; j < 1024; j++)
		{
			buffer = buffer*2;
			if(buffer%2)
				buffer = 2;
		}
	}

}


int userMain(int argc, char** argv)
{
	syncPrintf("Test starts: %d threads.\n",n);
	int i;
	TestThread threads[n];
	for(i=0;i<n;i++)
	{
		threads[i].start();
	}
	for(i=0;i<n;i++)
	{
		threads[i].waitToComplete();
		syncPrintf("%d. Done!\n",Thread::getThreadById(i+10)->getID());
	}
	syncPrintf("Test ends.\n");
	return 0;
}

*/
/*
int main() {
	timerInic();
	PCB::idle->start();
	userMain(0,0);
	timerRestore();
	return 0;

}
*/


#endif /* OSPROJ_MAIN_H_ */


