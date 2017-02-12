/*
 * timer.cpp
 *
 *  Created on: Jun 30, 2015
 *      Author: Lazar
 */
#include "lock.h"
#include "thread.h"
#include "pcb.h"
#include "pqueue.h"
#include "SCHEDULE.H"
#include "STDIO.H"

unsigned int brojac = 100;
unsigned tss,tsp;
unsigned oldTimerSEG,oldTimerOFF;
volatile unsigned int explicitContextSwitch = 0;

void tick();

//TIMER SA LABA
void interrupt timer(){
	tick();
	if(!explicitContextSwitch){
#ifndef BCC_BLOCK_IGNORE
	asm int 60h
#endif

	if(Kernel::running->timeSlice != 0) brojac--;
	PQueue::decrementTime();
	PQueue::DELETE();
	}

	if((Kernel::running->timeSlice!=0 &&  brojac==0)|| explicitContextSwitch==1){
		if(lockFlag==0){

			explicitContextSwitch = 0;
#ifndef BCC_BLOCK_IGNORE
			asm{
				mov tsp,sp
				mov tss,ss
			}
#endif
			Kernel::running->ss=tss;
			Kernel::running->sp=tsp;

			if(Kernel::running->pcbState!=PCB::BLOCKED && Kernel::running->pcbState!=PCB::FINISED && Kernel::running!= Kernel::idlePCB )
				Scheduler::put(Kernel::running);

			Kernel::running=Scheduler::get();

			if(Kernel::running!=NULL ){
				Kernel::running->pcbState=PCB::RUNNING;
			}
			else{ //IDLE

				Kernel::running = Kernel::idlePCB;
			}
			tsp=Kernel::running->sp;
			tss=Kernel::running->ss;

			brojac = Kernel::running->timeSlice;

#ifndef BCC_BLOCK_IGNORE
			asm{
				mov sp,tsp
				mov ss,tss
			}
#endif
			}else explicitContextSwitch = 1;
		}

	locke(0)//cli

	}

void init(){
	locke(1)
#ifndef BCC_BLOCK_IGNORE
	asm{
		push es
		push ax

		mov ax, 0
		mov es, ax

		mov ax, word ptr es:0022h
		mov word ptr oldTimerSEG, ax
		mov ax, word ptr es:0020h
		mov word ptr oldTimerOFF, ax

		mov word ptr es:0022h, seg timer
		mov word ptr es:0020h, offset timer

		mov ax, oldTimerSEG
		mov word ptr es:0182h, ax
		mov ax, oldTimerOFF
		mov word ptr es:0180h, ax

		pop ax
		pop es
	}
#endif
	unlocke(1)
}

void rest(){
	locke(1)
#ifndef BCC_BLOCK_IGNORE
	asm {
		push es
		push ax

		mov ax, 0
		mov es, ax

		mov ax, word ptr oldTimerSEG
		mov word ptr es:0022h, ax
		mov ax, word ptr oldTimerOFF
		mov word ptr es:0020h, ax

		pop ax
		pop es
	}
#endif
	unlocke(1)
}
