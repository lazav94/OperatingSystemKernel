/*
 * kernelev.cpp
 *
 *  Created on: Jul 1, 2015
 *      Author: Lazar
 */

#include "kernelev.h"



KernelEv::KernelEv(IVTNo ivtNo, Event* newEvent):ivtNumber(ivtNo),eventPCB(Kernel::running){
locke(1)
	eventSem = new KernelSe(0,NULL); //auxiliary semaphor, not need to add in Kernel::objects
unlocke(1)

//prepare for new route, save old route!
	if(IVTEntry::interruptTable[ivtNumber]->oldRoute == NULL){
		IVTEntry::interruptTable[ivtNumber]->oldRoute = IVTEntry::getRouteFromIVTNo(ivtNumber);
		IVTEntry::setVectorForIVTNoRoute(ivtNumber, IVTEntry::interruptTable[ivtNumber]->newRoute);
	}
	IVTEntry::interruptTable[ivtNo]->setEvent(newEvent);
	newEvent->myEvent = Kernel::objects->addEvent(this);
}

KernelEv::~KernelEv(){
//set old route
	IVTEntry::setVectorForIVTNoRoute(ivtNumber, IVTEntry::interruptTable[ivtNumber]->oldRoute);
	IVTEntry::interruptTable[ivtNumber]->oldRoute = NULL;
	IVTEntry::interruptTable[ivtNumber]->setEvent(NULL);

	//Don't delete eventPCB here -> PQ ERROR
	delete eventSem;

}

/*BINARY SEMAPHORE !!! 0/1 */
void KernelEv::wait(){
	if(eventPCB == NULL) { printf("ERROR: Something is wrong eventPCB is equal NULL, error location: KernelEv::wait\n"); exit(1); }
	if(eventPCB == Kernel::running)
		eventSem->wait();
}

void KernelEv::signal(){
	if(eventPCB == NULL) { printf("ERROR: Something is wrong eventPCB is equal NULL, error location: KernelEv::signal\n"); exit(1); }
	if(eventSem->Value()<0)
		eventSem->signal();
}
