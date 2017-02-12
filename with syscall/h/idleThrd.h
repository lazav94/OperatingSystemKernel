/*
 * idleThread.h
 *
 *  Created on: 09.06.2015.
 *      Author: Avax
 */

#ifndef IDLETHRH_
#define IDLETHRH_
#include "thread.h"
#include "pcb.h"
#include "user.h"
#include "kernel.h"

class Thread;
// Idle Thread contains one or more kernel threads which run when no other runnable thread can be scheduled on a CPU
class idleThread : public Thread {
public:

	friend class Kernel;
	friend class PCB;

	idleThread();
	virtual void run();

};

#endif /* IDLETHRH_ */
