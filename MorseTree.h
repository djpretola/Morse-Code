/*
A Binary Search tree implementation of Morse Code to ASCII and ASCII to Morse Code
By David Pretola

Here we use an array to store the tree. Formulas for Transversing the tree:

[0] -> root node
[(i-1)/2] -> parent node
[2i+1] -> left child
[2i+2] -> right child
*/

//Our MorseTree class

class MorseTree {
private:
	char * bTree; //array to hold the characters and numbers found in Morse Code plus root
	int treeLength; //the length of the bTree array

	/*
	Helper function for preOrderTansPrinter, that prints the current node with
	4 times the nodes index in spaces before the value. To STDIO.	

	Arguments:
	int i - current bTree array index
	int depth - The depth of the current tree node.

	Returns:
	none
	*/
	void printNodeWSpaces(int i,int depth);

	/*
	Helper function for printTree, that performs a Pre-Order Transversal of the tree
	for printing the contents and structure of the tree to STDIO.

	Arguments:
	int i - current bTree array index
	int depth - The depth of the current tree node.

	Returns:
	none
	*/
	void preOrderTransPrinter(int i,int depth);

	/*
	Perform a Pre-Order transversal of the tree to locate the array index of the specified 
	char.

	Arguments:
	int i - The starting index in the bTree array.
	char c - The character to locate.

	Return:
	int - The index of the specified character in the bTree array.
	*/
	int findCharIndex(int i,char c);

	/*
	Walk up the tree from the specified node index and fill in the string in reverse order,
	with the specified stack.

	Arguments:
	int i - The starting index to the node in the bTree array.
	morseStack & morse - Reference to the stack to use to construct the morse code.

	Returns:
	none
	*/
	void fillInParentString(int i,MorseStack & morse);

	/*
	Insert the specified character with the specified morse code into the tree.

	Arguments:
	char c - The character to store.
	char * code - A pointer to the morse code string. Only '-' and '.' are valid character
	values.
	*/
	void insert(const char c,const char * code);

	/*
	Calculate the parent index of the specified index in bTree.
	Calculation: [(i-1)/2] = parent node

	Arguments:
	int index - The specified index to find the parent of.

	Returns:
	int - The index of the parent node in the bTree array.	
	*/
	int parentOf(int index);
	
	/*
	Calculate the left child index of the specified parent node index in bTree.
	Calculation: [2i+1] = left child

	Arguments:
	int index - The specified parent index to find the child of.

	Returns:
	int - The index of the left child node.
	*/
	int leftChild(int index);

	/*
	Calculate the right child index of the specified parent node index in bTree.
	Calculation: [2i+2] = right child

	Arguments:
	int index - The specified parent index to find the child of.

	Returns:
	int - The index of the right child node.
	*/
	int rightChild(int index);
public:
	/*
	Constructor

	Initalize an empty tree with the provided array and size of the array.
	The constructor will clear the contents of the array.

	Arguments:
	char * bTree - Pointer to the start of the array bTree.
	int treeLength - The size of the *bTree array.

	Returns
	NA
	*/
	MorseTree(char * bTree,int treeLength);

	/*
	Print to STDIO the Morse Tree ordered by tree depth per column.

	Arguments:
	none

	Returns:
	none
	*/
	void printTree(); 

	/*
	Print to STDIO the Morse bTree array.

	Arguments:
	none

	Returns:
	none
	*/
	void printTreeArray();
	
	/*
	Print to STDIO the Morse bTree array in Hexadecimal.

	Arguments:
	none

	Returns:
	none
	*/
	void printTreeArrayHex();

	/*
	Convert the specified character to its specific morse code.
	The contents of the specified stack are filled in with the code, pop each morse
	signal and you have the full character morse code signal.

	Arguments:
	char c - The character to convert to morse code.
	morseStack & morse - Reference to the MorseStack to store the morse code.

	Returns:
	none
	*/
	void Ascii2Morse(char c,MorseStack & morse);
};
