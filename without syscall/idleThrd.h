/*
 * idleThread.h
 *
 *  Created on: 09.06.2015.
 *      Author: Avax
 */

#ifndef IDLETHRH_
#define IDLETHRH_
#include "thread.h"
class idleThread: public Thread {
public:
	virtual void run();
	idleThread();
};

#endif /* IDLETHRH_ */
