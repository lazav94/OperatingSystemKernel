/*
 * semaphore.h
 *
 *  Created on: 09.06.2015.
 *      Author: Avax
 */

#ifndef SEMAPHOR_H_
#define SEMAPHOR_H_

class KernelSem;

class Semaphore {
public:
	Semaphore(int init=1);
	virtual ~Semaphore();

	virtual void wait();
	virtual void signal();

	int val() const;
private:
	KernelSem* myImpl;
};

#endif /* SEMAPHOR_H_ */
