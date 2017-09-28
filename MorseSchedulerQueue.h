/*
MorseSchedulerQueue class

An implementation of a Queue data structure that contains pointers to functions
of type void(*func)(void*). The queue is circular and it is not possible to overrun
the front of the queue, if that occurs the enq() calls will not modify the queue
until pointers are removed. This would be a great oppertunity for STL with 
MorseQueue, but the Arduino does not appear to support it.
*/

class MorseSchedulerQueue
{
private:
	void(**queue)(void*); //Pointer to the provided array to serve as the Queue.
	unsigned int queueSize; //The size of queue[].
	unsigned int front; //the front index in queue[].
	unsigned int rear; //the rear index in queue[].
	unsigned int numPointers; //the number of pointers currently stored in the Queue.

	/*
	Properly increment the specified index.

	If index == queueSize, it is reset back to 0.

	Arguments
	unsigned int index - The index value to increment

	Returns
	unsigned int - The new index value properly incremented.
	*/
	unsigned int incIndex(unsigned int index);

public:
	/*
	Constructor

	Initalize an empty queue with the provided array and size of the array.
	The constructor will not clear the contents of the array.

	Arguments
	void(*queue)(void*) - Pointer to the start of the array that will contain the queue.
	int size - The number of pointers that can be stored in *queue.

	Returns
	NA
	*/
	MorseSchedulerQueue(void(**queue)(void *), int size);

	/*
	Place a specified pointer at the end of the queue.

	Places a pointer at the current rear index.

	Arguments
	void(*c)(void*) - The pointer to insert into the queue.

	Returns
	void(*)(void*) - The pointer inserted into the queue. 0 if the insert failed.
	*/
	void (*enq(void(*c)(void*)))(void*);

	/*
	Remove and return the pointer at the front of the queue.
	
	Returns the current pointer currently at the front index.

	Arguments
	None

	Returns
	void(*)(void*) - The pointer present at the front of the queue, 0 if there are no
			more pointers to return.
	*/
	void (*deq())(void*); 

	/*
	Return the size of the queue in pointers.

	Returns the value of numPointers, since this variable is the true size of the queue.

	Arguments:
	None

	Returns
	unsigned int - The number of pointers in the queue.
	*/
	unsigned int size();
};
