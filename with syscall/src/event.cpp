/*
 * event.cpp
 *
 *  Created on: Jul 1, 2015
 *      Author: Lazar
 */

#include "event.h"

function_Arguments *fae;
unsigned sege, offe;

Event::Event(IVTNo ivtNo) {
	locke(1)
		function_Arguments *fa = new function_Arguments();
	unlocke(1)

		fa->arguments[0] = &ivtNo;
		fa->arguments[1] = this;

		fa->object_id   = 0;
		fa->function_id = 1;

		fae = fa;

	#ifndef BCC_BLOCK_IGNORE
		sege  = FP_SEG(fae);
		offe  = FP_OFF(fae);
		asm {
			mov ax, sege
			mov bx, offe
		}
	#endif
		sysCall();
	locke(1)
		delete fa;
	unlocke(1)
}
Event::~Event() {
	locke(1)
		function_Arguments *fa = new function_Arguments();
	unlocke(1)

		/*      no arguments      */
		fa->object_id   = myEvent;
		fa->function_id = 2;

		fae = fa;

#ifndef BCC_BLOCK_IGNORE
		sege = FP_SEG(fae);
		offe  = FP_OFF(fae);
		asm {
			mov ax, sege
			mov bx, offe
		}
#endif
		sysCall();
	locke(1)
		delete fa;
	unlocke(1)
}
void Event::wait()  {
	locke(1)
		function_Arguments *fa = new function_Arguments();
	unlocke(1)

		/*      no arguments      */
		fa->object_id   = myEvent;
		fa->function_id = 3;

		fae = fa;

#ifndef BCC_BLOCK_IGNORE
		sege = FP_SEG(fae);
		offe  = FP_OFF(fae);
		asm {
			mov ax, sege
			mov bx, offe
		}
#endif
		sysCall();
	locke(1)
		delete fa;
	unlocke(1)
}

void Event::signal(){
	locke(1)
		function_Arguments *fa = new function_Arguments();
	unlocke(1)

		/*      no arguments      */
		fa->object_id   = myEvent;
		fa->function_id = 4;

		fae = fa;

#ifndef BCC_BLOCK_IGNORE
		sege = FP_SEG(fae);
		offe  = FP_OFF(fae);
		asm {
			mov ax, sege
			mov bx, offe
		}
	#endif
		sysCall();
	locke(1)
		delete fa;
	unlocke(1)
}


