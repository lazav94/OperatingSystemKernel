/*
 * queue.cpp
 *
 *  Created on: 09.06.2015.
 *      Author: Avax
 */

#include "queue.h"
#include "PCB.h"
#include "lock.h"
queue::queue() : head(0), tail(0) {
}

PCB* queue::get(){
	lock
	if(head==0)
		return 0;
	Elem* old=head;
	if(head==tail)
		tail=0;
	head=head->next;
	PCB* ret=old->pcb;
	unlock
	return ret;
}

void queue::put(PCB* p){
	lock
	Elem* toInsert=new Elem(p);
	if(head==0)
		head=toInsert;
	else
		tail->next=toInsert;
	tail=toInsert;
	unlock
}

