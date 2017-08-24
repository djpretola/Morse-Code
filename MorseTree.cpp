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
MorseTree::MorseTree(unsigned char * bTree, int treeLength, MorseTable * lookupTable)
{
	this->bTree = bTree;
	this->treeLength = treeLength;
	this->lookupTable = lookupTable;
}

/* insert the specified character, c, into MorseTree under the specified code */
void MorseTree::insert(unsigned char c,const char * code)
{
	int index = 0; //the current node location in MorseTree[]
	while(*code != 0) {
		if(*code == '.') //then go left 
		{
			index = leftChild(index);
		}
		else if(*code == '-') //then go right
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
		std::printf("%#02x\n",bTree[i]); //it's a little easier in C.
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

/* Perform a look up on the specified character's tree node and then
walk up the tree and return the morse code string for the specified character */
void MorseTree::Ascii2Morse(unsigned char c,MorseStack &  morse)
{
	int index = findCharIndex(c);
	if(index != MORSETREE_INVALID_INDEX) //we have found the index! Walk back up and fill in the morse code str
	{
		fillInParentString(index,morse);
	}
}

/*Use the lookup table or hashmap to locate the array index of the specified char */
int MorseTree::findCharIndex(unsigned char c)
{
	int foundIndex; //the index located in the bTree array, 0 if c not found.
	foundIndex = lookupTable->get(c);
	if(foundIndex != MORSETREE_INVALID_INDEX)
	{
		return foundIndex;
	}
	else
	{
		return MORSETREE_INVALID_INDEX;
	}
}

/*Walk up the tree from the specified node index and fill in the string in reverse order. */
void MorseTree::fillInParentString(int i,MorseStack & morse)
{
	while(i != 0) //else we have reached the root node and are done
	{
		int parentIndex = parentOf(i);
		if(i == leftChild(parentIndex)) //then place a '.' at the end of the string
		{
			morse.push('.');
		}
		else //otherwise it is a '-'
		{
			morse.push('-');
		}
		i = parentIndex; //move to the parent node.
	}
}


/* Walk down the tree from the root node with the specified Morse Code String and return the 
character located */
unsigned char MorseTree::Morse2Ascii(MorseStack &  morse)
{
	int index = 0; //the current node location in MorseTree[]
	unsigned char direction; //the current direction to take from the current node.
	do
	{
		direction = morse.pop();
		if(direction == '.') //then go left 
		{
			index = leftChild(index);
		}
		else if(direction == '-') //then go right
		{
			index = rightChild(index);
		}	
		else if(direction != 0) //then error
		{
			std::cout << "Invalid character in Morse Code: " << direction << '\n';
			return 0; //abort the character insertion.
		}
	}while(direction != 0); 
	
	return bTree[index];
}

/* Print the btree nodes in order as they appear in the array in hex. */
void MorseTree::printTreeArrayHex()
{
	std::cout << "{ ";
	unsigned char delimiter = ','; //delimite each number by a comma.
	for(int i=0;i<treeLength;++i)
	{
		if(i == treeLength - 1) delimiter = ' '; //make sure the last value has no comma.
		std::printf("%#02x%c",bTree[i],delimiter); //it's a little easier in C.
	}
	std::cout << "};\n";
}

/**
The Read Only MorseTreeRO functions
**/

/* Our Constructor that passes through to the MorseTree constructor */
MorseTreeRO::MorseTreeRO(unsigned char * bTree, int treeLength, MorseTable * lookupTable) : MorseTree(bTree,treeLength,lookupTable)
{} 

/* Implement the insert function that is now private */
void MorseTreeRO::insert(unsigned char c,const char * code)
{}
