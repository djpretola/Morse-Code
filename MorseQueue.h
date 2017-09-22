/*
MorseQueue class

An implementation of a Queue data structure that contains unsigned chars for
the representation of '.','-','l','w' for morse code. The queue is circular 
and it is not possible to overrun the front of the queue, if that occurs the 
enq() calls will not modify the queue until characters are removed.
*/

class MorseQueue
{
private:
	unsigned char * queue; //Pointer to the provided array to serve as the Queue.
	unsigned int queueSize; //The size of queue[].
	unsigned int front; //the front index in queue[].
	unsigned int rear; //the rear index in queue[].
	unsigned int numChars; //the number of characters currently stored in the Queue.

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

	Initalize an empty stack with the provided array and size of the array.
	The constructor will not clear the contents of the array.

	Arguments
	unsigned char * queue - Pointer to the start of the array that will contain the queue.
	int size - The number of characters that can be stored in *queue.

	Returns
	NA
	*/
	MorseQueue(unsigned char * queue, int size);

	/*
	Place a specified character at the end of the queue.

	Places a character at the current rear index.

	Arguments
	unsigned char c - The character to insert into the queue.

	Returns
	unsigned char - The character inserted into the queue. 0 if the insert failed.
	*/
	unsigned char enq(unsigned char c);

	/*
	Remove and return the character at the front of the queue.
	
	Returns the current character currently at the front index.

	Arguments
	None

	Returns
	unsigned char - The character present at the front of the queue, 0 if there are no
			more characters to return.
	*/
	unsigned char deq();

	/*
	Return the size of the queue in characters.

	Returns the value of numChars, since this variable is the true size of the queue.

	Arguments:
	None

	Returns
	unsigned int - The number of characters in the queue.
	*/
	unsigned int size();
};
