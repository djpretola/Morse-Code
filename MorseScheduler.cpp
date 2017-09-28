/*
MorseScheduler class

A Scheduler Class that executes each function pointer from MorseSchedulerQueue in order
*/

#include "MorseScheduler.h"

MorseScheduler::MorseScheduler(MorseSchedulerQueue * queue)
{
	this->queue = queue;
}

void MorseScheduler::tick()
{
	void (*fp)(void*) = queue->deq();
	if(fp != 0)
	{
		fp(0);
	}
}

void (*MorseScheduler::schedule(void(*c)(void*)))(void*)
{
	return queue->enq(c);
}
