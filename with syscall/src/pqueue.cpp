/*
 * pqueue.cpp
 *
 *  Created on: Jul 1, 2015
 *      Author: Lazar
 */

#include "pqueue.h"
#include "kernel.h"

int           PQueue::lenght = 0;
PQueue::Elem* PQueue::first  = NULL;

//Svaki sledeci element reda sadrzi razliku vremena od predhodnika


void PQueue::INSERT(PCB *pcb, Time timeForSleep){
	locke(1)
		if(pcb != NULL && timeForSleep > 0){
			pcb->pcbState = PCB::BLOCKED;
			Elem *newForSleep = new Elem(pcb, timeForSleep), *curr = first, *prev = NULL;

			while(curr != NULL){
				if(curr->sleepingTime < newForSleep->sleepingTime){
					prev = curr;
					newForSleep->sleepingTime -= curr->sleepingTime;
					curr = curr->next;
				}
				else break;
			}

			if(prev == NULL)
				first = newForSleep;
			else
				prev->next = newForSleep;

			newForSleep->next=curr;

			if(curr)
				curr->sleepingTime-=newForSleep->sleepingTime;

			lenght++;
		}
		else{
			printf("ERROR: PCB is NULL or timeForSleep is 0. Location:PQueue::INSERT\n");
		}
	unlocke(1)
}

void PQueue::DELETE(){
	locke(1)

	if(first == NULL) {   // || lenght==0
		printf("ERROR: Can't delete element from empty PQueue.Location:PQueue::DELETE()\n");  //maybe iddle->run?
		unlocke(1)
		return;
	}
	while(first!=NULL && first->sleepingTime == 0){
			Elem *curr=first;
			curr->pcb->pcbState = PCB::READY;
			Scheduler::put(curr->pcb);
			first=first->next;
			lenght--;
			delete curr;

	}
	unlocke(1)

}

int PQueue::lenghtPQ() { return lenght; }

void PQueue::decrementTime(){
	locke(1)
		if(first != NULL)
			first->sleepingTime--;
	unlocke(1)
}

void PQueue::incrementTime(){
	locke(1)
		if(first != NULL)
			first->sleepingTime++;
	unlocke(1)
}
/*----------------------Explicit wake up----------------------*/
void PQueue::resetTime(){
	locke(1)
			if(first != NULL)
			first->sleepingTime=0;
	unlocke(1)
}
/*-------Sleep more (all sleeping thread) for snoozeTime -----*/ /*Delay wake up!!!*/
void PQueue::snooze(Time snoozeTime){
	locke(1)
			if(first != NULL)
				first->sleepingTime+=snoozeTime;
	unlocke(1)
}

void PQueue::printPQ(){
	Elem *curr;
	while(curr != NULL){
		printf("ID PCB of PQueue %d\n",curr->pcb->myThread->getPCB());
		curr = curr->next;
	}
}
