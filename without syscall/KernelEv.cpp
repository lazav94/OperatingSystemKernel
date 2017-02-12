/*
 * KernelEv.cpp
 *
 *  Created on: 09.06.2015.
 *      Author: Avax
 */

#include "KernelEv.h"
#include "PCB.h"
#include "lock.h"
#include "IVTEntry.h"
#include "IOSTREAM.H"
KernelEv::KernelEv(unsigned Entry) : bin(0) {
	lock
	myPCB=PCB::running;
	entry=Entry;
	unlock
	if(IVTEntry::entries[entry]->oldRoute==0){
		IVTEntry::entries[entry]->oldRoute=getvector(entry);
		setvector(entry, IVTEntry::entries[entry]->newRoute);
	}
}



void KernelEv::signal(){
	if(bin.val()<0)
		bin.signal();
}
void KernelEv::wait(){
	if(PCB::running==myPCB)
		bin.wait();
}
KernelEv::~KernelEv(){
	setvector(entry, IVTEntry::entries[entry]->oldRoute);
	IVTEntry::entries[entry]->setEvent(0);

}
