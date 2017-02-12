/*
 * lock.h
 *
 *  Created on: 09.06.2015.
 *      Author: Avax
 */

#ifndef LOCK_H_
#define LOCK_H_
extern int cnt;
void dispatch();
extern volatile unsigned short demanded_takeover;
extern volatile unsigned short lockFlag;

#define lock\
		lockFlag=0; cnt++;

#define unlock\
		cnt--;\
		if(cnt<=0){\
			lockFlag=1; cnt=0;\
			if(demanded_takeover){\
				dispatch();\
			}\
		}

#endif /* LOCK_H_ */
