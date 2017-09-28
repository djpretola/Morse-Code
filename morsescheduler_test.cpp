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
void funcOne(void *);
void funcTwo(void *);
void funcThree(void *);
void funcFour(void *);
void funcFive(void *);

int main()
{
	/*fca[] is an array of pointers to functions that accept void * as an argument and 
		return nothing.*/
	void(*fca[QUEUE_SIZE])(void*); 
	MorseSchedulerQueue schedulerQueue(fca,QUEUE_SIZE);
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
void funcOne(void * v)
{
	std::cout << "Function One\n";
	sched->schedule(&funcOne);
}

void funcTwo(void * v)
{
	std::cout << "Function Two\n";
	sched->schedule(&funcTwo);
}

void funcThree(void * v)
{
	std::cout << "Function Three\n";
	sched->schedule(&funcThree);
}

void funcFour(void * v)
{
	std::cout << "Function Four\n";
	sched->schedule(&funcFour);
}

void funcFive(void * v)
{
	std::cout << "Function Five\n";
	sched->schedule(&funcFive);
}
