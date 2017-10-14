/*
MorseScheduler class

A Scheduler Class that executes each function pointer from MorseSchedulerQueue in order
*/

#include "MorseScheduler.h"

MorseScheduler::MorseScheduler(MorseSchedulerQueue * queue)
{
	this->queue = queue;
}

void MorseScheduler::tick(unsigned long currentTime)
{
	MorseSchedulerQueueElement element = queue->deq();
	if(element.time <= currentTime) //it is time to execute the scheduled function
	{
		void (*fp)(void*,void*) = element.fc;
		if(fp != 0)
		{
			fp(element.input,element.output);
		}
	}
	else //Reschedule the function element
	{
		queue->enq(element);
	}
}

//Remember the default values for the arguments to schedule()
void (*MorseScheduler::schedule(void(*c)(void*,void*), void * input, void * output, unsigned long time))(void*,void*)
{
	MorseSchedulerQueueElement element(c,input,output,time);
	MorseSchedulerQueueElement re = queue->enq(element);
	if(re == element) //then return the function pointer contained in re
	{
		return re.fc;
	}
	else //return 0, the scheduling has failed.
	{
		return 0;
	}
}
