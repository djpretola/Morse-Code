#include <iostream>
#include <memory.h>
#include "MorseStack.h"
#include "MorseTree.h"

#define STACKSIZE 5
#define TREELENGTH 64

int main()
{
	char stack[STACKSIZE];
	char tree[TREELENGTH];	
	
	MorseStack ms((char*)stack,STACKSIZE);

	MorseTree mt((char*)tree,TREELENGTH);

	//Print the tree structure
	mt.printTree();
	mt.printTreeArray();
	mt.printTreeArrayHex();

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
