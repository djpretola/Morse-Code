/*
Copyright (C) 2017 David Pretola

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3 as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _H_MORSECODE
#define _H_MORSECODE

#include "MorseStack.h"
#include "MorseTree.h"
#include "MorseTable.h"

/*
A class that encapsulates the MorseTable and MorseTreeRO classes. This class enables
the easy conversion of Morse Code <-> ASCII text via the instance functions.

By David Pretola
*/

//Our MorseCode class

class MorseCode
{
private:
 	//Morse Code <-> ASCII binary search tree.
	static unsigned char tree[TREELENGTH];

 	//Hashmap to enable a quicker ASCII to Morse conversion.
	static unsigned char table[TABLESIZE];

	//Encapsilation of the Hashmap stored in table[].
	MorseTable morseTable;

 	//Encapsilation of the binary search tree in tree[]
	MorseTreeRO morseTree;
public:

	/*
	Constructor 

	Initalize the morseTable and morseTree classes with the static tree and table arrays.

	Arguments:
	NA

	Returns:
	NA
	*/
	MorseCode();

	/*
	Convert the ASCII characters stored within the ascii stack into Morse Code characters
	stored within the coded stack. Each letter is postfixed via a special character to
	indicate a letter gap and each word is postfixed via a special character to indicate
	a word gap.

	Arguments:
	MorseStack & ascii - A stack containing the ASCII text to convert. The beginning of the
				string should be on the bottom of the stack.
	MorseStack & coded - An empty stack that will be filled with the Morse Code of the
				ascii stack.

	Returns:
	NA
	*/
	void Ascii2Morse(MorseStack & ascii,MorseStack & coded);

	/*
	Convert the Morse Code characters stored witin the coded stack to ASCII characters
	stored within the ascii stack. The special Morse Code characters are removed leaving
	a complete ASCII string in the ascii stack.

	Arguments:
	MorseStack & coded - A stack containing the Morse Code to convert. The beginning of the
				Morse Code should be on the bottom of the stack.
	MorseStack & ascii - An empty stack that will be filled with the ASCII of the coded
				stack.

	Returns:
	NA
	*/
	void Morse2Ascii(MorseStack & coded,MorseStack & ascii);	
};
#endif
