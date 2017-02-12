/*
 * idleThread.cpp
 *
 *  Created on: 09.06.2015.
 *      Author: Avax
 */


#include "idleThrd.h"
#include <STDIO.H>

/*int i;

void a(){
#ifndef BCC_BLOCK_IGNORE
	asm{
		push ax
		mov ax, [bp]+2
		mov i, ax
		pop ax
	}
#endif
}
void b(){
#ifndef BCC_BLOCK_IGNORE
	asm{
		push ax
		mov ax, i
		mov [bp]+2, ax
		pop ax
	}
#endif
}
*/

void idleThread::run(){
	while(1);


//	a(); b(); //infinity memoryless loop
}
idleThread::idleThread(): Thread(200, 1){}


