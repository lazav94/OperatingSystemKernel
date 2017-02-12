/*
 * KernelSem.cpp
 *
 *  Created on: 09.06.2015.
 *      Author: Avax
 */
#include "lock.h"
#include "STDLIB.H"
#include "PCB.h"
#include "queue.h"
#include "SCHEDULE.H"
#include "thread.h"
#include "KSem.h"
extern volatile unsigned short SchedulerEmpty;
KernelSem::KernelSem(int val) {
	this->val=val;
}

KernelSem::~KernelSem() {
	while(val<0)
		signal();
}

void KernelSem::signal(){
	lock
		if(val++<0){
			PCB* tmp=blocked.get();
			if(tmp==0) exit(1);
			tmp->state=PCB::READY;
			SchedulerEmpty=0;
			Scheduler::put(tmp);
		}
	unlock
}


void KernelSem::wait(){
	lock
	if(--val<0){
		blocked.put(PCB::running);
		PCB::running->state=PCB::BLOCKED;
		unlock
		dispatch();
	}
	else unlock

}

int KernelSem::value()const{
	return val;
}
