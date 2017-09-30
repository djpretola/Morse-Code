/*
MorseSchedulerQueue class

An implementation of a Queue data structure that contains MorseSchedulerQueueElements.
The queue is circular and it is not possible to overrun
the front of the queue, if that occurs the enq() calls will not modify the queue
until elements are removed. This would be a great oppertunity for STL with
MorseQueue, but the Arduino does not appear to support it.
*/

/*
The class to store in the MorseSchedulerQueue class. It stores the function pointer and
other variables required to run and schedule the specified function.
*/

class MorseSchedulerQueueElement
{
public:
	void(*fc)(void*,void*); //function pointer to the function scheduled.
	void * input; //void pointer to the input to *fc
	void * output; //void pointer to the output from *fc
	unsigned long time; //the time in milliseconds for when the scheduler is to call fc(arg)

	//The constructors
	MorseSchedulerQueueElement();
	MorseSchedulerQueueElement(void(*fc)(void*,void*),void * input, void * output, unsigned long time);

	//Comparison function
	bool operator!=(MorseSchedulerQueueElement compareElement);
};

class MorseSchedulerQueue
{
private:
	MorseSchedulerQueueElement * queue; //Pointer to the provided array to serve as the Queue.
	unsigned int queueSize; //The size of queue[].
	unsigned int front; //the front index in queue[].
	unsigned int rear; //the rear index in queue[].
	unsigned int numElements; //the number of elements currently stored in the Queue.

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
	MorseSchedulerQueueElement * queue - Pointer to the start of the array that will contain the queue.
	int size - The number of elements that can be stored in *queue.

	Returns
	NA
	*/
	MorseSchedulerQueue(MorseSchedulerQueueElement * queue, int size);

	/*
	Place a specified element at the end of the queue.

	Places a element at the current rear index.

	Arguments
	MorseSchedulerQueueElement c - The element to insert into the queue.

	Returns
	MorseSchedulerQueueElement - The element inserted into the queue. 0 if the insert failed.
	*/
	MorseSchedulerQueueElement enq(MorseSchedulerQueueElement c);

	/*
	Remove and return the element at the front of the queue.
	
	Returns the current element currently at the front index.

	Arguments
	None

	Returns
	MorseSchedulerQueueElement - The element present at the front of the queue, 0 if 
					there are no more elements to return.
	*/
	MorseSchedulerQueueElement deq();

	/*
	Return the size of the queue in MorseSchedulerQueueElements.

	Returns the value of numElements, since this variable is the true size of the queue.

	Arguments:
	None

	Returns
	unsigned int - The number of elements in the queue.
	*/
	unsigned int size();
};
