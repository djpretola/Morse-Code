#ifndef _H_MORSESTACK
#define MORSESTACK
/*
MorseStack class

An implementation of a Stack data structure that contains chars 
representing '.' and '-' for morse code.
*/

#include <iostream>
#include <memory.h>
#include "MorseStack.h"

//Our MorseStack class

//Our Constructor
MorseStack::MorseStack(char * stack, int stackSize)
{
	this->stack = stack;
	this->stackSize = stackSize;
	top = 0; //set the top of the stack
}

void MorseStack::push(char c)
{
	if(top != stackSize) stack[top++]=c;

}

char MorseStack::pop()
{
	if(top != 0) 
	{
		return stack[--top];
	}
	else
	{
		return 0;
	}
}

void MorseStack::debugPrintStack()
{
	for(int i=0;i<stackSize;++i)
	{
		std::cout << stack[i];
	}
	std::cout << ' ' << top << '\n';
}
#endif
