/*
 * syscall.cpp
 *
 *  Created on: Aug 4, 2015
 *      Author: OS1
 */

#include "syscall.h"
#include "kernelev.h"
#include "kernelse.h"
#include "thread.h"
#include "pcb.h"
#include "lock.h"
#include <DOS.H>
#include <STDLIB.H>
#include <STDIO.H>



typedef unsigned long StackSize;
typedef unsigned int Time;

volatile unsigned ttss,ttsp;
volatile unsigned syss,syso;
int returnValue;

PCB* systemPCB;
function_Arguments* funArg = NULL;

void interrupt sysCall(){

#ifndef BCC_BLOCK_IGNORE
	asm{
	mov syss, ax
	mov syso, bx
	}

	funArg=(function_Arguments*)MK_FP(syss,syso);
#endif

locke(1)
#ifndef BCC_BLOCK_IGNORE
	asm{
		mov ttsp, sp
		mov ttss, ss
	}
#endif
	Kernel::running->sp = ttsp;
	Kernel::running->ss = ttss;

	systemPCB->createSystemStack(funArg);

	ttsp = systemPCB->sp;
	ttss = systemPCB->ss;

#ifndef BCC_BLOCK_IGNORE
	asm{
		mov sp, ttsp
		mov ss, ttss
	}
#endif

}

void  interrupt sysRet(){

	ttss = Kernel::running->ss;
	ttsp = Kernel::running->sp;
#ifndef BCC_BLOCK_IGNORE
	asm{
		mov sp, ttsp
		mov ss, ttss
	}
#endif

unlocke(1)
}

void  sysFun(function_Arguments *argum){

	unsigned id   = argum->function_id;
	ID obID = argum->object_id;

	/* Event system call */
	if      (id >0 && id <5) {
		KernelEv*  kernelEvent = (KernelEv*) Kernel::objects->getObject(obID);

		switch(id){
		case 1:
			locke(1)
				kernelEvent = new KernelEv(*(IVTNo*)argum->arguments[0], (Event *)argum->arguments[1]);
			unlocke(1)
			break;
		case 2:
			locke(1)
				delete kernelEvent;
				Kernel::objects->deleteObject(obID);
			unlocke(1)
			break;
		case 3:
			kernelEvent->wait();
			break;
		case 4:
			kernelEvent->signal();
			break;
		default: printf("FATAL ERROR system function EVENT! \n"); exit(-1); break;
		}

	}
	/* Semaphor system call */
	else if (id > 4 && id <10)  {
		KernelSe* kernelSemaphor = (KernelSe*) Kernel::objects->getObject(obID);

		switch(id){
		case 5:
			locke(1)
				kernelSemaphor = new KernelSe ((Semaphore*)argum->arguments[1],*(int*)argum->arguments[0] );
			unlocke(1)
			break;
		case 6:
			locke(1)
				delete kernelSemaphor;
				Kernel::objects->deleteObject(obID);
			unlocke(1);
			break;
		case 7:
			kernelSemaphor->wait();
			break;
		case 8:
			kernelSemaphor->signal();
			break;
		case 9:
			returnValue = kernelSemaphor->Value();
			break;

		default: printf("FATAL ERROR system function SEMAPHORE! \n"); exit(-1); break;
		}
	}
	/* Thread system call */
	else if (id >9 && id <17) {
		PCB *kernelPCB = (PCB*)Kernel::objects->getObject(obID);

		switch(id){
		case 10:
			locke(1)
				kernelPCB = new PCB(*(Time*)argum->arguments[0],*(StackSize*)argum->arguments[1],(Thread*)argum->arguments[2]);
			unlocke(1)
			break;
		case 11:
			locke(1)
				delete kernelPCB;
				Kernel::objects->deleteObject(obID);
			unlocke(1)
				break;
		case 12:
			kernelPCB->waitToComplete();
			break;
		case 13:
			kernelPCB->createStack();
			break;
		case 14:
			kernelPCB->sleep(*(Time*)argum->arguments[0], Kernel::running);
			break;
		case 15:
			kernelPCB->turnOffThread();
			break;

		default: printf("FATAL ERROR system function THREAD! \n"); exit(-1); break;
		}

	}
	sysRet();

}


sysObject::sysObject():numObject(0){
	objectMap = new void*[MAX_OBJECT];
}
sysObject::~sysObject(){
	delete []objectMap;
	delete objectMap;

}

ID sysObject::addPCB(PCB* object){
	if(object != NULL){
		for(int i = 0; i < MAX_OBJECT; i++)
			if(objectMap[i] == NULL){

				objectMap[i] = object;
				numObject++;
				return i;
			}
	}
	return -1;
}
ID sysObject::addSemaphor(KernelSe* object){
	if(object != NULL){
		for(int i = 0; i < MAX_OBJECT; i++){
			if(objectMap[i] == NULL){


				objectMap[i] = object;
				numObject++;
				return i;
			}
		}
	}
	return -1;
}
ID sysObject::addEvent(KernelEv* object){
	if(object != NULL){
		for(int i = 0; i < MAX_OBJECT; i++)
			if(objectMap[i] == NULL){

				objectMap[i] = object;
				numObject++;
				return i;
			}
	}
	return -1;
}

void* sysObject::getObject(ID id){
	if(id < 0 || id > MAX_OBJECT) { printf("ERROR: Out of bounders. Location: sysObject::getObject()\n");exit(1);}
	if(objectMap[id] == NULL && id != 0){ printf("GRESKA GET OBJECT NULL\n"); exit(1);}
	return objectMap[id];
}

void sysObject::deleteObject(ID id){
	if(id < 0 || id > MAX_OBJECT) {printf("Greska deleteObject\n");return;}
	objectMap[id] = NULL;
	numObject--;

}

