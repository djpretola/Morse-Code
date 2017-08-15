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
	if((c >= 'a') && (c <= 'z'))
	{
		return c - 'a'; //The first 26 entries are for the characters.
	}
	else if((c >= '0') && (c <= '9'))
	{
		return c - '0' + 26; //Place the numbers in the last porition of the table.
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
