/*
 * Idle.cpp
 *
 *  Created on: Aug 1, 2020
 *      Author: OS1
 */

#include "Idle.h"
#include <iostream.h>

Idle::Idle() : Thread(defaultStackSize, 1) {}	// parametri konstruktora po uslovu zadatka

//Idle::~Idle() {}

PCB* Idle::getPCB() {
	return myPCB;
}


void Idle::run() {
//	int i = 0;
	while(/*i<100000*/ 1) {
		//cout << "===  zaludna nit radi ===" << endl;
		//i++;
	}		// "zaludna" nit
}

