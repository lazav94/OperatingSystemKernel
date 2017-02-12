/*
 * main.cpp
 *
 *  Created on: 09.06.2015.
 *      Author: Avax
 */
#include "PCB.h"
#include "lock.h"
#include <IOSTREAM.H>

int userMain(int argc, char* argv[]);



int main(int argc, char* argv[]){
	PCB::initialize();

	//Thread::sleep(100);
	userMain(argc, argv);

	PCB::restore();


	return 0;
}
