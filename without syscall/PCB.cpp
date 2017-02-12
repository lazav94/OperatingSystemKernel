/*
 * PCB.cpp
 *
 *  Created on: 09.06.2015.
 *      Author: Avax
 */

#include "PCB.h"
#include "lock.h"
#include <DOS.H>

#include "idleThrd.h"
#include "sleepQue.h"
#include "SCHEDULE.H"

PCB* PCB::running=0;
PCB* PCB::main=0;
PCB* PCB::idle=0;
Thread* t;
idleThread *iddle;

extern volatile unsigned short SchedulerEmpty;

PCB::PCB(StackSize stackSize, Time timeSlice, Thread* t) : done(0){
	if(stackSize>65536) stackSize=65536;
	stackSize/=2;
	this->stackSize=stackSize;
	this->timeSlice=timeSlice;
	myThread=t;
	stack=0;
	ss=sp=bp=0;
	blockedThread=0;
	state=PCB::NEW;
}

PCB::~PCB() {
	lock
		delete[]stack;
	unlock
}

void PCB::create(){
lock
	stack=new unsigned[stackSize];
	stack[stackSize-1]=0x200;
#ifndef BCC_BLOCK_IGNORE
	stack[stackSize-2]=FP_SEG(starter);
	stack[stackSize-3]=FP_OFF(starter);
	sp=FP_OFF(stack+stackSize-12);
	ss=FP_SEG(stack+stackSize-12);
#endif
	if(state!=PCB::IDLE){
		state=PCB::READY;
		SchedulerEmpty=0;
		Scheduler::put(this);
	}
unlock
}

void PCB::starter(){
	PCB::running->myThread->run();
	PCB::running->exitThread();
}

void PCB::initialize(){
	asm cli;

	init();
	t=new Thread(0, 100);
	PCB::running=t->myPCB;
	t->myPCB->state=PCB::RUNNING;
	iddle=new idleThread();
	PCB::idle= iddle->myPCB;
	PCB::idle->state=PCB::IDLE;
	iddle->start();

	asm sti;
}

void PCB::restore(){
	asm cli;

	delete iddle;
	delete t;
	rest();

	asm sti;
}

void PCB::sleep(PCB* p, Time timeToSleep){
	sleepQue::put(p, timeToSleep);
	dispatch();
}
void PCB::exitThread(){
	state=PCB::DONE;

	while(blockedThread>0){
		done.signal();
		lock
		blockedThread--;
		unlock
	}
	dispatch();
}

void PCB::waitToComplete(){
	if(state!=PCB::IDLE && state!=PCB::DONE && state!=PCB::RUNNING){
		lock
		blockedThread++;
		unlock
		done.wait();
	}
}
