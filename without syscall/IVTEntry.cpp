/*
 * IVTEntry.cpp
 *
 *  Created on: 09.06.2015.
 *      Author: Avax
 */

#include "IVTEntry.h"
#include "event.h"
#include "lock.h"

IVTEntry* IVTEntry::entries[256];

IVTEntry::IVTEntry(unsigned int entry, pInterrupt newRoute) {
	this->oldRoute=0;
	this->newRoute=newRoute;
	this->entry=entry;
	entries[entry]=this;
	event=0;
}

IVTEntry::~IVTEntry() {

}

void IVTEntry::setEvent(Event* e){
	event=e;
}

void IVTEntry::signal(){
	event->signal();
}

pInterrupt getvector(int entryNum){
	lock
	pInterrupt* ret=(pInterrupt*)(4*entryNum);
	unlock
	return *ret;
}

void setvector(int entryNum, pInterrupt newRoutine){
	lock
	pInterrupt* ret=(pInterrupt*)(4*entryNum);
	*ret=newRoutine;
	unlock
}

