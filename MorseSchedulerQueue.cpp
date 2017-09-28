/*
MorseSchedulerQueue class

An implementation of a Queue data structure that contains pointers to functions
of type void(*fp)(void*). The queue is circular and it is not possible to overrun
the front of the queue, if that occurs the enq() calls will not modify the queue
until pointers are removed. This would be a great oppertunity for STL with 
MorseQueue, but the Arduino does not appear to support it.
*/

#include "MorseSchedulerQueue.h"

/* Our Constructor */
MorseSchedulerQueue::MorseSchedulerQueue(void(**queue)(void *), int size)
{
	this->queue = queue;
	this->queueSize = size;
	this->front = 0; //initalize both front, rear and numPointers to 0, we have an empty queue
	this->rear = 0;
	this->numPointers = 0; 
}

unsigned int MorseSchedulerQueue::incIndex(unsigned int index)
{
	if(index < queueSize - 1)
	{
		return ++index;	
	}
	else //go back to home! index 0.
	{
		return 0;
	}
}

//enq() accepts a function pointer of the form void(*fp)(void*) and returns that same type.
void (*MorseSchedulerQueue::enq(void(*c)(void*)))(void*)
{
	if(front != rear || numPointers == 0)
	{
		queue[front] = c;
		++numPointers;
		front = incIndex(front);
		return c;
	}
	else //return 0, the insert failed
	{
		return 0;
	}	
}

//deq() returns a function pointer of the form void(*fp)(void*)
void (*MorseSchedulerQueue::deq())(void*)
{
	if(rear != front || numPointers != 0)
	{
		void(*c)(void*) = queue[rear];
		--numPointers;
		rear = incIndex(rear);
		return c; 
	}
	else //the queue is empty
	{
		return 0;
	}
}

unsigned int MorseSchedulerQueue::size()
{
	return numPointers;
}
