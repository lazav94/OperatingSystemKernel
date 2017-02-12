/*
 * IVTEntry.h
 *
 *  Created on: 09.06.2015.
 *      Author: Avax
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

typedef void interrupt (*pInterrupt)(...);

class KernelEv;

pInterrupt getvector(int entryNum);
void setvector(int entryNum, pInterrupt newRoutine);


class Event;

class IVTEntry {
public:

	pInterrupt oldRoute;
	pInterrupt newRoute;
	IVTEntry(unsigned entry, pInterrupt oldRoute);
	virtual ~IVTEntry();
	void setEvent(Event* e);
	void signal();
	static IVTEntry* entries[256];
private:
	Event* event;
	unsigned entry;


};

#define PREPAREENTRY(x, y)\
	void interrupt myFunction##x(...){\
		IVTEntry::entries[##x]->signal();\
		if(y)\
			IVTEntry::entries[##x]->oldRoute();\
	}\
	IVTEntry entry##x(##x, myFunction##x);\


#endif /* IVTENTRY_H_ */
