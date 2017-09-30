/*
A test program for the MorseScheduler and MorseSchedulerQueue classes. A short series of
functions will be scheduled to repeatadly run and display output. This program will utilize
the input/output and scheduled time fields.
*/

#include <iostream>
#include "MorseScheduler.h"
#define QUEUE_SIZE 5

//A global pointer to the scheduler defined in main below.
MorseScheduler * sched;

//A global variable for the current scheduler time.
unsigned int currentTime;

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

	//Some input/output variables
	unsigned int in=0;
	unsigned int out=0;
	unsigned int * inp = &in;
	unsigned int * outp = &out;
	

	//Initalize the scheduler with the functions below.
	scheduler.schedule(&funcOne,inp,outp);
	scheduler.schedule(&funcTwo,inp,outp,5); //scheduled to execute every 5 "seconds".
	//funcThree and funcFour will be scheduled by funcOne and funcThree, respectively.
	scheduler.schedule(&funcFive,0,0,14); //scheduled at every quarter "minute".

	//Execute the scheduler for a simulated time of 60 "seconds".
	for(currentTime=0;currentTime<60;++currentTime)
	{
		std::cout << currentTime << ": ";
		scheduler.tick(currentTime); //we will use the index as the current scheduler time.
	}

	std::cout << "The execution of the scheduler is complete.\n";
	return 0;
}

//The functions to schedule in order
void funcOne(void * i,void * o)
{
	unsigned int *ip = (unsigned int *)i;
	unsigned int *op = (unsigned int *)o;
	std::cout << "Function One\n";
	*op = *ip + 1; //increment the output by 1 during each execution.
	sched->schedule(&funcThree,o,i); //funcTwo will do additional work for funcOne.
	sched->schedule(&funcOne,i,o); //Execute funcOne again, as in a loop.
}


void funcTwo(void * i,void * o)
{
	unsigned int *ip = (unsigned int *)i;
	unsigned int *op = (unsigned int *)o;
	std::cout << "Function Two: ";
	std::cout << "i: " << *ip << " o: " << *op << '\n'; //just dispay the input and output
	sched->schedule(&funcTwo,i,o,currentTime+5);
}

void funcThree(void * i,void * o)
{
	unsigned int *ip = (unsigned int *)i;
	unsigned int *op = (unsigned int *)o;
	std::cout << "Function Three\n";
	*op = *ip + 3; //increment the output by 3 during each execution.
	sched->schedule(&funcFour,o,i);
}

void funcFour(void * i,void * o)
{
	unsigned int *ip = (unsigned int *)i;
	unsigned int *op = (unsigned int *)o;
	std::cout << "Function Four\n";
	*op = *ip + 4; //increment the output by 4 during each execution.
}

void funcFive(void * i,void * o)
{
	std::cout << "Function Five\n";
	sched->schedule(&funcFive,0,0,currentTime+14); //execute every quarter "minute".
}
