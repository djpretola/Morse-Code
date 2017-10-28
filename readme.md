#Morse Code

By David Pretola

The *Morse Code* project was created with the purpose of creating software to allow an Arduino to process and generate International Morse Code signals. Rather then write simple software solely within the simple C library provided by Arduino, I wanted to utilize data structures. I also wanted a good reason to write in C++ and I think I have accomplished both goals. I wrote a Stack, Binary Search Tree, Hashtable, Queue and a Round Robbin Scheduler to support the Morse Code processing. Besides the build environment, I have avoided external dependencies, the project is entirely self contained. **Besides one test executable the project does not utilize Strings!!!**

##Data Structure Descriptions

* MorseStack - A stack that processes unsigned chars used to represent the characters for Morse Code. Allows simple operations such as push and pop and reverse. The stack is contained within an array that is provided to the constructor.
* MorseTree - A Binary Search Tree that processes unsigned chars for the encoding and decoding of ASCII characters into Morse Code strings. The strings are stored in MorseStacks. The tree is contained within an array that is proved to the constructor. A look up table in the form of a MorseTable enables for faster encoding of Morse Code.
* MorseTreeRO - An extension of the MorseTree class that does not allow for the insertion of additional Morse Code conversions into the tree.
* MorseTable - A Hashtable that allows for valid ASCII characters for Morse Code to be stored along with an integer. The table is contained within an array that is provided to the constructor. The provided character is an argument into a hash function that calculates an index into the storage array where the provided integer is stored for look up.
* MorseQueue - A circular queue contained within an array of unsigned chars, provided to the constructor. Supports simple operations such as enq and deq and size. This structure is used to store Morse Code characters for processing.
* MorseSchedulerQueue - A circular queue contained within an array of MorseSchedulerQueueElements, provided to the constructor. This structure is identical in design to the MorseQueue but for a different data type. This was done due to the lack of template support in the Arduino. 
* MorseCode - This is not a true data structure, more of an Abstraction Barrier that allows for the conversion between Morse Code and ASCII. **All with Stacks!!!**

I have tried to document the source code as much as possible to provide insight into how they work. Most of the important documentation can be found in the header files.

##Building

The project is built through cmake, which produces all of the executables and Arduino version within the project directory. Since the standard C++ library is not available by default in Arduino, I have configured cmake to **perform some preprocessing** on the source to produce valid C++ for the Arduino IDE. That code is placed under the **Arduino/lib/** directory. Both the **Morse** and **MorseScheduled** Arduino sketches can be copied along with the Arduino/lib directory into the local Arduino sketches and library directory for building through the Arduino IDE. Within the project directory are a series of test executables that perform demonstrations and testing of the data structures. They should be consulted to see examples on how to use the software.

##Building example:

1. cd Morse-Code
2. cmake .
3. make

The Arduino sketches in Arduino/Morse and Arduion/MorseScheduled should be copied or linked to the local Sketchbook location. To determine the local Sketchbook location, open the Arduion IDE and observe the directory under File->Preferences. Usually the lib/ directory under the Sketchbook location is where Arduino libraries are located. Copy or link the Arduino/lib/ directory into the local lib/ directory. The name of the directory created is not important to the IDE, but it of course must be unique.

##Arduino Usage

The Sketchs utilize external circuitry to perform their operations. The pin numbers are defined below the include statements.

* POT_PIN - An analog signal input pin from a potentiometer that allows for the Morse Code dot time to be controlled, the shortest rate 60 ms, which is about 20 words per minute, but this pin allows that to be adjusted up to 4000 ms. **If this feature is not to be used, the pin should be pulled low so the dot time is not random.**
* SPK_PIN - A digital output pin to a Arduino Speaker. This will produce a 750hz tone while a Morse Code signal is being produced, thus allowing you to hear the code.
* DO_PIN - A digital output pin that sends Morse Code in pulse width form. The pin is to be high during the sending of dots and dashes and low for the appropriate intervals. This pin is different from the SPK_PIN in that it is only high or low, no tone is produced.
* DI_PIN1 - A digital interrupt input pin that receives Morse Code from another Arduino or some other hardware. The code should be the same as being sent from the DO_PIN.
* DI_PIN2 - A digital interrupt input pin that receives Morse Code. This pin should be split from the receiving DI_PIN1. The software utilizes interrupts to process the Morse Code so two interrupt pins are required to know when the signal goes high and low.

##Test Executable Descriptions

* morse - Not a true test executable, but it is used to compute the Binary Search Tree and Hashtable for the processing of Morse Code.
* morsecode_test - Tests the conversion of a quote from a Burroughs manual into Morse Code and then back.
* morse_generate - Allows the user to enter text and observe the produced Morse Code. The letter gaps are shown as spaces and the word gaps are shown as a 'w' surrounded by two spaces. **Type q to exit!**
* morse_generate2 - Another test executable that allows the user to enter text and observe the produced Morse Code. The letter gaps are shown with the l character and the word gaps are shown with the w character.
* morsequeue_test - Simple unit test program for MorseQueue class.
* morse_ro - Simple unit test program for the MorseTreeRO class.
* morsescheduler_test - Simple unit demonstration/test program for the MorseScheduler class. Five different functions are scheduled in a Round Robbin fashion 3 times.
* morsescheduler_test2 - Another unit demonstration/test program for the MorseScheduler that utilizes input and output between the scheduled functions and simple execution time delay.
* morse_to_ascii - Convert Morse Code text into ASCII text. It is best to use the Morse Code output from morse_generate2.
