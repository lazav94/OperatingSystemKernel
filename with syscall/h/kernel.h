/*
a * kernel.h
 *
 *  Created on: Jul 1, 2015
 *      Author: Lazar
 */

#ifndef KERNEL_H_
#define KERNEL_H_

#include "thread.h"
#include "pcb.h"
#include "lock.h"
#include "idleThrd.h"
#include "syscall.h"
#include "SCHEDULE.H"
#include <STDLIB.H>
#include <STDIO.H>
#include <DOS.H>

void rest();
void init();

class Thread;
class idleThread;
class PCB;
class PQueue;
class IVTEntry;
class sysObject;



class Kernel {
private:
	friend class Thread;
	friend class PCB;
	friend class KernelSe;
	friend class KernelEv;
	friend class idleThread;
	friend class IVTEntry;
	friend void dispatch();

public:
	static void startKernel();
	static void stopKernel();

	static PCB*        idlePCB; //Kernel::objects->getObject(idleThread->myPCB);
	static PCB*        running; //Pointer of current(running) thread
	static sysObject*  objects; //Class with map of all syscall objects
};

#endif /* KERNEL_H_ */
