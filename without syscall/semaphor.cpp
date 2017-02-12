/*
 * semaphore.cpp
 *
 *  Created on: 09.06.2015.
 *      Author: Avax
 */

#include "semaphor.h"

#include "KSem.h"
#include "lock.h"

Semaphore::Semaphore(int val) {
	lock
	myImpl=new KernelSem(val);
	unlock
}

Semaphore::~Semaphore() {
	lock
	delete myImpl;
	unlock
}

void Semaphore::signal(){
	myImpl->signal();
}
void Semaphore::wait(){
	myImpl->wait();
}
int Semaphore::val()const{
	return myImpl->value();
}
