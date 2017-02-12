/*
 * pqueue.h
 *
 *  Created on: Jul 1, 2015
 *      Author: Lazar
 */

#ifndef PQUEUE_H_
#define PQUEUE_H_

#include "pcb.h"
#include "kernel.h"
#include "lock.h"
#include "thread.h"
#include <STDLIB.H>
#include <STDIO.H>

typedef unsigned int Time;


class PQueue {
public:
	struct Elem{
			PCB *pcb;
			Elem *next;
			Time sleepingTime;

			Elem(PCB *pcbb, Time sleepTime, Elem *nexxt = NULL):pcb(pcbb),sleepingTime(sleepTime),next(nexxt){}
			~Elem(){ pcb=NULL; next=NULL; }
		};

		static void INSERT(PCB *pcb, Time timeForSleep);
		static void DELETE();
		static int lenghtPQ();

		static void decrementTime();
		static void incrementTime();
		static void resetTime();
		static void snooze(Time snoozeTime);
		static void printPQ();
private:
		friend class Kernel;
		static Elem *first; //*last is useless!!!
		static int lenght;
		PQueue(){}
};

#endif /* PQUEUE_H_ */
