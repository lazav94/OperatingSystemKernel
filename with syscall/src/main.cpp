/*
 * main.cpp
 *
 *  Created on: July 1, 2015
 *      Author: Lazar
 */

#include "kernel.h"
#include <CONIO.H>

extern int userMain(int argc, char* argv[]);

int main(int argc, char* argv[]){


	clrscr(); //clear screen
	textcolor(YELLOW);
	cprintf("Lazar Vasic 298/13 Projekat OS1\r\n\n");
	textcolor(LIGHTCYAN);
	cprintf("Number of producers: %s\r\n",argv[1]);
	cprintf("Buffer size: %s\r\n",argv[2]);
	cprintf("Time slice: %s\r\n",argv[3]);

	Kernel::startKernel();
	int endStatus = userMain(argc,argv);
	Kernel::stopKernel();
	return endStatus;
}




