/*
 * queue.cpp
 *
 *  Created on: Jul 1, 2015
 *      Author: Lazar
 */

#include "queue.h"



Queue::Queue():first(NULL),last(NULL),lenght(0) { }


Queue::~Queue() {
	locke(1)
		List *curr;
		while(first != NULL ){
			curr = first;
			first = first->next;
			delete curr;
			lenght--;
		}
		lenght = 0;
	unlocke(1)
}

void Queue::INSERT(PCB *p){
locke(1)

	if(p == NULL){
		printf("ERROR: Can't insert PCB = NULL in Queue.Location:Queue::INSERT(PCB* p)\n");
		unlocke(1)
		return;
	}

	List *newPCB = new List(p);
	if(first == NULL )
		first =  newPCB;
	else
		last->next = newPCB;
	last = newPCB;
	lenght++;
unlocke(1)
}

PCB* Queue::DELETE(){
locke(1)

	if(first == NULL || lenght == 0) {
		printf("ERROR: Can't delete element from empty Queue.Location:Queue::DELETE()\n");
		unlocke(1)
		return NULL;
	} //Error if return NULL in kernel.cpp signal!!!

	List *deletedList = first;

	if( first == last)
		last = NULL;

	first= first->next;
	deletedList->next = NULL;
	lenght--;

unlocke(1)
	return deletedList->pcb;
}


void Queue::printQueue(){
	locke(1)
		List *curr = first;
		while(curr != NULL ){
			printf("PCB ID in Queue = %d\n ",curr->pcb->myThread->getPCB());
			curr = curr->next;
		}
	unlocke(1)
}
