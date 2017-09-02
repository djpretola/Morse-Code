#ifndef _H_MORSESTACK
#define MORSESTACK
/*
MorseStack class

An implementation of a Stack data structure that contains chars 
representing '.' and '-' for morse code. And 'l' and 'w' for letter
and word timing.
*/
#ifndef _H_ARDUINO
#include <iostream>
#endif
#include "MorseStack.h"

//Our MorseStack class

//Our Constructor
MorseStack::MorseStack(unsigned char * stack, int stackSize,int top)
{
	this->stack = stack;
	this->stackSize = stackSize;
	this->top = top; //note the default value.
}

void MorseStack::push(unsigned char c)
{
	if(top != stackSize) stack[top++]=c;

}

unsigned char MorseStack::pop()
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
#ifndef _H_ARDUINO
	for(int i=0;i<stackSize;++i)
	{
		std::cout << stack[i];
	}
	std::cout << ' ' << top << '\n';
#endif
}

void MorseStack::reverse()
{
	//Swap the contents of the stack around.
	unsigned char c; //current character being swapped.
	for(int i=0,j=top-1; i < top/2 && j > top/2 ;++i,--j)
	{
		c = stack[i];
		stack[i] = stack[j];
		stack[j] = c;
	}
}
#endif
