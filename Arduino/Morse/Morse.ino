/*
 * A simple sketch to allow for the input of ASCII text,
 * via serial, it's conversion to Morse Code and finally
 * sending that code via the onboard LED light.
 */
#include <MorseCode.h>
#define USERENTRYSIZE 75
void displayStack(MorseStack & stack);

/*Our Globals */
MorseCode morse;
unsigned char ascii[USERENTRYSIZE]; //array to hold the entered text.
MorseStack stack(ascii,USERENTRYSIZE); //we will place the user entry into a stack.

unsigned char morsecode[USERENTRYSIZE*4]; //array to hold the Morse Code
MorseStack mc(morsecode,USERENTRYSIZE*4); //stack for the Morse Code

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() 
{
  // put your main code here, to run repeatedly:

  //Place the user entered ASCII into the stack.
  if(Serial.available() > 0)
  {
    unsigned char entry;
    entry = Serial.read();
    switch(entry)
    {
      case 0x0D: //CR, then convert the ASCII text.
          Serial.println(); //move cursor to the next line.
          
          //Convert the ASCII to Morse Code
          morse.Ascii2Morse(stack,mc);
          
          displayStack(mc);
          break;
      case 0x7F: //BS, then remove the character from the stack
          stack.pop();
          Serial.write(entry); //Echo the backspace
          break;
      default:
          stack.push(entry);
          Serial.write(entry); //Echo back
    }
  }
}  

void displayStack(MorseStack & stack)
{
  unsigned char c; //current Morse Code character.
  do
  {
    c = mc.pop();
    if(c != 0)
    {
      Serial.write(c);
    }
  }while(c != 0);
  Serial.println();
}

