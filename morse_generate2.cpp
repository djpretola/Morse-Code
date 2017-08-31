/*
Another test program to examine the generation of Morse Code from user entry. 
*/

#include <cstdio>
#include <cstring>
#include <memory.h>
#include <iostream> 
#include "MorseCode.h"

#define CHARACTERS 2000 

int main()
{
	/* The characters and numbers defined in Morse Code */
	unsigned char buffer1[CHARACTERS];
	unsigned char buffer2[CHARACTERS]; 
	MorseStack asciiStack(buffer1,CHARACTERS); //stack to store the entered ASCII chars.
	MorseStack morseStack(buffer2,CHARACTERS); //stack to store the Morse Code
	MorseCode morse;
	unsigned char c; //the current character under test.

	std::cout << "Enter a String to encode in Morse Code:\n" << "> ";
	do
	{
		c = std::getc(stdin);
		if(c >= 'A' && c <= 'Z') 
		{
			c += 32; //simple convert capital ASCII to lower ASCII
		}
		if(c == '\n')
		{
			continue; //we are done entering the ASCII.
		}
		else
		{
			asciiStack.push(c);
		}
	}while(c != '\n');

	//Do the actual conversion with MorseCode.
	morse.Ascii2Morse(asciiStack,morseStack);

	//Display the code in the stack.
	unsigned char dc; //The Morse Code character to display.
	do
	{
		dc = morseStack.pop();
		std::cout << dc;
	}while(dc != 0);
	std::cout << '\n';
	return 0;
}
