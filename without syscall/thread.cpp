/*
 * thread.cpp
 *
 *  Created on: 08.06.2015.
 *      Author: Avax
 */

#include "thread.h"
#include "PCB.h"
#include "lock.h"
void interrupt timer();
Thread::Thread(StackSize stackSize, Time timeSlice) {
	lock
		myPCB=new PCB(stackSize, timeSlice, this);
	unlock
	// TODO Auto-generated constructor stub

}

Thread::~Thread() {
	waitToComplete();
	lock
	delete myPCB;
	unlock
}

void Thread::waitToComplete(){
	myPCB->waitToComplete();
}
void Thread::start(){
	myPCB->create();
}

void Thread::sleep(Time timeToSleep){
	PCB::sleep(PCB::running, timeToSleep);
}

void dispatch(){
	demanded_takeover=1;
	timer();
}
