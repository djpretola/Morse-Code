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

	//find the Morse Code for the letter q
	mt.Ascii2Morse('q',ms);
	std::cout << "About to print the code\n"; //DEBUG
	std::cout << "Morse Code for Q: ";

	//Display the code
	char c;
	do
	{
		c = ms.pop();
		std::cout << c;
	}while(c != 0);
	std::cout << '\n';
	std::cout << "Finnished printing the code\n"; //DEBUG

	return 0;
}
