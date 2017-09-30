/*
MorseScheduler class

A Scheduler Class that executes each function pointer from MorseSchedulerQueue in order
*/

#include "MorseSchedulerQueue.h"

class MorseScheduler
{
private:
	MorseSchedulerQueue * queue; //Pointer to the provided queue to schedule with.

public:
	/*
	Constructor

	Constructs a MorseScheduler object for a MorseSchedulerQueue. The constructor
	will not clear the contents of the queue.

	Arguments
	MorseSchedulerQueue * queue - Pointer ot the provided queue to schedule

	Returns
	NA
	*/
	MorseScheduler(MorseSchedulerQueue * queue);

	/*
	Execute the next function scheduled to execute.

	Only execute the next function scheduled to execute.

	Arguments:
	unsigned long currentTime - The current execution time, defaulted to 0.

	Returns:
	None
	*/
	void tick(unsigned long currentTime=0);

	/*
	Schedule the provided function to execute.

	Places the function pointer at the end of the queue to await execution.

	Arguments:
	void(**func)(void*,void*) - The function pointer to scheduler for execution
	void * input - The input for func, defaulted to 0
	void * output - The output from func, defaulted to 0
	unsigned long time - The time to schedule func to execute at, defaulted to 0

	Returns:
	void(**func)(void*,void*) - The function pointer scheduled or 0 if the queue is full.
	*/
	void (*schedule(void(*c)(void*,void*), void * input=0, void * output=0, unsigned long time=0))(void*,void*);
};
