/*
 * syscall.h
 *
 *  Created on: Aug 4, 2015
 *      Author: OS1
 */

#ifndef SYSCALL_H_
#define SYSCALL_H_

#include "kernel.h"
#include "kernelev.h"
#include "kernelse.h"

#include "thread.h"
#include "event.h"
#include "pcb.h"
#include <DOS.H>

#define MAX_OBJECT 32024
#define MAX_NO_ARG 5

typedef int ID;

class PCB;
class Event;

struct function_Arguments{
	unsigned   function_id;
	int        object_id;
	void*      arguments[MAX_NO_ARG];
};

class sysObject{
private:
	void** objectMap;
	int    numObject;

public:
	sysObject();
	~sysObject();

	ID addPCB        (PCB*       object);
	ID addSemaphor   (KernelSe*  object);
	ID addEvent      (KernelEv*  object);

	void deleteObject (ID id);
	void* getObject   (ID id);

};

extern function_Arguments* funArg;
extern int returnValue;
extern sysObject* objects;
extern PCB* systemPCB;

void  interrupt sysCall();
void  interrupt sysRet();
void  sysFun(function_Arguments *fa);


#endif /* SYSCALL_H_ */
