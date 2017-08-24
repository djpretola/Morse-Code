#ifndef _H_MORSETABLE
#define _H_MORSETABLE

/* Define our default table size */
#define TABLESIZE 56

/* Define our non-printable ASCII characters and Multiplication for Int Morse Code */
#define STARTING_SIGNAL 0x02
#define END_OF_WORK 0x04
#define INV_TO_TRANS 'k'
#define UNDERSTOOD 0x06
#define ERROR 0x15
#define WAIT 0x16
#define MULT 'x'

/* Define our error codes */
#define MORSETABLE_INVALID_HASH 58 //We picked a value outside of the valid hash index range

/*
A Hash table to aide in the look up of characters for Morse Code encoding.
Each key will be a valid Morse Code character.
Each value will be an integer. This integer can be used as the value for the specific
MorseTree node to begin the encoding from.

Hash Function:
The hash function will convert the ASCII code for the letters and numbers into the 
indexes for an array, where the values will be stored.

*/
class MorseTable {
private:
	unsigned char * hashTable; // an array to contain the Hash Table.
	int hashTableSize; // the size of the hastTable array.

	/*
	Calculate the hashing for the specified character c.
	
	The hashing function is as follows:
	if(c >= 'a' && c <= 'z') then hash = c - 61
	if(c >= 48 && c <= 57) then hash = c - 48 + 26

	Arguments:
	unsigned char c - The character to calculate the hash function for.

	Returns:
	int - The hash key 0 - 35, for the valid Morse Code characters.
	*/

	int computeHash(unsigned char c);

public:

	/*
	Constructor

	The constructor function for the MorseTable. The contents of the hashTable
	array is not cleared.

	Arguments:
	unsigned char * hashTable - Pointer to the array to store the table in.
	int hashTableSize - The size of the hashTable array.

	Returns:
	NA
	*/

	MorseTable(unsigned char * hashTable, int hashTableSize);

	/*
	Insert the specified character with the specified value into the hash table.

	Arguments:
	unsigned char c - The character to insert
	unsigned char value - The value to store under the character in the hash table.
	*/

	virtual void put(unsigned char c,unsigned char value);

	/*
	Retrieve the value from the hash table for the specified character.
	
	Arguments:
	unsigned char c - The character to look up.

	Returns:
	unsigned char - The value stored in the hash table under the specified character.
			 MORSETABLE_INVALID_HASH will be returned if the unsigned char*acter is invalid.
	*/
	unsigned char get(unsigned char c);

	
	/*
	Print to STDIO the character hash table array in Hexadecimal.

	Arguments:
	none

	Returns:
	none
	*/
	void printTableArrayHex();
};
#endif
