#ifndef _H_MORSESTACK
#define _H_MORSESTACK

/* Define a default stack size */
#define STACKSIZE 8

/*
MorseStack class

An implementation of a Stack data structure that contains unsigned chars 
representing '.' and '-' for morse code.
*/

class MorseStack {
private:
	int stackSize; /* The size of the stack. */
	unsigned char * stack; /* Pointer to the provided array to serve as the stack. */
	int top; /* The index to the current top of the stack. */
public:
	/*
	Constructor 

	Initalize an empty stack with the provided array and size of the array.
	The constructor will not clear the contents of the array.

	Arguments
	unsigned char * stack - Pointer to the start of the array stack.
	int stackSize - The size of the *stack array.
	int top - The initial location of the stack top in the stack array. Default to 0.

	Returns
	NA
	*/
	MorseStack(unsigned char * stack, int stackSize, int top = 0);

	/*
	Push a single character into the stack.

	Places a character on the top of the stack.

	Arguments
	unsigned char c - The character to push.

	Returns
	The unsigned char argument if the character was pushed onto the stack, 0 if
	the stack is full.
	*/	
	unsigned char push(unsigned char c);

	/*
	Pop the first character off the stack.

	Removes the character on the top of the stack.

	Arguments
	none

	Returns
	unsigned char - The character from the top.
	*/
	unsigned char pop();

	/*
	Print to STDIO the stack array characters and the current index of the top.

	Arguments
	none

	Returns
	none
	*/
	void debugPrintStack();

	/*
	Reverse the contents of the stack from the bottom to the top.

	Arguments
	none

	Returns
	none
	*/
	void reverse();
};
#endif
