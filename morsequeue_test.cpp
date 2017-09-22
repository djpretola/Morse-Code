/*
A test program for the MorseQueue class. We will test enqueue and dequeue of Morse Code
characters.
*/

#include <iostream>
#include <cstdio>
#include "MorseQueue.h"

int main()
{
	bool testFailed = false;
	unsigned char testBuffer[] = {'w','w','w','w','w','w','w','w'};
	unsigned char testBufferSize = 8;

	MorseQueue testQueue(testBuffer,testBufferSize); //constructor test

	unsigned char retC;

	//Test 1 Deq() from an empty queue
	retC = testQueue.deq();
	if(retC != 0) //we should not be able to get anything from an empty queue
	{	
		std::cout << "Test 1 Empty MorseQueue returned: ";
		std::printf("%x\n",retC);
		testFailed = true;
		return 0;
	}

	//Test 2 Enq() into an empty queue
	retC = testQueue.enq('.');
	if(retC != '.') //we should get the enqueued character back
	{
		std::cout << "Test 2 Empty MorseQueue enq() returned: ";
		std::printf("%x\n",retC);
		testFailed = true;
		return 0;
	}

	//Test 3 Deq() from a queue
	retC = testQueue.deq();
	if(retC != '.') //we should get the '.' back
	{
		std::cout << "Test 3 Deq() from a queue with '.' returned: ";
		std::printf("%x\n",retC);
		testFailed = true;
		return 0;
	}

	//Test 4
	//enq() a few values	
	testQueue.enq('-');
	testQueue.enq('.');
	testQueue.enq('l');
	testQueue.enq('w');
	
	//Now deq() the values
	unsigned char retCA[4];
	retCA[0] = testQueue.deq();
	retCA[1] = testQueue.deq();
	retCA[2] = testQueue.deq();
	retCA[3] = testQueue.deq();
	if(retCA[0] != '-' || retCA[1] != '.' || retCA[2] != 'l' || retCA[3] != 'w') //deq() failure
	{
		std::cout << "Test 4 Deq() with multiple values failed!\n";
		std::cout << "retCA[0] = " << retCA[0] << '\n';
		std::cout << "retCA[1] = " << retCA[1] << '\n';
		std::cout << "retCA[2] = " << retCA[2] << '\n';
		std::cout << "retCA[3] = " << retCA[3] << '\n';
		testFailed = true;
		return 0;
	}

	//Test 5 
	testQueue.enq('a');
	testQueue.enq('b');
	testQueue.enq('c');
	testQueue.enq('d');
	testQueue.enq('e');
	testQueue.enq('f');
	testQueue.enq('g');
	testQueue.enq('h');
	retC = testQueue.enq('i'); //This should fail
	if(retC == 'i' || retC != 0) //we overflowed the test queue
	{
		std::cout << "Test 5 Enq() with more then the queue size failed!\n";
		testFailed = true;
		return 0;
	}

	//Test 6
	unsigned char retCB[9];
	retCB[0] = testQueue.deq();
	retCB[1] = testQueue.deq();
	retCB[2] = testQueue.deq();
	retCB[3] = testQueue.deq();
	retCB[4] = testQueue.deq();
	retCB[5] = testQueue.deq();
	retCB[6] = testQueue.deq();
	retCB[7] = testQueue.deq();
	retCB[8] = testQueue.deq(); //This should fail
	if(retCB[0] != 'a' || retCB[1] != 'b' || retCB[2] != 'c' || retCB[3] != 'd' || retCB[4] != 'e' || retCB[5] != 'f' || retCB[6] != 'g' || retCB[7] != 'h' || retCB[8] != 0)
	{
		std::cout << "Test 6 failed Deq() with more then the queue size failed!\n";
		std::cout << "retCB[0] = " << retCB[0] << '\n';
		std::cout << "retCB[1] = " << retCB[1] << '\n';
		std::cout << "retCB[2] = " << retCB[2] << '\n';
		std::cout << "retCB[3] = " << retCB[3] << '\n';
		std::cout << "retCB[4] = " << retCB[4] << '\n';
		std::cout << "retCB[5] = " << retCB[5] << '\n';
		std::cout << "retCB[6] = " << retCB[6] << '\n';
		std::cout << "retCB[7] = " << retCB[7] << '\n';
		std::cout << "retCB[8] = " << retCB[8] << '\n';
		std::cout << "retCB[9] = " << retCB[9] << '\n';
		testFailed = true;
		return 0;
	}

	//TEST COMPLETE
	if(!testFailed)
	{
		std::cout << "All MorseQueue tests passed!\n";
	}
	return 0;
}
