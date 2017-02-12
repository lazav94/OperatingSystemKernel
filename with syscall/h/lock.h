/*
 * lock.h
 *
 *  Created on: Jul 1, 2015
 *      Author: Lazar
 */

#ifndef LOCK_H_
#define LOCK_H_

extern volatile unsigned int lockFlag;              // from lock
extern volatile unsigned int counterInterruption;   // from lock
extern volatile unsigned int explicitContextSwitch; // from timer
void dispatch();

#define locke(lockFlagEnable)\
			if(lockFlagEnable){\
				lockFlag=1;\
				++counterInterruption;\
			}\
			else { asm  cli; } //Clear interrupt bit

#define unlocke(lockFlagEnable)\
		if(lockFlagEnable){\
			--counterInterruption;\
			if(counterInterruption<=0){\
				lockFlag=0;\
				counterInterruption = 0 ;\
				if(explicitContextSwitch)\
					dispatch();\
			}\
		}\
		else { asm  sti; } //Set interrupt bit

#endif /* LOCK_H_ */
