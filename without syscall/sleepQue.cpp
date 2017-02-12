/*
 * sleepQue.cpp
 *
 *  Created on: 09.06.2015.
 *      Author: Avax
 */

#include "sleepQue.h"
#include "lock.h"
#include "SCHEDULE.H"
sleepQue::Elem* sleepQue::head=0;

extern volatile unsigned short SchedulerEmpty;

void sleepQue::put(PCB* p, Time t){
	lock
	p->state=PCB::BLOCKED;
	Elem* toInsert=new Elem(p, t);
	Elem* cur=head;
	Elem* last=0;
	while(cur!=0){
		if(cur->timeToSleep>toInsert->timeToSleep)
			break;
		last=cur;
		toInsert->timeToSleep-=cur->timeToSleep;
		cur=cur->next;
	}
	if(last==0)
		head=toInsert;
	else
		last->next=toInsert;
	toInsert->next=cur;
	if(cur)
		cur->timeToSleep-=toInsert->timeToSleep;
	unlock
}

void sleepQue::remove(){
	lock
	while(head!=0){
		if(head->timeToSleep==0){
			Elem* toRemove=head;
			toRemove->pcb->state=PCB::READY;
			SchedulerEmpty=0;
			Scheduler::put(toRemove->pcb);
			head=head->next;
			delete toRemove;
		}
		else break;
	}
	unlock
}
void sleepQue::tick(){
	lock
	if(head)
		head->timeToSleep--;
	unlock
}

