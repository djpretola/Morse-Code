#include <iostream>
#include <memory.h>
#include "MorseStack.h"
#include "MorseTree.h"
#include "MorseTable.h"

#define STACKSIZE 5
#define TREELENGTH 64
#define TABLESIZE 36

int main()
{
	char stack[STACKSIZE];
	char tree[TREELENGTH];	
	char table[TABLESIZE];
	
	MorseStack ms((char*)stack,STACKSIZE);

	MorseTable mlookup((char*)table,TABLESIZE);

	MorseTree mt((char*)tree,TREELENGTH,&mlookup);

	//Print the tree structure
	mt.printTree();
	mt.printTreeArray();
	mt.printTreeArrayHex();

	//Print the hash table
	mlookup.printTableArrayHex();

	//find the Morse Code for the letter q
	mt.Ascii2Morse('q',ms);

	//Display the code for the letter q.
	std::cout << "Morse Code for Q: ";
	char c;
	do
	{
		c = ms.pop();
		std::cout << c;
	}while(c != 0);
	std::cout << '\n';

	return 0;
}
