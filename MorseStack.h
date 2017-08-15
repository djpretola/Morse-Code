/*
MorseStack class

An implementation of a Stack data structure that contains chars 
representing '.' and '-' for morse code.
*/

class MorseStack {
private:
	int stackSize; /* The size of the stack. */
	char * stack; /* Pointer to the provided array to serve as the stack. */
	int top; /* The index to the current top of the stack. */
public:
	/*
	Constructor 

	Initalize an empty stack with the provided array and size of the array.
	The constructor will not clear the contents of the array.

	Arguments
	char * stack - Pointer to the start of the array stack.
	int stackSize - The size of the *stack array.

	Returns
	NA
	*/
	MorseStack(char * stack, int stackSize);

	/*
	Push a single character into the stack.

	Places a character on the top of the stack.

	Arguments
	char c - The character to push.

	Returns
	none 
	*/	
	void push(char c);

	/*
	Pop the first character off the stack.

	Removes the character on the top of the stack.

	Arguments
	none

	Returns
	char - The character from the top.
	*/
	char pop();

	/*
	Print to STDIO the stack array characters and the current index of the top.

	Arguments
	none

	Returns
	none
	*/
	void debugPrintStack();
};
