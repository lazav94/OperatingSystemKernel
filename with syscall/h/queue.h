/*
 * queue.h
 *
 *  Created on: Jul 1, 2015
 *      Author: Lazar
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "lock.h"
#include "pcb.h"
#include "kernel.h"
#include <STDLIB.H>
#include <STDIO.H>


class PCB;

struct List{
	PCB *pcb;
	List *next;
	List(PCB *p  , List * n = NULL):pcb(p),next(n) { }
	~List(){ pcb = NULL; next = NULL; }
};

class Queue {
private:
	List *first, *last;
	int lenght;

	friend class PCB;
	friend class Kernel;

public:
	Queue();
	~Queue();

	void INSERT(PCB *p);
	PCB *DELETE();

	int Lenght()const;
	void printQueue();

};

#endif /* QUEUE_H_ */
