/*
 * thread.h
 *
 *  Created on: 08.06.2015.
 *      Author: Avax
 */

#ifndef THREAD_H_
#define THREAD_H_

typedef unsigned long StackSize;
const StackSize defaultStackSize=4096;
typedef unsigned int Time;
const Time defaultTimeSlice =2;
typedef int ID;

class PCB;

class Thread {
public:
	void start();
	void waitToComplete();
	static void sleep(Time timeToSleep);
	virtual ~Thread();
protected:
	friend class PCB;
	Thread(StackSize stackSize=defaultStackSize, Time timeSlice=defaultTimeSlice);
	virtual void run(){}
private:
	PCB* myPCB;
};

void dispatch();

#endif /* THREAD_H_ */
