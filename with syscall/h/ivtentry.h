/*
 * ivtentry.h
 *
 *  Created on: Jul 1, 2015
 *      Author: Lazar
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

#include "event.h"
#include "lock.h"
#include <DOS.H>
#include <STDLIB.H>

//MAKRO
#define PREPAREENTRY(numIVT,oldINT)\
    void interrupt InteruptFunction##numIVT(...){\
            IVTEntry::interruptTable[##numIVT]->signalIVT();\
            if (oldINT) IVTEntry::interruptTable[##numIVT]->oldRoute();}\
    IVTEntry ivtNumber##numIVT(##numIVT,InteruptFunction##numIVT);


typedef unsigned char IVTNo;
typedef void interrupt (*route)(...); // ROUTE == ROUTINE

class Event;
class KernelEv;

class IVTEntry {
private:
	IVTNo ivtNumber;
	Event* event;
public:
	friend class Kernel;

	IVTEntry (IVTNo ivtNo, route interruptRoute);
	IVTEntry (IVTNo ivtNo, route interruptRoute , Event * newEvent);
	~IVTEntry();

	Event* getEvent();
	void   setEvent(Event *newEvent);

	void signalIVT();

	route oldRoute;
	route newRoute;

	static IVTEntry *interruptTable[256];

	static IVTEntry* Instance			    (IVTNo ivtNo);
	static route 	 getRouteFromIVTNo      (IVTNo ivtNo);
	static void  	 setVectorForIVTNoRoute (IVTNo ivtNo, route newRoute);

};

#endif /* IVTENTRY_H_ */
