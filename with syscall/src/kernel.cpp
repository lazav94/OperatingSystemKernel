/*
 * kernel.cpp
 *
 *  Created on: Jul 1, 2015
 *      Author: Lazar
 */

#include "kernel.h"
#include "semaphor.h"
#include <CONIO.H>

idleThread* idleT;
PCB*        Kernel::idlePCB     = NULL;
PCB* 		Kernel::running 	= NULL;
sysObject*  Kernel::objects     = NULL;



void Kernel::startKernel(){
locke(0) //asm cli;

	textcolor(LIGHTBLUE);
	cprintf("\r\nStarting kernel......\n");
	objects = new sysObject();

	systemPCB=new PCB(100, 500, 0); //systemPCB->myStack=new unsigned[systemPCB->stackSize]; // syscall -> PCB::crateSystemStack()

	funArg=new function_Arguments();

	init();

	Kernel::running = new PCB(100, 100, 0);

	// Creating and starting idle thread.
	idleT = new idleThread();
	idlePCB = (PCB*)objects->getObject(idleT->myPCB);
	idleT->start();


	cprintf("\rStarting kernel finished!!!\r\n\n");

unlocke(0)  //asm sti;
}

void Kernel::stopKernel(){
locke(0)   //asm cli;

	textcolor(LIGHTRED);
	cputs("\r\nStopping kernel......\n\r");

	delete idleT; delete idlePCB;
	Kernel::running->pcbState = PCB::RUNNING;
	delete Kernel::running;
//	delete PCB::sleepingQueue;
	delete objects;

//	while(1){
//		PCB* temp = Scheduler::get();
//		if(temp == NULL) break;
//		delete temp;
//	}//empty scheduler

	rest();

	cputs("\rKernel finised with work!!!\n\r");
unlocke(0) //asm sti;
}
