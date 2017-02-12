/*
 * thread.h
 *
 *  Created on: Jul 1, 2015
 *      Author: Lazar
 */

#ifndef THREAD_H_
#define THREAD_H_


typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time;
const Time defaultTimeSlice = 2;
typedef int ID;

class PCB;				// Kernel's implementation of a user's thread

class Thread {
public:
	void start();
	void waitToComplete();
	virtual ~Thread();
	static void sleep(Time timeToSleep);

	//ID myPCB;
	ID   getPCB();      //auxiliary method
	void setPCB(ID id); //auxiliary method
protected:
	friend class Kernel;
	friend class idleThread;
	friend class PCB;

	Thread (StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	virtual void run(){}
private:
	static void wrapper(Thread *running);
	void turnOFFThread();

	ID myPCB;

};


void dispatch();


#endif /* THREAD_H_ */
