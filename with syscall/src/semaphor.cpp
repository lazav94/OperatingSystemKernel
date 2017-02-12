/*
 * semaphor.cpp
 *
 *  Created on: Jul 1, 2015
 *      Author: Lazar
 */

#include "semaphor.h"
//new i delete must have locke(1)/unlocke(1)

function_Arguments *fas;
unsigned segs, offs;

Semaphore::Semaphore(int init){
	locke(1)
		function_Arguments *fa = new function_Arguments();
	unlocke(1)

		fa->arguments[0] = &init;
		fa->arguments[1] = this;

		fa->object_id   = 0;
		fa->function_id = 5;

		fas = fa;

#ifndef BCC_BLOCK_IGNORE
		segs  = FP_SEG(fas);
		offs  = FP_OFF(fas);
		asm {
			mov ax, segs
			mov bx, offs
		}
#endif
		sysCall();
	locke(1)
		delete fa;
	unlocke(1)
}

Semaphore::~Semaphore(){
	locke(1)
		function_Arguments *fa = new function_Arguments();
	unlocke(1)

		/*      no arguments      */
		fa->object_id   = myImpl;
		fa->function_id = 6;

		fas = fa;

#ifndef BCC_BLOCK_IGNORE
		segs  = FP_SEG(fas);
		offs  = FP_OFF(fas);
		asm {
			mov ax, segs
			mov bx, offs
		}
#endif
		sysCall();
	locke(1)
		delete fa;
	unlocke(1)
}

void Semaphore::wait(){
	locke(1)
		function_Arguments *fa = new function_Arguments();
	unlocke(1)

		/*      no arguments      */
		fa->object_id   = myImpl;
		fa->function_id = 7;

		fas = fa;

#ifndef BCC_BLOCK_IGNORE
		segs  = FP_SEG(fas);
		offs  = FP_OFF(fas);
		asm {
			mov ax, segs
			mov bx, offs
		}
#endif
		sysCall();
	locke(1)
		delete fa;
	unlocke(1)
}

void Semaphore::signal(){
	locke(1)
		function_Arguments *fa = new function_Arguments();
	unlocke(1)

		/*      no arguments      */
		fa->object_id   = myImpl;
		fa->function_id = 8;

		fas = fa;

#ifndef BCC_BLOCK_IGNORE
		segs  = FP_SEG(fas);
		offs  = FP_OFF(fas);
		asm {
			mov ax, segs
			mov bx, offs
		}
#endif
		sysCall();
	locke(1)
		delete fa;
	unlocke(1)
}

int Semaphore::val()const {

	locke(1)
			function_Arguments *fa = new function_Arguments();
	unlocke(1)

		/*      no arguments      */
		fa->object_id   = myImpl;
		fa->function_id = 9;

		fas = fa;

#ifndef BCC_BLOCK_IGNORE
		segs  = FP_SEG(fas);
		offs  = FP_OFF(fas);
		asm {
			mov ax, segs
			mov bx, offs
		}
#endif
		sysCall();
	locke(1)
		delete fa;
	unlocke(1)
	return returnValue;
}


