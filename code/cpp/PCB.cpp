/*
 * PCB.cpp
 *
 *  Created on: Jul 29, 2020
 *      Author: OS1
 */

#include "PCB.h"
#include <iostream.h>

Lista* PCB::PCBlista = new Lista(); // pravimo staticku listu PCB-ova
//Lista* PCB::waitToCompleteList = new Lista();

int PCB::nID = 0;
Idle* PCB::idle = new Idle();	// pcb za "zaludnu nit"

const int PCB::NEW = 0;
const int PCB::READY = 1;
const int PCB::BLOCKED = 2;
const int PCB::TERMINETED = 3;

Thread* PCB::start = new Thread(4096,2); // sada start pokazuje na novo kreiranu nit
PCB* PCB::running = PCB::start->myPCB; // running pokazuje na PCB niti na koju ukazuje start

//PCB* PCB::running = myThread->myPCB; // ne moze zato sto myThread jos uvek ne postoji

PCB::PCB(Thread* t, StackSize _stackSize, Time _timeSlice) {
	lock;
	state = NEW;
	stackSize = _stackSize;
	timeSlice = _timeSlice; // koliko vreme nit treba da se izvrsava
	this->waitToCompleteList = new Lista(); // niti koje ce cekati na zavrsetak ove niti
	blockFlag = 1;
	id = nID++;
	myThread = t;
	stack = 0;
	PCBelem* element = new PCBelem(this, id); // pravimo objekat klase PCBelem, koji se sastoji iz niti i njenog ID-ja
	PCB::PCBlista->dodajNaPocetak((void*) element);
	unlock;
}

PCB::~PCB() {
	lock;
//	if(stack!= 0) delete stack;
//	this->waitToCompleteList->isprazniListu();
//	this->waitToCompleteList = 0;
//	waitToComplete();
	for(PCB::PCBlista->tekuciNaPocetaK(); PCB::PCBlista->postojiTekuci(); ) {
		PCBelem* pom = (PCBelem*) PCB::PCBlista->dohvTekuci();
		if((PCB*)pom->t == (PCB*)this) {
			PCB::PCBlista->obrisiTekuci();
			break;
		} else {
			PCB::PCBlista->sledeci();
		}
//		delete pom->t;
//		delete pom->id;
		delete pom;
	}
//	cout<< "========= PCB destruktor =======" << endl;
//	asm cli;
/*	if(stack!= 0) {
		delete stack;
	}*/
	unlock;
}

void PCB::stackCreate() {
	lock;
	stack = new unsigned int [stackSize / sizeof(unsigned)];	// stack je pokazivac na pocetak niza
	// npr stack ima 1024 mesta, pa je vrh steka na poziciji stack[1023]
	stack[stackSize-1] = 0x200; // PSW sa setovanim I bitom
#ifndef BCC_BLOCK_IGNORE
	stack[stackSize-2] = FP_SEG(PCB::wrapper); // segmentni deo adrese f-je koju izvrsava nit, tj. segment PC-a
	stack[stackSize-3] = FP_OFF(PCB::wrapper); // offsetni deo adrese f-je, tj. offset PC

	// odvojen deo steka za registe ax,bx,cx,dx,es,ds,si,di

	ss = FP_SEG(stack+stackSize - 12);	// segmentni deo stack pointer-a
	sp = FP_OFF(stack+stackSize - 12);
	bp = FP_OFF(stack+stackSize - 12);
#endif
	unlock;
}

void PCB::wrapper() {
	//lock
	PCB::running->myThread->run();
	lock
	PCB::running->state = PCB::TERMINETED;

	int n = (int) PCB::running->waitToCompleteList->brojElemenataListe(); // odblokiramo sve niti koje su cekale na zavrsetak running niti

	for(int i=0; i<n; i++) {
		PCB* tmp = (PCB*) PCB::running->waitToCompleteList->uzmiPrvi();
		if(tmp != 0) {
		tmp->state = PCB::READY;
		Scheduler::put((PCB*) tmp);
		} else {
			printf("=== Greska waitToComlete ===\n");
		}
	}

//	PCB::running->state = PCB::TERMINETED;
	unlock
	dispatch();
	//unlock
}

Thread* PCB::getById(ID id_) {	// treba da iz liste svih PCB-ova dohvatimo nit za zadati ID i da je izbacimo iz liste
	lock
	Thread* nit = 0;
	if(PCB::PCBlista !=0 ) {	// provera da li je lista PCB-ova prazna

		for(PCB::PCBlista->tekuciNaPocetaK(); PCB::PCBlista->postojiTekuci(); ) {
				PCBelem* tmp = (PCBelem*) PCB::PCBlista->dohvTekuci();

				if(tmp->id != id_) {
					PCB::PCBlista->sledeci(); // ako ID tekuceg nije trazeni ID, prelazimo na sledeci PCB
				} else {
					nit = (Thread*) tmp->t;
					PCB::PCBlista->obrisiTekuci();
				}
		}
	}
	unlock
	return nit;
}

void PCB::waitToComplete() {
	lock

	PCB::running->state = PCB::BLOCKED;
	this->waitToCompleteList->dodajNaPocetak((void*)PCB::running);
	timerWait();
	//dispatch();

	unlock
}









