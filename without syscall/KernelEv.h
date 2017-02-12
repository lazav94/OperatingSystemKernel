/*
 * KernelEv.h
 *
 *  Created on: 09.06.2015.
 *      Author: Avax
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_
#include "semaphor.h"

class PCB;

class KernelEv {
public:
	KernelEv(unsigned entry);
	void signal();
	void wait();
	virtual ~KernelEv();
private:
	unsigned entry;
	Semaphore bin;
	PCB* myPCB;
};

#endif /* KERNELEV_H_ */
