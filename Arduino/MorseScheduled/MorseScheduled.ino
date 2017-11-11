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
/*
 * A more complex sketch to allow for the input of ASCII text,
 * via serial, it's conversion to Morse Code and finally
 * sending that code via the onboard LED light, a Speaker
 * and through digital output. The sketch utilizes the scheduling
 * of functions through the MorseScheduler class.
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
#include <MorseCode.h>
#include <MorseQueue.h>
#include <MorseScheduler.h>

//The Pins
#define POT_PIN 0 //The Analog Input Pin to use for morse buadrate control.
#define SPK_PIN 11 //The Digital Output Pin for the speaker.
#define DO_PIN 13 //The Digital Output Pin for genaric Digital Out.
#define DI_PIN1 2 //The Digital Input Pin for genaric Digital Input.
#define DI_PIN2 3 //The Digital Input Pin for genaric Digital Input. Both are required.

#define USERENTRYSIZE 75 //The max number of characters allowed for input.
#define DEF_DOTTIME 60 //The default number of ms for the dot time.
#define MAXPULSECOUNT 50 //The max number of pulses to record for input.
#define SCHEDSIZE 10 //The size of the scheduler queue.

/*Our Globals */
unsigned int dotTime; //The time in ms for each Morse Code dot in the LED.
MorseCode morse; //Morse Code converter

unsigned char ascii[USERENTRYSIZE]; //array to hold the entered text.
MorseStack stack(ascii,USERENTRYSIZE); //we will place the user entry into a stack.

unsigned char morsecode[USERENTRYSIZE*4]; //array to hold the Morse Code
MorseStack mc(morsecode,USERENTRYSIZE*4); //stack for the Morse Code

unsigned char receivedMorseCode[MAXPULSECOUNT]; //array to hold received Morse Code over DI.
MorseQueue recmc(receivedMorseCode,MAXPULSECOUNT); //queue for the Received Morse Code

unsigned char recStackArray[MAXPULSECOUNT]; //array to hold the received Morse Code in a stack
MorseStack recStack(recStackArray,MAXPULSECOUNT); //stack to hold the received Morse Code for conversion

volatile unsigned long startPulse = 0; //the time stamp in ms of the start of the last morse code pulse.
volatile unsigned long endPulse = 0; //the time stamp in ms of the end of the last morse code pulse.
volatile bool receivedLetter = false; //Have we received a Morse Code character over DI?
volatile bool receivedWord = false; //Have we received a Morse Code word gap over DI?

unsigned long loopTime; //The time since the last loop call

MorseSchedulerQueueElement schedQueueElements[SCHEDSIZE]; //array to hold the function elements to be scheduled.
MorseSchedulerQueue schedQueue(schedQueueElements,SCHEDSIZE); //queue to hold the function elements.
MorseScheduler sched(&schedQueue); //our scheduler

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  // configure the builtin LED.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // configure the digital output pin.
  pinMode(DO_PIN, OUTPUT);
  digitalWrite(DO_PIN, LOW);

  // configure the analog voltage reference
  analogReference(DEFAULT);

  // Initalize dotTime
  dotTime = calculateDotTime();

  // configure our Interrupt routines
  pinMode(DI_PIN1, INPUT);
  pinMode(DI_PIN2, INPUT);
  attachInterrupt(digitalPinToInterrupt(DI_PIN1), startpulse, RISING);
  attachInterrupt(digitalPinToInterrupt(DI_PIN2), endpulse, FALLING);
  interrupts(); //enable interrupts

  sched.schedule(processSerial);
  sched.schedule(processMorseCode);
}

void loop()
{
  // put your main code here, to run repeatedly:

  loopTime = millis(); //what time is it?
  sched.tick(loopTime);
}

void processSerial(void * i, void * o)
{
  bool reschedule = true; //do we need to reschedule the function.
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
        //morse.Ascii2Morse(stack,mc);
        sched.schedule(callAscii2Morse,&stack,&mc);

        //Calculate the time for each dot, based on Analog Input
        dotTime = calculateDotTime();

        displayDotTime();
        //displayStack(mc);
        reschedule = false; //don't allow processSerial call to effect the transmission of the Morse Code

        break;
      case 0x7F: //BS, then remove the character from the stack
        stack.pop();
        Serial.write(entry); //Echo the backspace
        break;
      default:
        entry = stack.push(entry);
        Serial.write(entry); //Echo back the character pushed onto the stack.
    }
  }
  if(reschedule)
  {
    sched.schedule(processSerial); //reschedule the serial processing.
  }
}

void processMorseCode(void * i,void * o)
{
  //Process any received letters or words over Digtial Input, those are Morse Code characters
  if(receivedLetter) //Processing the Morse Code on a word gap, forces Morse2Ascii to strip the white space.
  {
    //move the contents of the received Morse Code stack into the Received Stack.
    unsigned char c;
    do
    {
      c = recmc.deq();
      if(c != 0)
      {
        recStack.push(c);
        //Serial.write(c); //DEBUG
      }
    }while(c != 0);

    //Convert the received Morse Code to ASCII
    sched.schedule(callMorse2Ascii,&recStack,&stack);

    //reset the received flags
    receivedLetter = false;
    receivedWord = false;
  }
  //Do we have a character to decode and has the last pulse ended over two word spaces ago?
  //If yes, the message has completed, but we still have to process the last character received.
  //loopTime is a global variable
  else if(recmc.size() > 0 && (endPulse < loopTime - (dotTime * 14)))
  {
    //receivedWord = true; //loop back around and treat the last character as the final word for this message.
    receivedLetter = true;
    sched.schedule(processMorseCode,i,o); //reschedule the processing of Morse Code.
  }
  else
  {
    sched.schedule(processMorseCode,i,o); //reschedule the processing of Morse Code.
  }
}

void callMorse2Ascii(void * i,void * o)
{
  MorseStack * inStack = (MorseStack*)i;
  MorseStack * outStack = (MorseStack*)o;
  morse.Morse2Ascii(*inStack,*outStack);
  sched.schedule(outputStackOverSerial,outStack);
}

void outputStackOverSerial(void * i,void * o)
{
  MorseStack * output = (MorseStack*)i;
  unsigned char c;
  //Display the stack over Serial
    do
    {
      c = output->pop();
      if (c != 0)
      {
        Serial.write(c);
      }
    }while(c != 0);
    sched.schedule(processMorseCode); //make sure to enable the processing of additional Morse Code.
}

void callAscii2Morse(void * i,void * o)
{
  MorseStack * inStack = (MorseStack*)i;
  MorseStack * outStack = (MorseStack*)o;
  morse.Ascii2Morse(*inStack,*outStack);
  sched.schedule(displayStack,&mc);
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
 * over Serial.
 */
void displayDotTime()
{
  Serial.print("Time for 1 Dot: ");
  Serial.print(dotTime,10);
  Serial.println(" ms");
}

/*
 * Display the Morse Code in the provided stack over serial,
 * through blinking the LED on the board, through digital out
 * and through the speaker.
 */
void displayStack(void * i, void * o)
{
  signalsOff(0,0);
  MorseStack * instack = (MorseStack*)i;
  unsigned char c; //current Morse Code character.
  unsigned long currentDelay = loopTime; //the current delay before a new signal, either letter or word gap.
    c = instack->pop();
    if(c != 0)
    {
      if(c == 'l')
      {
        Serial.write(' '); //one space between each morse letter.
        currentDelay += dotTime * 3;//delay for three dots between each letter.
        sched.schedule(displayStack,i,o,currentDelay);
      }
      else if(c == 'w')
      {
        Serial.write("  "); //two spaces between each morse word.
        currentDelay += dotTime * 7; //delay for seven dots between each word.
        sched.schedule(displayStack,i,o,currentDelay);
      }
      else if(c == '.')
      {
        signalsOn();
        Serial.write(c);
        currentDelay += dotTime;
        sched.schedule(signalsOff,0,0,currentDelay);
        currentDelay += dotTime; //delay between siganls for the same letter.
        sched.schedule(displayStack,i,o,currentDelay);
      }
      else if(c =='-')
      {
        signalsOn();
        Serial.write(c);
        currentDelay += dotTime * 3;
        sched.schedule(signalsOff,0,0,currentDelay);
        currentDelay += dotTime; //delay between signals for the same letter.
        sched.schedule(displayStack,i,o,currentDelay);
      }
    }
    else //send the newline and don't reschedule, but schedule the processSerial function.
    {
      Serial.println();
      sched.schedule(processSerial);
    }
}

/*
 * Turn the Morse Code signals to on by bringing the LED, Digital Output Pin to high.
 * Also turn the speaker tone on.
 */
void signalsOn()
{
  digitalWrite(LED_BUILTIN,HIGH); //set the LED on for the duration of the dot.
  tone(SPK_PIN,750); //Speaker on
  digitalWrite(DO_PIN,HIGH); //Digital on
}

/*
 * Turn the Morse Code signals to off by bringing the LED, Digital Output Pin to low.
 * Also turn off the speaker tone.
 */
void signalsOff(void * i,void * o)
{
  digitalWrite(LED_BUILTIN,LOW);
  noTone(SPK_PIN); //Speaker off
  digitalWrite(DO_PIN,LOW); //Digital off
}

/*
    ISR to record the timestamp of when the Digital Input goes high.
*/
void startpulse()
{
  startPulse = millis();
  unsigned int pulseGapTime = startPulse - endPulse;
  unsigned int letterPulseGap = dotTime * 3;
  unsigned int wordPulseGap = dotTime * 7;
  //Does a letter or word gap exist after the last pulse time?
  if (pulseGapTime >= letterPulseGap - 2 && pulseGapTime <= letterPulseGap + 2) //within +-2 ms for a letter gap.
  {
    recmc.enq('l');
    receivedLetter = true;
  }
  else if (pulseGapTime >= wordPulseGap - 2 && pulseGapTime <= wordPulseGap + 2) //within +-2 ms for a word gap.
  {
    recmc.enq('w');
    receivedWord = true;
  }
}

/*
  ISR to record the timestamp of when the Digital Input goes low.
*/
void endpulse()
{
  endPulse = millis();
  unsigned int pulseTime = endPulse - startPulse;
  unsigned int dashTime = dotTime * 3;
  if (pulseTime >= dotTime - 2 && pulseTime <= dotTime + 2) //within +-2 ms for a dot, push '.'
  {
    recmc.enq('.');
  }
  else if (pulseTime >= dashTime - 2 && pulseTime <= dashTime + 2) //within +-2 ms for dash, push '-'
  {
    recmc.enq('-');
  }
}
