/*
 * pcb.cpp
 *
 *  Created on: Jul 1, 2015
 *      Author: Lazar
 */

#include "pcb.h"
#include "syscall.h"
#include "kernel.h"

#include "semaphor.h"

static volatile unsigned newIP,newCS,newSP, newSS,oldSS,oldSP,newFS,newFO;

/*=============Static members=============*/
PQueue* PCB::sleepingQueue;

/*=============Constructor================*/
PCB::PCB(Time time, StackSize stacksize, Thread * t){

	this->timeSlice = time;
	this->pcbState  = PCB::NEW;
	this->ss		= 0;
	this->sp		= 0;

	if(stacksize > 65536) stacksize = 65536;
		this->stackSize = stacksize / 2;

	locke(1)
		this->blocked = new Queue();
	unlocke(1)
	this->myStack   = NULL;

	this->myThread = t;

	if(t != NULL){
		t->myPCB = Kernel::objects->addPCB(this);
		if(t->myPCB == -1) { printf("MyPCB = -1. Location PCB::PCB()->Kernel::objects->addPCB(this)\n"); exit(1); }
	}

}
/*=============Destructor================*/
PCB::~PCB() {
locke(1)
	delete []myStack;
	delete blocked;
unlocke(1)
}

/*=============Create Stack================*/
void PCB::createStack(){
locke(1)

	myStack=new unsigned[stackSize];

#ifndef BCC_BLOCK_IGNORE
	newSP = this->sp = FP_OFF(myStack + stackSize-16);
	newSS = this->ss = FP_SEG(myStack + stackSize-16);
	newIP = FP_OFF(Thread::wrapper);
	newCS = FP_SEG(Thread::wrapper);

	newFS = FP_SEG(myThread);
	newFO = FP_OFF(myThread);

	asm{
		mov oldSP,sp //save first sp
		mov oldSS,ss //save first ss

		mov ss,newSS //load second ss
		mov sp,newSP //load second sp

		push ax

		mov ax,newFS	//save new CS and IP on stack
		push ax
		mov ax,newFO
		push ax

		mov ax,0
		push ax
		push ax

		pushf //PSW
		pop ax
		or ax,1000000000b //10 0000 0000b
		push ax    //PSWI=1



		mov ax,newCS	//save new CS and IP on stack
		push ax
		mov ax,newIP
		push ax


		mov ax,0
						//save all registars on stack (hardware's method)
		push ax
		push bx
		push cx
		push dx
		push es
		push ds
		push si
		push di
		push bp

		mov newSP,sp	//save last point on second SP

		mov ss,oldSS	//load first sp & ss
		mov sp,oldSP
	}

	sp=newSP;

#endif
	if(this != Kernel::idlePCB){
			pcbState=PCB::READY;
			Scheduler::put(this);
	}
unlocke(1)
}

void PCB::createSystemStack(function_Arguments *f){

	if(myStack == NULL)
		myStack = new unsigned [stackSize];


#ifndef BCC_BLOCK_IGNORE

	//lock unlock = syscall!
	newSP = this->sp = FP_OFF(myStack + stackSize-16);
	newSS = this->ss = FP_SEG(myStack + stackSize-16);
	newIP = FP_OFF(sysFun);
	newCS = FP_SEG(sysFun);

	newFS = FP_SEG(f);
	newFO = FP_OFF(f);

	asm{
		mov oldSP,sp //save first sp
		mov oldSS,ss //save first ss

		mov ss,newSS //load second ss
		mov sp,newSP //load second sp

		push ax

		mov ax,newFS	//save new CS and IP on stack
		push ax
		mov ax,newFO
		push ax

		mov ax,0
		push ax
		push ax

		pushf //PSW
		pop ax
		or ax,1000000000b //10 0000 0000b
		push ax    //PSWI=1



		mov ax,newCS	//save new CS and IP on stack
		push ax
		mov ax,newIP
		push ax



		mov ax,0
						//save all registars on stack (hardware's method)
		push ax
		push bx
		push cx
		push dx
		push es
		push ds
		push si
		push di
		push bp



		mov newSP,sp	//save last point on second SP

		mov ss,oldSS	//load first sp & ss
		mov sp,oldSP


	}

	sp=newSP;
	//ss = newSS;
#endif

}


/*=============Unblocke(1) All================*/
void PCB::unblockAll(){
	locke(1)
	while(Kernel::running->blocked->first!=NULL){
		PCB* curr = Kernel::running->blocked->DELETE();
		curr->pcbState = READY;
		Scheduler::put(curr);
	}
	unlocke(1)
}

void PCB::unblockOne(){
	locke(1)
	if(Kernel::running->blocked->first!=NULL){
		PCB* curr = Kernel::running->blocked->DELETE();
		curr->pcbState = READY;
		if(curr != NULL)
			Scheduler::put(curr);
	}
	unlocke(1)
}

void PCB::waitToComplete(){

		if(this == NULL)			   		  {     return; } //Null pointer exception!
		if(this->pcbState == PCB::FINISED)	  {     return; } //Thread is finished!
		if(this->pcbState == PCB::NEW) 	  	  {     return; } //Thread hasn't started jet!
		if(this == Kernel::idlePCB)	          {     return; } //Idle Thread never stop! Can't waiting for Idle Thread!
		if(this == systemPCB)	              { printf("w82c5\n");    return; } //Can't wait for starting (system) Thread!
		if(this == Kernel::running)           {     return; } //Can't wait for own thread!
		if(this->pcbState == PCB::RUNNING)    {     return; } //Can't wait for own thread!


	locke(1)
		Kernel::running->pcbState = PCB::BLOCKED;
		this->blocked->INSERT(Kernel::running);
	unlocke(1)

	dispatch();

	}
void PCB::sleep(Time tts, PCB *pcbSleep){
	if(tts != 0 && pcbSleep != NULL){
		PCB::sleepingQueue->INSERT(pcbSleep, tts);
		dispatch();
	}
	else printf("ERROR SLEEP\n");
}
void PCB::turnOffThread(){
	this->pcbState = PCB::FINISED;
	this->unblockAll();
	dispatch();
}

