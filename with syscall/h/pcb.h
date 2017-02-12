/*
 * pcb.h
 *
 *  Created on: Jul 1, 2015
 *      Author: Lazar
 */

#ifndef PCB_H_
#define PCB_H_

#include "syscall.h"
#include "lock.h"
#include "kernel.h"
#include "queue.h"
#include "pqueue.h"
#include "SCHEDULE.H"
#include <DOS.H>
#include <STDLIB.H>
#include <STDIO.H>

typedef unsigned long StackSize;
typedef unsigned int Time;
typedef int ID;

class Thread;
class Queue;
class PQueue;
class Semaphore;
struct function_Arguments;


class PCB {
public:
	enum STATE {NEW, READY, RUNNING, BLOCKED, FINISED};
	STATE pcbState;

	Thread *myThread;

	volatile unsigned int ss;
	volatile unsigned int sp;

	unsigned int *myStack;
	StackSize stackSize;

	Time timeSlice;

	Queue *blocked;
	static  PQueue *sleepingQueue;

	PCB(Time t, StackSize s, Thread *tr);
	~PCB();

	friend void interrupt timer();

	void createStack();
	void createSystemStack(function_Arguments *f);

	/* dodatne fje !*/
	void unblockAll();
	void unblockOne();

	/*Thread function one on one with thread*/
	void waitToComplete();
	static void sleep(Time tts, PCB *pcbSleep);
	void turnOffThread();

protected:
	friend class Thread;
	friend class IdleThread;
};

#endif /* PCB_H_ */
