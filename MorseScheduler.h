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
	None

	Returns:
	None
	*/
	void tick();

	/*
	Schedule the provided function to execute.

	Places the function pointer at the end of the queue to await execution.

	Arguments:
	void(**func)(void*) - The function pointer to scheduler for execution

	Returns:
	void(**func)(void*) - The function pointer scheduled or 0 if the queue is full.
	*/
	void (*schedule(void(*c)(void*)))(void*);
};
