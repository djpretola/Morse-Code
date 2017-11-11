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
/* An Abstraction Barrier that allows for the processing of Morse Code <-> ASCII. 
*/

#include "MorseCode.h"

/* Our Morse Code Tree encoded with the morse.cpp program, Morse Code <-> ASCII binary search tree */
unsigned char MorseCode::tree[]={00,0x65,0x74,0x69,0x61,0x6e,0x6d,0x73,0x75,0x72,0x77,0x64,0x6b,0x67,0x6f,0x68,0x76,0x66,00,0x6c,00,0x70,0x6a,0x62,0x78,0x63,0x79,0x7a,0x71,00,00,0x35,0x34,0x6,0x33,00,00,00,0x32,0x16,00,0x2b,00,00,00,00,0x31,0x36,0x3d,0x2f,00,00,0x2,0x28,00,0x37,00,00,00,0x38,00,0x39,0x30,00,00,00,00,00,0x4,00,00,00,00,00,00,0x3f,00,00,00,00,00,0x22,00,00,0x2e,00,00,00,00,0x40,00,00,00,0x27,00,00,0x2d,00,00,00,00,00,00,00,00,00,00,00,0x29,00,00,00,00,00,0x2c,00,00,00,00,0x3a,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,0x15};

/* Our Morse Code Tree lookup table encoded with the morse.cpp program, Hashmap to enable a quicker ASCII to Morse conversion */
unsigned char MorseCode::table[]={0x4,0x17,0x19,0xb,0x1,0x11,0xd,0xf,0x3,0x16,0xc,0x13,0x6,0x5,0xe,0x15,0x1c,0x9,0x7,0x2,0x8,0x10,0xa,0x18,0x1a,0x1b,0x3e,0x2e,0x26,0x22,0x20,0x1f,0x2f,0x37,0x3b,0x3d,0x5d,0x35,0x6c,00,0x29,0x72,0x60,0x54,0x31,0x44,00,0x21,0xff,0x27,0x34,0x51,0x77,0x30,0x4b,0x59};

MorseCode::MorseCode() : morseTable(table,TABLESIZE), morseTree(tree,TREELENGTH,&morseTable)
{
}

void MorseCode::Ascii2Morse(MorseStack & ascii,MorseStack & coded)
{
	unsigned char character;
	do
	{
		character = ascii.pop();
		if(character != 0)
		{
			if(character == ' ') //then push a word indicator
			{
				coded.pop(); //remove the last letter indicator
				coded.push('w');
			}
			else
			{
				morseTree.Ascii2Morse(character,coded);
				coded.push('l');	
			}
		}
	}while(character != 0);
	coded.pop(); //remove the last space character.
}

void MorseCode::Morse2Ascii(MorseStack & coded,MorseStack & ascii)
{
	unsigned char local[STACKSIZE];
	MorseStack currentCode(local,STACKSIZE); //temporary local stack to hold a Morse char.
	unsigned char code; //The current Morse Code character
	unsigned char character; //The decoded Morse Character
	do
	{
		do
		{
			code = coded.pop();
			if(code != 'l' && code != 'w' && code != 0) 
			{
				currentCode.push(code);
			}
		}while(code != 'l' && code != 'w' && code != 0);
		
		character = morseTree.Morse2Ascii(currentCode);
		if(character != 0)
		{
			ascii.push(character);
			if(code == 'w') //then make sure to add a space
			{
				ascii.push(' ');
			}
		}
	}while(code != 0);
}
