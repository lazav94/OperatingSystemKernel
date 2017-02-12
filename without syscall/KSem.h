/*
 * KernelSem.h
 *
 *  Created on: 09.06.2015.
 *      Author: Avax
 */

#ifndef KSEM_H_
#define KSEM_H_
#include "queue.h"
class KernelSem {
public:
	int value()const;
	KernelSem(int val=1);
	virtual void signal();
	virtual void wait();
	virtual ~KernelSem();
protected:
	int val;
private:
	queue blocked;
};

#endif /* KSEM_H_ */
