/*
A test program to examine the generation of Morse Code from user entry. 
*/
#include <cstring>
#include <memory.h>
#include <iostream> 
#include "MorseStack.h"
#include "MorseTree.h"
#include "MorseTable.h"

#define CHARACTERS 768

/* Our Morse Code Tree encoded with the morse.cpp program */
unsigned char tree[]={00,0x65,0x74,0x69,0x61,0x6e,0x6d,0x73,0x75,0x72,0x77,0x64,0x6b,0x67,0x6f,0x68,0x76,0x66,00,0x6c,00,0x70,0x6a,0x62,0x78,0x63,0x79,0x7a,0x71,00,00,0x35,0x34,0x6,0x33,00,00,00,0x32,0x16,00,0x2b,00,00,00,00,0x31,0x36,0x3d,0x2f,00,00,0x2,0x28,00,0x37,00,00,00,0x38,00,0x39,0x30,00,00,00,00,00,0x4,00,00,00,00,00,00,0x3f,00,00,00,00,00,0x22,00,00,0x2e,00,00,00,00,0x40,00,00,00,0x27,00,00,0x2d,00,00,00,00,00,00,00,00,00,00,00,0x29,00,00,00,00,00,0x2c,00,00,00,00,0x3a,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,0x15};

/* Our Morse Code Tree lookup table encoded with the morse.cpp program */
unsigned char table[]={0x4,0x17,0x19,0xb,0x1,0x11,0xd,0xf,0x3,0x16,0xc,0x13,0x6,0x5,0xe,0x15,0x1c,0x9,0x7,0x2,0x8,0x10,0xa,0x18,0x1a,0x1b,0x3e,0x2e,0x26,0x22,0x20,0x1f,0x2f,0x37,0x3b,0x3d,0x5d,0x35,0x6c,00,0x29,0x72,0x60,0x54,0x31,0x44,00,0x21,0xff,0x27,0x34,0x51,0x77,0x30,0x4b,0x59};

int main()
{
	/* The characters and numbers defined in Morse Code */
	char Characters[CHARACTERS];
	unsigned char stack[STACKSIZE]; //The stack used for encoding and decoding
	memset(stack,0,STACKSIZE);
	MorseStack morseStack(stack,STACKSIZE);
	MorseTable lookUp(table,TABLESIZE);
	MorseTreeRO morseTree(tree,TREELENGTH,&lookUp);
do
{
	std::cout << "Enter a String to encode in Morse Code:\n" << "> ";
	std::cin.getline(Characters,CHARACTERS);
	unsigned char c; //the current character under test.
	unsigned char dc; //the morse code character from the stack to display.
	for(int i=0;Characters[i] != 0;++i)
	{
		c = Characters[i];
		if(c >= 'A' && c <= 'Z') 
		{
			c += 32; //simple convert capital ASCII to lower ASCII
		}
		if(c == ' ')
		{
			std::cout << "w "; //just display a 'w' for word end
		}
		else
		{
		morseTree.Ascii2Morse(c,morseStack);
	
		//Display the code in the stack.
		do
		{
			dc = morseStack.pop();
			std::cout << dc;
		}while(dc != 0);
		std::cout << ' ';
		}
	}
	std::cout << '\n';
}while(std::strcmp(Characters,"q") != 0);
	return 0;
}
