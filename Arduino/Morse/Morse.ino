/*
 * A simple sketch to allow for the input of ASCII text,
 * via serial, it's conversion to Morse Code and finally
 * sending that code via the onboard LED light.
 *
 * Notes for the terminal:
 *
 * If you are using the Arduino Serial Monitor, configure the
 * monitor to send a "Carriage return" after each command.
 *
 * If you are using PuTTY, force the Local echo and Local line
 * editing to off, Auto wrap mode initially on. Make sure the
 * Backspace key is 127.
 *
 * The baudrate for the serial is standard 9600 bps, with 8
 * data bits and 1 stop bits, no parity and no flow control.
 *
 */
#include <stdlib.h>
#include <MorseCode.h>

#define USERENTRYSIZE 75 //The max number of characters allowed for input.
#define POT_PIN 0 //The Analog Input Pin to use for speed control.
#define DEF_DOTTIME 60 //The default number of ms for the dot time.

void displayStack(MorseStack & stack);
void blinkMorseCodeLED(unsigned char c);

/*Our Globals */
unsigned int dotTime; //The time in ms for each Morse Code dot in the LED.
char number[20]; //Array to hold the ASCII representation of the dot length value.
unsigned int dotScale; //the value to scale the dotTime, provided by analog input.
MorseCode morse; //Morse Code converter
unsigned char ascii[USERENTRYSIZE]; //array to hold the entered text.
MorseStack stack(ascii,USERENTRYSIZE); //we will place the user entry into a stack.
unsigned char morsecode[USERENTRYSIZE*4]; //array to hold the Morse Code
MorseStack mc(morsecode,USERENTRYSIZE*4); //stack for the Morse Code

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  // configure the builtin LED.
  pinMode(LED_BUILTIN, OUTPUT);

  // configure the analog voltage reference
  analogReference(DEFAULT);
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
          
          //Calculate the time for each dot, based on Analog Input
          dotTime = calculateDotTime();

          displayDotTime();
          displayStack(mc);
          dotTime = DEF_DOTTIME; //don't forget to reset dotTime.
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

/*
 * Calculate the Dot time based upon the Potientiometer input.
 * The time is between 4000ms to 60ms.
 */
int calculateDotTime()
{
  unsigned int dot = analogRead(POT_PIN) * 4.881836;
  dot -= dot % 1000; //make sure the delay is an even number of seconds
  if(dot > 0)
  {
    return dot;
  }
  else
  {
    return DEF_DOTTIME;
  }
}

/*
 * Display the calculated time for each Morse Code dot.
 */
 void displayDotTime()
 {
  Serial.print("Time for 1 Dot: ");
  Serial.write(itoa(dotTime,number,10));
  Serial.println();
 }

/*
 * Display the Morse Code in the provided stack over serial
 * and through blinking the LED on the board.
 */
void displayStack(MorseStack & stack)
{
  unsigned char c; //current Morse Code character.
  do
  {
    c = mc.pop();
    if(c != 0)
    {
      Serial.write(c);
      blinkMorseCodeLED(c);
    }
  }while(c != 0);
  Serial.println();
}

/*
 * Blink the board LED based on the Morse Code character
 * provided
 */
 void blinkMorseCodeLED(unsigned char c)
{
  switch(c)
  {
    case '.': //set the LED on for the duration of the dot.
      digitalWrite(LED_BUILTIN,HIGH);
      delay(dotTime);
      digitalWrite(LED_BUILTIN,LOW);
      delay(dotTime); //delay between the signals for the same letter.
      break;
    case '-': //set the LED to produce three dots
      digitalWrite(LED_BUILTIN,HIGH);
      delay(dotTime*3);
      digitalWrite(LED_BUILTIN,LOW);
      delay(dotTime); //delay between signals for the same letter.
      break;
    case 'l': //delay for three dots between each letter.
      delay(dotTime*3);
      break;
    case 'w': //delay for seven dots between each world
      delay(dotTime*7);
      break;
  }
}
