/*
A test program to examine the MorseTreeRO class
*/
#include <memory.h>
#include "MorseStack.h"
#include "MorseTree.h"
#include "MorseTable.h"

#define STACKSIZE 5
/*
#define TREELENGTH 64
#define TABLESIZE 36
*/

/* Our Morse Code Tree encoded with the morse.cpp program */
char tree[]={00,0x74,0x65,0x6d,0x6e,0x61,0x69,0x6f,0x67,0x6b,0x64,0x77,0x72,0x75,0x73,00,00,0x71,0x7a,0x79,0x63,0x78,0x62,0x6a,0x70,00,0x6c,00,0x66,0x76,0x68,0x30,0x39,00,0x38,00,00,00,0x37,00,00,00,00,00,00,00,0x36,0x31,00,00,00,00,00,00,00,0x32,00,00,00,0x33,00,0x34,0x35,00};

/* Our Morse Code Tree lookup table encoded with the morse.cpp program */
char table[]={0x5,0x16,0x14,0xa,0x2,0x1c,0x8,0x1e,0x6,0x17,0x9,0x1a,0x3,0x4,0x7,0x18,0x11,0xc,0xe,0x1,0xd,0x1d,0xb,0x15,0x13,0x12,0x1f,0x2f,0x37,0x3b,0x3d,0x3e,0x2e,0x26,0x22,0x20};

int main()
{
	char stack[STACKSIZE]; //The stack used for encoding and decoding
	memset(stack,0,STACKSIZE);
	MorseStack morseStack(stack,STACKSIZE);
	/*char tree[TREELENGTH];	
	char table[TABLESIZE];*/
	
	MorseTable lookUp(table,sizeof(table));

	MorseTreeRO morseTree(tree,sizeof(tree),&lookUp);

	return 0;
}