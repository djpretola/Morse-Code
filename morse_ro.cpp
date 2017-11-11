/*
Copyright (C) 2017 David Pretola

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3 as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/*
A test program to examine the MorseTreeRO class
*/
#include <cstdio>
#include <memory.h>
#include <iostream> 
#include "MorseStack.h"
#include "MorseTree.h"
#include "MorseTable.h"

#define CHARACTERS 56

/* Our Morse Code Tree encoded with the morse.cpp program */
unsigned char tree[]={00,0x65,0x74,0x69,0x61,0x6e,0x6d,0x73,0x75,0x72,0x77,0x64,0x6b,0x67,0x6f,0x68,0x76,0x66,00,0x6c,00,0x70,0x6a,0x62,0x78,0x63,0x79,0x7a,0x71,00,00,0x35,0x34,0x6,0x33,00,00,00,0x32,0x16,00,0x2b,00,00,00,00,0x31,0x36,0x3d,0x2f,00,00,0x2,0x28,00,0x37,00,00,00,0x38,00,0x39,0x30,00,00,00,00,00,0x4,00,00,00,00,00,00,0x3f,00,00,00,00,00,0x22,00,00,0x2e,00,00,00,00,0x40,00,00,00,0x27,00,00,0x2d,00,00,00,00,00,00,00,00,00,00,00,0x29,00,00,00,00,00,0x2c,00,00,00,00,0x3a,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,0x15};

/* Our Morse Code Tree lookup table encoded with the morse.cpp program */
unsigned char table[]={0x4,0x17,0x19,0xb,0x1,0x11,0xd,0xf,0x3,0x16,0xc,0x13,0x6,0x5,0xe,0x15,0x1c,0x9,0x7,0x2,0x8,0x10,0xa,0x18,0x1a,0x1b,0x3e,0x2e,0x26,0x22,0x20,0x1f,0x2f,0x37,0x3b,0x3d,0x5d,0x35,0x6c,00,0x29,0x72,0x60,0x54,0x31,0x44,00,0x21,0xff,0x27,0x34,0x51,0x77,0x30,0x4b,0x59};

/* The characters and numbers defined in Morse Code */
unsigned char morseCharacters[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','1','2','3','4','5','6','7','8','9','0', STARTING_SIGNAL, END_OF_WORK, INV_TO_TRANS, UNDERSTOOD, ERROR, WAIT, MULT, '"', 0x27, '(', ')', '+', ',', '-', '.', '/', ':', '=', '?', '@'};

int main()
{
	unsigned char stack[STACKSIZE]; //The stack used for encoding and decoding
	memset(stack,0,STACKSIZE);
	MorseStack morseStack(stack,STACKSIZE);
	MorseTable lookUp(table,TABLESIZE);
	MorseTreeRO morseTree(tree,TREELENGTH,&lookUp);

	unsigned char c; //the current character under test.
	unsigned char xc; //the character produced after the lookup
	bool error = false; //have any errors been detected!
	for(int i=0;i<CHARACTERS;++i)
	{
		c = morseCharacters[i];
		morseTree.Ascii2Morse(c,morseStack);
		xc = morseTree.Morse2Ascii(morseStack);
		if(c != xc) //then the test has failed!
		{
			std::printf("Character: %#02x Error! %#02x decoded! index: %d\n",c,xc,i);
			error = true;
		}
	}
	if(!error) std::cout << "All Morse Code characters where properly encoded and decoded!\n";
	return 0;
}
