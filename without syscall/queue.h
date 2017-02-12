/*
 * queue.h
 *
 *  Created on: 09.06.2015.
 *      Author: Avax
 */

#ifndef QUEUE_H_
#define QUEUE_H_
class PCB;

class queue {
public:

	struct Elem{
		Elem* next;
		PCB* pcb;
		Elem(PCB* pcb){
			this->pcb=pcb;
			next=0;
		}
	};


	queue();
	void put(PCB* p);
	PCB* get();


private:
	Elem* head, *tail;
};

#endif /* QUEUE_H_ */
