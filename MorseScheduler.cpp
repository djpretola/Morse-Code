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
