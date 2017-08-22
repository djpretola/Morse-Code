#include <iostream>
#include <cstdio>
#include <memory.h>
#include "MorseTable.h"

//The Constructor

MorseTable::MorseTable(char * hashTable, int hashTableSize)
{
	this->hashTable = hashTable;
	this->hashTableSize = hashTableSize;
}

void MorseTable::put(char c, unsigned char value)
{
	int hash = computeHash(c);
	if(hash != -1) //insert the value at the position hash
	{
		hashTable[hash] = value;
	}
	else //display an error
	{
		std::cout << "Invalid character value: " << c << '\n';
	}
}

/*
Calculate the hashing for the specified character c.

The hashing function is as follows:
if(c >= 'a' && c <= 'z') then hash = c - 61
if(c >= 48 && c <= 57) then hash = c - 48 + 26

Arguments:
char c - The character to calculate the hash function for.

Returns:
int - The hash key 0 - 35, for the valid Morse Code characters. -1 for invalid characters.
*/

int MorseTable::computeHash(char c)
{
	if(((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')))
	{
		return c - 'a'; //The first 26 entries are for the characters.
	}
	else if((c >= '0') && (c <= '9'))
	{
		return c - '0' + 26; //Place the numbers in the last porition of the table.
	}
	else if((c >= 0x27) && (c <= '/'))
	{
		return c - 0x27 + 37; //Place ' ( ) * + , - . / after the numbers in the table.
	}
	else if((c >= END_OF_WORK) && (c <= UNDERSTOOD))
	{
		return c - END_OF_WORK + 46; //Place END_OF_WORK INV_TO_TRANS UNDERSTOOD
	}
	else if((c == ERROR) || (c == WAIT))
	{
		return c - ERROR + 49; //Place ERROR WAIT
	}
	else if(c == STARTING_SIGNAL)
	{
		return 51; //Place STARTING_SIGNAL
	}
	else if(c == '"')
	{
		return 52; //Place quotation
	}
	else if(c == ':')
	{
		return 53; //Place colon
	}
	else if(c == '=')
	{
		return 54; //Place double hyphon
	}
	else if(c == '?')
	{
		return 55; //Place question
	}
	else if(c == '@')
	{
		return 56; //Place commerical at "@"
	}
	else //we have an invalid character
	{
		return -1;
	}
}

unsigned char MorseTable::get(char c)
{
	int hash = computeHash(c);
	if(c != -1) //retreive the value
	{
		return hashTable[hash];
	}
	else //return -1 for error
	{
		return -1;
	}
}

/* Print the array nodes in order as they appear in the array in hex. */
void MorseTable::printTableArrayHex()
{
	std::cout << "{ ";
	char delimiter = ','; //delimite each number by a comma.
	for(int i=0;i<hashTableSize;++i)
	{
		if(i == hashTableSize - 1) delimiter = ' '; //make sure the last value has no comma.
		std::printf("%#02x%c",hashTable[i],delimiter); //it's a little easier in C.
	}
	std::cout << "};\n";
}
