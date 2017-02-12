/*
 * lock.cpp
 *
 *  Created on: Jul 1, 2015
 *      Author: Lazar
 */

#include "lock.h"


volatile unsigned int lockFlag            = 0;
					//lockFlag = 0 => context switch enable, default
				    //lockFlag = 1 => context switch disable
volatile unsigned int counterInterruption = 0;

				   //LOCK
				   //UNLOCK
