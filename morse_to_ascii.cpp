/*
Another test program to examine the generation of ASCII from user entered Morse Code.
*/

#include <cstdio>
#include <cstring>
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

	std::cout << "Enter a Morse Code to encode in ASCII:\n" << "> ";
	do
	{
		c = std::getc(stdin);
		if(c == '\n')
		{
			continue; //we are done entering the ASCII.
		}
		else if(c == '.' || c == '-' || c == 'w' || c == 'l') //valid Morse Code?
		{
			morseStack.push(c);
		}
	}while(c != '\n');

	//Do the actual conversion with MorseCode.
	morse.Morse2Ascii(morseStack,asciiStack);

	//Display the text in the stack.
	unsigned char dc; //The ASCII character to display.
	do
	{
		dc = asciiStack.pop();
		std::cout << dc;
	}while(dc != 0);
	std::cout << '\n';
	return 0;
}
