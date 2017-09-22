/*
MorseQueue class

An implementation of a Queue data structure that contains unsigned chars for
the representation of '.','-','l','w' for morse code. The queue is circular 
and it is not possible to overrun the front of the queue, if that occurs the 
enq() calls will not modify the queue until characters are removed.
*/

#include "MorseQueue.h"

/* Our Constructor */
MorseQueue::MorseQueue(unsigned char * queue, int size)
{
	this->queue = queue;
	this->queueSize = size;
	this->front = 0; //initalize both front, rear and numChars to 0, we have an empty queue
	this->rear = 0;
	this->numChars = 0; 
}

unsigned int MorseQueue::incIndex(unsigned int index)
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

unsigned char MorseQueue::enq(unsigned char c)
{
	if(front != rear || numChars == 0)
	{
		queue[front] = c;
		++numChars;
		front = incIndex(front);
		return c;
	}
	else //return 0, the insert failed
	{
		return 0;
	}	
}

unsigned char MorseQueue::deq()
{
	if(rear != front || numChars != 0)
	{
		unsigned char c = queue[rear];
		--numChars;
		rear = incIndex(rear);
		return c; 
	}
	else //the queue is empty
	{
		return 0;
	}
}

unsigned int MorseQueue::size()
{
	return numChars;
}
