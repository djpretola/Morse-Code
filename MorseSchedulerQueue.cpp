/*
MorseSchedulerQueue class

An implementation of a Queue data structure that contains MorseSchedulerQueueElements
The queue is circular and it is not possible to overrun
the front of the queue, if that occurs the enq() calls will not modify the queue
until elements are removed. This would be a great oppertunity for STL with
MorseQueue, but the Arduino does not appear to support it.
*/

#include "MorseSchedulerQueue.h"

/* Our Constructor */
MorseSchedulerQueue::MorseSchedulerQueue(MorseSchedulerQueueElement * queue, int size)
{
	this->queue = queue;
	this->queueSize = size;
	this->front = 0; //initalize both front, rear and numElements to 0, we have an empty queue
	this->rear = 0;
	this->numElements = 0;
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

MorseSchedulerQueueElement MorseSchedulerQueue::enq(MorseSchedulerQueueElement & c)
{
	if(front != rear || numElements == 0)
	{
		queue[front] = c;
		++numElements;
		front = incIndex(front);
		return c;
	}
	else //return 0, the insert failed
	{
		return MorseSchedulerQueueElement();
	}	
}

MorseSchedulerQueueElement MorseSchedulerQueue::deq()
{
	if(rear != front || numElements != 0)
	{
		MorseSchedulerQueueElement element = queue[rear];
		--numElements;
		rear = incIndex(rear);
		return element;
	}
	else //the queue is empty
	{
		return MorseSchedulerQueueElement();
	}
}

unsigned int MorseSchedulerQueue::size()
{
	return numElements;
}

//Functions for the MorseSchedulerQueueElement class

MorseSchedulerQueueElement::MorseSchedulerQueueElement()
{
	this->fc=0;
	this->input=0;
	this->output=0;
	this->time=0;
}

MorseSchedulerQueueElement::MorseSchedulerQueueElement(void(*fc)(void*,void*),void * input, void * output, unsigned long time)
{
	this->fc=fc;
	this->input=input;
	this->output=output;
	this->time=time;
}

bool MorseSchedulerQueueElement::operator==(MorseSchedulerQueueElement & compareElement)
{
	return this->fc == compareElement.fc &&
		 this->input == compareElement.input &&
		 this->output == compareElement.output &&
		 this->time == compareElement.time;
}
