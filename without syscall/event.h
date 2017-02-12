/*
 * Event.h
 *
 *  Created on: 09.06.2015.
 *      Author: Avax
 */

#ifndef EVENT_H_
#define EVENT_H_
#include "IVTEntry.h"
typedef unsigned char IVTNo;
class KernelEv;

class Event {
public:
 Event (IVTNo ivtNo);
 ~Event ();
 void wait ();
protected:
 friend class KernelEv;
 friend class IVTEntry;
 void signal(); // can call KernelEv
private:
 KernelEv* myImpl;
};

#endif /* EVENT_H_ */
