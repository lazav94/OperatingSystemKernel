/*
 * idleThread.cpp
 *
 *  Created on: 09.06.2015.
 *      Author: Avax
 */

#include "IOSTREAM.H"
#include "idleThrd.h"
extern volatile unsigned short SchedulerEmpty;
void idleThread::run(){
	while(1){
		if(!SchedulerEmpty)
			dispatch();
	}
}
idleThread::idleThread(): Thread(300, 1){}

