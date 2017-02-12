/*
 * PCB.h
 *
 *  Created on: 09.06.2015.
 *      Author: Avax
 */

#ifndef PCB_H_
#define PCB_H_
#include "semaphor.h"
#include "thread.h"
class PCB {
public:
	enum phase {READY, NEW, DONE, RUNNING, BLOCKED, IDLE};
	static PCB* running, *idle, *main;
	void waitToComplete();
	static void sleep(PCB* p, Time timeToSleep);
	void create();
	static void starter();
	PCB(StackSize stackSize= defaultStackSize, Time timeSlice = defaultTimeSlice, Thread* t);
	static void initialize();
	static void restore();
	virtual ~PCB();
	void exitThread();
	unsigned timeSlice;
	unsigned ss, sp, bp;
	phase state;
private:
	Semaphore done;
	unsigned* stack;
	unsigned stackSize;
	Thread* myThread;
	unsigned blockedThread;

};

void init();
void rest();
#endif /* PCB_H_ */
