/*
 * thread.cpp
 *
 *  Created on: Jul 1, 2015
 *      Author: Lazar
 */


#include "kernel.h"


void interrupt timer();

function_Arguments *funt;
unsigned segt, offt;

Thread::Thread(StackSize stackSize, Time timeSlice){
	locke(1)
			function_Arguments *fat = new function_Arguments();
	unlocke(1);

		fat->arguments[0] = &timeSlice;
		fat->arguments[1] = &stackSize;
		fat->arguments[2] = this;

		fat->object_id  = 0;
		fat->function_id = 10;

		funt = fat;

#ifndef BCC_BLOCK_IGNORE
		segt=FP_SEG(funt);
		offt=FP_OFF(funt);
		asm {
			mov ax, segt;
			mov bx, offt;
		}
#endif
		sysCall();
	locke(1)
		delete fat;
	unlocke(1)
}

Thread::~Thread(){
	waitToComplete();
	locke(1)
		function_Arguments *fat = new function_Arguments();
	unlocke(1);

	/*      no arguments      */
		fat->object_id  = myPCB;
		fat->function_id = 11;

	funt = fat;

#ifndef BCC_BLOCK_IGNORE
		segt = FP_SEG(funt);
		offt  = FP_OFF(funt);
		asm {
			mov ax, segt
			mov bx, offt
		}
#endif
		sysCall();
	locke(1)
		delete fat;
	unlocke(1)

}
void Thread::waitToComplete(){
locke(1)
		function_Arguments *fat = new function_Arguments();
unlocke(1);

		/*      no arguments      */
		fat->object_id  = myPCB;
		fat->function_id = 12;

		funt = fat;

#ifndef BCC_BLOCK_IGNORE
		segt = FP_SEG(funt);
		offt  = FP_OFF(funt);
		asm {
			mov ax, segt
			mov bx, offt
		}
#endif
		sysCall();
	locke(1)
		delete fat;
	unlocke(1)

}

void Thread::start(){
locke(1)
		function_Arguments *fat = new function_Arguments();
unlocke(1);

		/*      no arguments      */
		fat->object_id  = myPCB;
		fat->function_id = 13;

		funt = fat;

#ifndef BCC_BLOCK_IGNORE
		segt = FP_SEG(funt);
		offt  = FP_OFF(funt);
		asm {
			mov ax, segt
			mov bx, offt
		}
#endif
		sysCall();
	locke(1)
		delete fat;
	unlocke(1)

}

void Thread::sleep(Time tts){
locke(1)
		function_Arguments *fat = new function_Arguments();
unlocke(1);
		/*      static function      */

		fat->arguments[0] = &tts;

		fat->object_id   = 0;// Kernel::running->myThread->myPCB; //0
		fat->function_id = 14;

		funt = fat;

#ifndef BCC_BLOCK_IGNORE
		segt = FP_SEG(funt);
		offt  = FP_OFF(funt);
		asm {
			mov ax, segt
			mov bx, offt
		}
#endif
		sysCall();
	locke(1)
		delete fat;
	unlocke(1)

}

void Thread::turnOFFThread(){
	locke(1)
		function_Arguments *fat = new function_Arguments();
	unlocke(1);

		/*      no arguments      */
		fat->object_id  = myPCB;
		fat->function_id = 15;

		funt = fat;

#ifndef BCC_BLOCK_IGNORE
		segt = FP_SEG(funt);
		offt  = FP_OFF(funt);
		asm {
			mov ax, segt
			mov bx, offt
		}
#endif
		sysCall();
	locke(1)
		delete fat;
	unlocke(1)
}

ID Thread::getPCB(){
	return myPCB;
}

void Thread::setPCB(ID id){
	myPCB = id;
}

void Thread::wrapper(Thread* running){
	running->run();
	running->turnOFFThread(); // pcbstate = Finised , unblockAll, dispatch() //
}

void dispatch(){
	explicitContextSwitch = 1;
	timer();
}


