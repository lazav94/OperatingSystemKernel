/*
 * kernelse.h
 *
 *  Created on: Jul 1, 2015
 *      Author: Lazar
 */

#ifndef KERNELSE_H_
#define KERNELSE_H_

#include "queue.h"
#include "kernel.h"
#include "pcb.h"
#include "lock.h"
#include "SCHEDULE.H"

class Queue;

class KernelSe {
private:
		int value;
		Queue *blocked;

		friend class Semaphore;
		friend class Thread;

	public:

		KernelSe(Semaphore *newSemaphor, int inita=1);
		~KernelSe();

		void signal();
		void wait();

		int Value()const;
};

#endif /* KERNELSE_H_ */
