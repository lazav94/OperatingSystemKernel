/*
 * kernelse.cpp
 *
 *  Created on: Jul 1, 2015
 *      Author: Lazar
 */

#include "kernelse.h"


KernelSe::KernelSe(Semaphore* newSemaphor,int inita) {
	value = inita;
	locke(1)
		blocked = new Queue();
	unlocke(1)

	newSemaphor->myImpl = Kernel::objects->addSemaphor(this);
}

KernelSe::~KernelSe() {
	while(value<0)
		signal(); //SIGNA ALL: Before destructor delete  all  blocked threads on this Semaphore
	delete blocked;
}

void KernelSe::wait(){
	locke(1)

		if(Kernel::running == NULL){
			printf("ERROR: Running thread is NULL. Location KernelSe::wait()\n");
			exit(1);
		}

		if(--value < 0) {
			blocked->INSERT(Kernel::running);
			Kernel::running->pcbState = PCB::BLOCKED;
			unlocke(1)
			dispatch();
		}
		else { unlocke(1)  }
}

void KernelSe::signal(){
	locke(1)

		if(++value <= 0) {
			PCB *freeNow = blocked->DELETE();//DELETE can't  return a NULL pointer , because exit in DELETE!!!
			if(freeNow == NULL) { printf("ERROR: Something is wrong freeNow is equal NULL, error location: KernelSe::signal!\n"); exit(1); }
			freeNow->pcbState = PCB::READY;
			Scheduler::put(freeNow);
		}

	unlocke(1)
}

int KernelSe::Value()const { return value; }
