#include <iostream>
#include <memory.h>
#include "MorseStack.h"
#include "MorseTree.h"
#include "MorseTable.h"

#define STACKSIZE 8
#define TREELENGTH 256
#define TABLESIZE 57

int main()
{
	char stack[STACKSIZE];
	char tree[TREELENGTH];	
	char table[TABLESIZE];

	// Clear the contents of the arrays
	memset(stack,0,STACKSIZE);
	memset(tree,0,TREELENGTH);
	memset(table,0,TABLESIZE);
	
	MorseStack ms((char*)stack,STACKSIZE);

	MorseTable mlookup((char*)table,TABLESIZE);

	MorseTree mt((char*)tree,TREELENGTH,&mlookup);

	
	//Insert the characters and their associated codes
	mt.insert('a',".-");
	mt.insert('b',"-...");
	mt.insert('c',"-.-.");
	mt.insert('d',"-..");
	mt.insert('e',".");
	mt.insert('f',"..-.");
	mt.insert('g',"--.");
	mt.insert('h',"....");
	mt.insert('i',"..");
	mt.insert('j',".---");
	mt.insert('k',"-.-");
	mt.insert('l',".-..");
	mt.insert('m',"--");
	mt.insert('n',"-.");
	mt.insert('o',"---");
	mt.insert('p',".--.");
	mt.insert('q',"--.-");
	mt.insert('r',".-.");
	mt.insert('s',"...");
	mt.insert('t',"-");
	mt.insert('u',"..-");
	mt.insert('v',"...-");
	mt.insert('w',".--");
	mt.insert('x',"-..-");
	mt.insert('y',"-.--");
	mt.insert('z',"--..");
	mt.insert('1',".----");
	mt.insert('2',"..---");
	mt.insert('3',"...--");
	mt.insert('4',"....-");
	mt.insert('5',".....");
	mt.insert('6',"-....");
	mt.insert('7',"--...");
	mt.insert('8',"---..");
	mt.insert('9',"----.");
	mt.insert('0',"-----");
	mt.insert(STARTING_SIGNAL,"-.-.-");
	mt.insert(END_OF_WORK,"...-.-");
	mt.insert(INV_TO_TRANS,"-.-"); //INV_TO_TRANS is identical to the character k.
	mt.insert(UNDERSTOOD,"...-.");
	mt.insert(ERROR,"........");
	mt.insert(WAIT,".-...");
	mt.insert(MULT,"-..-"); //MULT is identical to the character x.
	mt.insert('"',".-..-.");
	mt.insert(0x27,".----."); // ' Apostrophe character
	mt.insert('(',"-.--.");
	mt.insert(')',"-.--.-");
	mt.insert('+',".-.-.");
	mt.insert(',',"--..--");
	mt.insert('-',"-....-");
	mt.insert('.',".-.-.-");
	mt.insert('/',"-..-.");
	mt.insert(':',"---...");
	mt.insert('=',"-...-");
	mt.insert('?',"..--..");
	mt.insert('@',".--.-.");

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
