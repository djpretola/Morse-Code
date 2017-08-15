/*
A Binary Search tree implementation of Morse Code to ASCII and ASCII to Morse Code
By David Pretola

Here we use an array to store the tree. Formulas for Transversing the tree:

[0] -> root node
[(i-1)/2] -> parent node
[2i+1] -> left child
[2i+2] -> right child
*/

#include <iostream>
#include <cstdio>
#include <memory.h>
#include "MorseStack.h"
#include "MorseTable.h"
#include "MorseTree.h"

/* Constructor */
MorseTree::MorseTree(char * bTree, int treeLength, MorseTable * lookupTable)
{
	this->bTree = bTree;
	this->treeLength = treeLength;
	this->lookupTable = lookupTable;
	
	//Insert the characters and their associated codes
	insert('a',".-");
	insert('b',"-...");
	insert('c',"-.-.");
	insert('d',"-..");
	insert('e',".");
	insert('f',"..-.");
	insert('g',"--.");
	insert('h',"....");
	insert('i',"..");
	insert('j',".---");
	insert('k',"-.-");
	insert('l',".-..");
	insert('m',"--");
	insert('n',"-.");
	insert('o',"---");
	insert('p',".--.");
	insert('q',"--.-");
	insert('r',".-.");
	insert('s',"...");
	insert('t',"-");
	insert('u',"..-");
	insert('v',"...-");
	insert('w',".--");
	insert('x',"-..-");
	insert('y',"-.--");
	insert('z',"--..");
	insert('1',".----");
	insert('2',"..---");
	insert('3',"...--");
	insert('4',"....-");
	insert('5',".....");
	insert('6',"-....");
	insert('7',"--...");
	insert('8',"---..");
	insert('9',"----.");
	insert('0',"-----");
}

/* insert the specified character, c, into MorseTree under the specified code */
void MorseTree::insert(const char c,const char * code)
{
	int index = 0; //the current node location in MorseTree[]
	while(*code != 0) {
		if(*code == '-') //then go left 
		{
			index = leftChild(index);
		}
		else if(*code == '.') //then go right
		{
			index = rightChild(index);
		}	
		else
		{
			std::cout << "Invalid character in Morse Code: " << *code << '\n';
			return; //abort the character insertion.
		}
		code++; //increment to the next character
	}
	//our current index is the location of the character in the tree
	bTree[index] = c;

	//Insert the current index and the character into the lookup table.
	lookupTable->put(c,index);
}

/* Calculate the parent index of the provided node index */
int MorseTree::parentOf(int index)
{
	if(index > 0)
	{
		return (index-1)/2;
	} else {
		return 0;
	}
}

/* Calculate the left child of the provided node index */
inline int MorseTree::leftChild(int index)
{
	return 2*index+1;
}

/* Calculate the right child of the provided node index */
inline int MorseTree::rightChild(int index)
{
	return 2*index+2;
}

/* Perform a Pre-Order transversal of the tree and print out the node character values */
void MorseTree::printTree() 
{
	int index = 0; //the current index in bTree.
	preOrderTransPrinter(index,0);
}

void MorseTree::preOrderTransPrinter(int i,int depth)
{
	if(i < treeLength) //make sure we don't overrun the bTree array.
	{
		printNodeWSpaces(i,depth);
		preOrderTransPrinter(leftChild(i),depth+1);
		preOrderTransPrinter(rightChild(i),depth+1);
	}
}

void MorseTree::printNodeWSpaces(int i,int depth)	
{
	//The number of spaces to print before the node value.
	int spaces = 4*depth; //print four times the nodes index in spaces before the value.
	while(spaces > 0)
	{
		std::cout << ' ';
		spaces--;
	}
	if(bTree[i] != 0)
	{
		std::cout << bTree[i] << '\n';
	}
	else
	{
		std::cout << "__" << '\n';
	}
}

/* Print the btree nodes in order as they appear in the array.*/
void MorseTree::printTreeArray()
{
	std::cout << '"';
	for(int i=0;i<treeLength;++i)
	{
		if(bTree[i] != 0)
		{
			std::cout << bTree[i];
		}
		else
		{
			std::cout << ' ';
		}
	}
	std::cout << "\"\n";
}

/* Perform a Pre-Order transversal of the tree to find the specified character and then
walk up the tree and return the morse code string for the specified character */
void MorseTree::Ascii2Morse(char c,MorseStack &  morse)
{
	std::cout << "Entering Ascii2Morse\n"; //DEBUG
	int index = findCharIndex(c);
	if(index != 0) //we have found the index! Walk back up and fill in the morse code str
	{
		fillInParentString(index,morse);
	}
	std::cout << "Leaving Ascii2Morse\n"; //DEBUG
}

/*Use the lookup table or hashmap to locate the array index of the specified char */
int MorseTree::findCharIndex(char c)
{
	int foundIndex; //the index located in the bTree array, 0 if c not found.
	foundIndex = lookupTable->get(c);
	if(foundIndex != -1)
	{
		return foundIndex;
	}
	else
	{
		return 0;
	}
}

/*Walk up the tree from the specified node index and fill in the string in reverse order. */
void MorseTree::fillInParentString(int i,MorseStack & morse)
{
	std::cout << "Entering fillINParentString\n"; //DEBUG
	while(i != 0) //else we have reached the root node and are done
	{
		int parentIndex = parentOf(i);
		if(i == leftChild(parentIndex)) //then place a '-' at the end of the string
		{
			morse.push('-');
		}
		else //otherwise it is a '.'
		{
			morse.push('.');
		}
		i = parentIndex; //move to the parent node.
	}
	std::cout << "Leaving fillInParentString\n"; //DEBUG
}

/* Print the btree nodes in order as they appear in the array in hex. */
void MorseTree::printTreeArrayHex()
{
	std::cout << "{ ";
	char delimiter = ','; //delimite each number by a comma.
	for(int i=0;i<treeLength;++i)
	{
		if(i == treeLength - 1) delimiter = ' '; //make sure the last value has no comma.
		std::printf("%#02x%c",bTree[i],delimiter); //it's a little easier in C.
	}
	std::cout << "};\n";
}
