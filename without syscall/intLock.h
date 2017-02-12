#ifndef _INTLOCK_H_
#define _INTLOCK_H_

#include <semaphor.h>

extern Semaphore mutex_glb;

#define intLock mutex_glb.wait();
#define intUnlock mutex_glb.signal();

#endif