/*
 * sleepQue.h
 *
 *  Created on: 09.06.2015.
 *      Author: Avax
 */

#ifndef SLEEPQUE_H_
#define SLEEPQUE_H_
#include "PCB.h"


class sleepQue {
public:
	struct Elem{
		PCB* pcb;
		Elem* next;
		Time timeToSleep;
		Elem(PCB* p, Time t){
			pcb=p; timeToSleep=t;
			next=0;
		}
	};

	static void put(PCB* p, Time timeToSleep);
	static void remove();
	static void tick();
private:
	sleepQue(){}
	static Elem* head;
};

#endif /* SLEEPQUE_H_ */
