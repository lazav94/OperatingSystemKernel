/*
 * ivtentry.cpp
 *
 *  Created on: Jul 1, 2015
 *      Author: Lazar
 */

#include "ivtentry.h"

IVTEntry* IVTEntry::interruptTable[256]={NULL};

IVTEntry::IVTEntry(IVTNo ivtNo, route interruptRoute){
	if(ivtNo < 0 || ivtNo >= 256) { printf("ERROR: IVT ENTRY NUMBER OUT OF BOUNDS!\n"); return; }
	oldRoute  = NULL;
	newRoute  = interruptRoute;
	ivtNumber = ivtNo;
	interruptTable[ivtNumber] = this;
	event 	  = NULL;
}

IVTEntry::IVTEntry(IVTNo ivtNo, route interruptRoute , Event *newEvent){
	if(ivtNo < 0 || ivtNo >= 256) { printf("ERROR: IVT ENTRY NUMBER OUT OF BOUNDS!\n"); return; }
	oldRoute  = 0;
	newRoute  = interruptRoute;
	ivtNumber = ivtNo;
	interruptTable[ivtNumber] = this;
	event 	  = newEvent;
}

void   IVTEntry::signalIVT()               { event->signal();  }
void   IVTEntry::setEvent(Event *newEvent) { event = newEvent; }
Event* IVTEntry::getEvent() 			   { return event;     }

IVTEntry::~IVTEntry() { /* oldRoute(); */}

IVTEntry* IVTEntry::Instance(IVTNo ivtNo){
	if(ivtNo < 0 || ivtNo >= 256) { printf("ERROR: IVT ENTRY NUMBER OUT OF BOUNDS!\n"); return NULL; }
	return interruptTable[ivtNo];
}
/*--------Method for seting Interapt Route in ivtTable------------*/
void IVTEntry::setVectorForIVTNoRoute(IVTNo ivtNo,route newRoute){
	if(ivtNo < 0 || ivtNo >= 256) { printf("ERROR: IVT ENTRY NUMBER OUT OF BOUNDS!\n"); return; }
	locke(1)
		route *temp = (route *)(4*ivtNo); //UNSIGNED = 4 * CHAR
		*temp = newRoute;
	unlocke(1)

}

route IVTEntry::getRouteFromIVTNo(IVTNo ivtNo){
	if(ivtNo < 0 || ivtNo >= 256) { printf("ERROR: IVT ENTRY NUMBER OUT OF BOUNDS!\n"); return NULL; }
	locke(1)
		route *returnRoute = (route *)(4*ivtNo);
	unlocke(1)
		return *returnRoute;
}


