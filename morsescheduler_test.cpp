/*
Copyright (C) 2017 David Pretola

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3 as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/*
A test program for the MorseScheduler and MorseSchedulerQueue classes. A short series of
functions will be scheduled to repeatadly run and display output.
*/

#include <iostream>
#include "MorseScheduler.h"
#define QUEUE_SIZE 5

//A global pointer to the scheduler defined in main below.
MorseScheduler * sched;

//Prototypes for the test functions below
void funcOne(void *,void*);
void funcTwo(void *,void *);
void funcThree(void *,void *);
void funcFour(void *,void *);
void funcFive(void *,void *);

int main()
{
	/*fca[] is an array of pointers to functions that accept void * as an argument and 
		return nothing.*/
	MorseSchedulerQueueElement queue[QUEUE_SIZE];
	MorseSchedulerQueue schedulerQueue(queue,QUEUE_SIZE);
	MorseScheduler scheduler(&schedulerQueue);
	sched = &scheduler; //set the global pointer to the scheduler

	//Initalize the scheduler with the functions below.
	scheduler.schedule(&funcOne);
	scheduler.schedule(&funcTwo);
	scheduler.schedule(&funcThree);
	scheduler.schedule(&funcFour);
	scheduler.schedule(&funcFive);

	//Execute the first 15 functions on the scheduler.
	for(int i=0;i<15;++i)
	{
		std::cout << i+1 << ": ";
		scheduler.tick();
	}

	std::cout << "The execution of the scheduler is complete.\n";
	return 0;
}

//The functions to schedule in order
void funcOne(void * i,void * o)
{
	std::cout << "Function One\n";
	sched->schedule(&funcOne);
}

void funcTwo(void * i,void * o)
{
	std::cout << "Function Two\n";
	sched->schedule(&funcTwo);
}

void funcThree(void * i,void * o)
{
	std::cout << "Function Three\n";
	sched->schedule(&funcThree);
}

void funcFour(void * i,void * o)
{
	std::cout << "Function Four\n";
	sched->schedule(&funcFour);
}

void funcFive(void * i,void * o)
{
	std::cout << "Function Five\n";
	sched->schedule(&funcFive);
}
