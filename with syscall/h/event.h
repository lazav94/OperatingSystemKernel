/*
 * event.h
 *
 *  Created on: Jul 1, 2015
 *      Author: Lazar
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "lock.h"
#include "kernel.h"
#include "kernelev.h"
#include "ivtentry.h"
#include <DOS.H>


typedef unsigned char IVTNo;

class KernelEv;

class Event {
public:
	Event (IVTNo ivtNo);
	~Event ();
	void wait();

protected:
	friend class KernelEv;
	friend class IVTEntry; 	//add friend class

	void signal(); // can call KernelEv

private:
	ID myEvent;
};



#endif /* EVENT_H_ */
