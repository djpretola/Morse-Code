/*
Another test program to test ASCII <-> Morse Code using the MorseCode class
*/

#include <iostream> 
#include "MorseCode.h"
#include <string> 

int main()
{
/* Quote from the "The OPERATIONAL CHARACTERISTICS of the PROCESSORS for the Burroughs B 5000", 5000-21005 Revision A, page 3-2 This will serve as our test string for processing. */
	unsigned char quote[]="stacks are an efficient form of automatic temporary storage. a stack is essentially a list of ordered items of information. in the b 5000, it is a list of operands and control information stored sequentially in the order of processing. the physical stack is composed of the a and b registers and the memory area addressed by the s register. a new world coming into the stack pushes down the information previously held in the registers. the information contained in the registers is the last information entered into the stack, the stack operates on a list in, first out principle. as operands are fetched by a program, they are placed in the a register. if the a register already contained a word, that word is transferred to the b register prior to loading the operand into the a register. if the b register is also occupied by information, then the s register is automatically increased by one, and the word in the b register is stored in a cell addressed by the s register. then the word in the a register can be transferred to the b register and the operand brought into the a register, see figure 3-2. as information is operated on in the stack, operands are eliminated from the stack and results of operations are returned to the stack. the need for information contained in the stack may require an automatic \"push-up\" to occur. this operation causes a word to be brought to the a or b register form the memory area addressed by the s register. the s register is then counted down by one. the flip-flops associated with the a and b registers are used to eliminate unnecessary stack operations. when an operand is to be placed in the stack, and either of the registers is empty, no push-down into memory occurs. no push-up is executed either, when an operation leaves one or both of the registers empty. note that the use of the stack, combined with the internal logic of the processor, eliminates the need for programming the storage or recall of intermediate results. in the case of multiprocessing, each program has its own stack. when an interrupt occurs, all required registers and control flip-flops are automatically pushed into the appropriate stack and the last s register setting is stored in a fixed location. to return to a program, this location is programatically fetched by the operating system and the s register is reset from the contents of the word. the other registers are then automatically reset and control continues in sequence.";

	//Determine the length of quote[] via basic_string
	std::basic_string<unsigned char> quoteString=quote;
	unsigned int quoteSize = quoteString.length();
	unsigned char buffer1[quoteSize*4];//increase the size of the buffer for the Morse Code
	unsigned char buffer2[quoteSize]; //buffer to decode the Morse Code into to compare with quote.
	unsigned char buffer3[quoteSize*4]; //a debug buffer

	MorseStack quoteStack(quote,quoteSize,quoteSize); //stack to store the ASCII quote above.
	MorseStack morseStack(buffer1,quoteSize*4);//stack to store the Morse Code
	MorseStack asciiStack(buffer2,quoteSize); //stack to store the final conversion into.
	MorseStack reverseStack(buffer3,quoteSize*4); //a debug buffer for stack reversal.

	MorseCode morse;

	//Do the conversion with MorseCode.
	morse.Ascii2Morse(quoteStack,morseStack);
	
	//Reverse the stack
	unsigned char c;
	do
	{
		c = morseStack.pop();
		if(c != 0) reverseStack.push(c);
	}while(c != 0);
	
	//Now convert the Morse Code back to ASCII
	morse.Morse2Ascii(reverseStack,asciiStack);

	//Print the ASCII stack and compare with the origional quote[] above
	unsigned char d;
	unsigned int i=0;
	bool diff = false;
	do
	{
		d = asciiStack.pop();
		if(quote[i] != d && !diff)
		{
			diff = true;
			std::cout << "\n****\nMismatch at quote[" << i << "]\n****\n";
			break; //leave the while loop!
		}
		++i; //increment into quote[]
		std::cout << d;
	}while(d != 0);

	//Display the final diff string
	if(diff)
	{
		std::cout << "\n\nThe conversion of quote[] failed!\n";
	}
	else
	{
		std::cout << "\n\nThe conversion of quote[] was succesfull.\n";
	}
	return 0;
}
