/*
 * semaphor.h
 *
 *  Created on: Jul 1, 2015
 *      Author: Lazar
 */

#ifndef SEMAPHOR_H_
#define SEMAPHOR_H_

#include "pcb.h"
#include "kernel.h"
#include "kernelse.h"
#include "thread.h"
#include "syscall.h"
#include <STDIO.H>

class KernelSe;

class Semaphore {
public:
	Semaphore(int init=1);
	virtual ~Semaphore();

	virtual void wait();
	virtual void signal();

	int val() const;

private:
	friend class KernelSe; //Add friend class
	ID myImpl;
};

#endif /* SEMAPHOR_H_ */
