/*
 * timer.cpp
 *
 *  Created on: 09.06.2015.
 *      Author: Avax
 */
#include "lock.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include <IOSTREAM.H>
#include "sleepQue.h"
unsigned int counter=100;
volatile unsigned short demanded_takeover=0;
unsigned tsp, tss, tbp;
unsigned oldTimerSEG, oldTimerOFF;
volatile unsigned short SchedulerEmpty=1;
void tick();

void interrupt timer(){
	tick();
	if(!demanded_takeover){
	#ifndef BCC_BLOCK_IGNORE
		asm int 60h
	#endif
		if(PCB::running->timeSlice!=0)
			counter--;
		sleepQue::tick();

		sleepQue::remove();

	}


	if((counter==0 && PCB::running->timeSlice!=0) || demanded_takeover==1){
		if(lockFlag){

			demanded_takeover=0;
		#ifndef BCC_BLOCK_IGNORE
			asm{
				mov tsp, sp
				mov tss, ss
				mov tbp, bp
			}
		#endif
			PCB::running->ss=tss;
			PCB::running->sp=tsp;
			PCB::running->bp=tbp;
			if(PCB::running->state!=PCB::BLOCKED && PCB::running!=PCB::idle && PCB::running->state!=PCB::DONE){
				Scheduler::put(PCB::running);
				SchedulerEmpty=0;
			}
			PCB::running=Scheduler::get();
			if(PCB::running==0){
				SchedulerEmpty=1;
				PCB::running=PCB::idle;
			}
			else{

				PCB::running->state=PCB::RUNNING;
			}
			tsp=PCB::running->sp;
			tss=PCB::running->ss;
			tbp=PCB::running->bp;

			counter=PCB::running->timeSlice;

			#ifndef BCC_BLOCK_IGNORE
				asm{
					mov sp, tsp
					mov ss, tss
					mov bp, tbp
				}
			#endif




		}
		else demanded_takeover=1;



	}

asm cli;
}

void init(){
	lock
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
	unlock
}

void rest(){
	lock
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
	unlock
}
