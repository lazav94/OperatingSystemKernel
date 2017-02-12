/*
 * kernelev.h
 *
 *  Created on: Jul 1, 2015
 *      Author: Lazar
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_

#include "queue.h"
#include "pcb.h"
#include "kernelse.h"
#include "lock.h"
#include "kernel.h"
#include "event.h"
#include "semaphor.h"
#include "ivtentry.h"
#include "thread.h"

typedef unsigned char IVTNo;

class Event;
class Semaphore;
class KernelSe;


class KernelEv {
private:
	IVTNo 		ivtNumber;
	KernelSe*   eventSem;   //Sem!(sysCall!!!) || Queue!
	PCB*        eventPCB;

public:
	KernelEv(IVTNo ivtNo, Event* newEvent);
	~KernelEv();

	void wait();
	void signal();
};

#endif /* KERNELEV_H_ */
