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
#ifndef _H_ARDUINO
#include <iostream>
#include <cstdio>
#include <memory.h>
#endif
#include "MorseTable.h"

//The Constructor

MorseTable::MorseTable(unsigned char * hashTable, int hashTableSize)
{
	this->hashTable = hashTable;
	this->hashTableSize = hashTableSize;
}

void MorseTable::put(unsigned char c, unsigned char value)
{
	int hash = computeHash(c);
	if(hash != MORSETABLE_INVALID_HASH) //insert the value at the position hash
	{
		hashTable[hash] = value;
	}
	else //display an error
	{
#ifndef _H_ARDUINO
		std::cout << "Invalid character value: " << c << '\n';
#endif
	}
}

/*
Calculate the hashing for the specified character c.

The hashing function is as follows:
if(c >= 'a' && c <= 'z') then hash = c - 61
if(c >= 48 && c <= 57) then hash = c - 48 + 26

Arguments:
unsigned char c - The character to calculate the hash function for.

Returns:
int - The hash key 0 - 35, for the valid Morse Code characters. MORSETABLE_INVALID_HASH for invalid characters.
*/

int MorseTable::computeHash(unsigned char c)
{
	if(((c >= 'a') && (c <= 'z')))
	{
		return c - 'a'; //The first 26 entries are for the characters.
	}
	else if((c >= '0') && (c <= '9'))
	{
		return c - '0' + 26; //Place the numbers in the last porition of the table.
	}
	else if((c >= 0x27) && (c <= '/'))
	{
		return c - 0x27 + 36; //Place ' ( ) * + , - . / after the numbers in the table.
	}
	else if((c >= END_OF_WORK) && (c <= UNDERSTOOD))
	{
		return c - END_OF_WORK + 45; //Place END_OF_WORK INV_TO_TRANS UNDERSTOOD
	}
	else if((c == ERROR) || (c == WAIT))
	{
		return c - ERROR + 48; //Place ERROR WAIT
	}
	else if(c == STARTING_SIGNAL)
	{
		return 50; //Place STARTING_SIGNAL
	}
	else if(c == '"')
	{
		return 51; //Place quotation
	}
	else if(c == ':')
	{
		return 52; //Place colon
	}
	else if(c == '=')
	{
		return 53; //Place double hyphon
	}
	else if(c == '?')
	{
		return 54; //Place question
	}
	else if(c == '@')
	{
		return 55; //Place commerical at "@"
	}
	else //we have an invalid character
	{
		return MORSETABLE_INVALID_HASH;
	}
}

unsigned char MorseTable::get(unsigned char c)
{
	int hash = computeHash(c);
	if(hash != MORSETABLE_INVALID_HASH) //retreive the value
	{
		return hashTable[hash];
	}
	else //return MORSETABLE_INVALID_HASH for error
	{
		return MORSETABLE_INVALID_HASH;
	}
}

/* Print the array nodes in order as they appear in the array in hex. */
void MorseTable::printTableArrayHex()
{
#ifndef _H_ARDUINO
	std::cout << "{ ";
	unsigned char delimiter = ','; //delimite each number by a comma.
	for(int i=0;i<hashTableSize;++i)
	{
		if(i == hashTableSize - 1) delimiter = ' '; //make sure the last value has no comma.
		std::printf("%#02x%c",hashTable[i],delimiter); //it's a little easier in C.
	}
	std::cout << "};\n";
#endif
}
