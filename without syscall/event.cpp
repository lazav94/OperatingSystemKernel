/*
 * Event.cpp
 *
 *  Created on: 09.06.2015.
 *      Author: Avax
 */
#include "lock.h"
#include "event.h"
#include "IVTEntry.h"
#include "KernelEv.h"

Event::Event(IVTNo ivtNo) {
	IVTEntry::entries[ivtNo]->setEvent(this);
	lock
	myImpl=new KernelEv(ivtNo);
	unlock

}

Event::~Event() {
	lock
	delete myImpl;
	unlock
}


void Event::signal(){
	myImpl->signal();
}

void Event::wait(){
	myImpl->wait();
}

