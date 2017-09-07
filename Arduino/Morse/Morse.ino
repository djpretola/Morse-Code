/*
 * A simple sketch to allow for the input of ASCII text,
 * via serial, it's conversion to Morse Code and finally
 * sending that code via the onboard LED light, a Speaker
 * and through digital output.
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

//The output pins
#define POT_PIN 0 //The Analog Input Pin to use for morse buadrate control.
#define SPK_PIN 11 //The Digital Output Pin for the speaker.
#define DO_PIN 13 //The Digital Output Pin for genaric Digital Out.

#define USERENTRYSIZE 75 //The max number of characters allowed for input.
#define DEF_DOTTIME 60 //The default number of ms for the dot time.
#define MAXPULSECOUNT 150*3 //The max number of pulses to record for input.

void displayStack(MorseStack & stack);
void blinkMorseCodeLED(unsigned char c);

/*Our Globals */
unsigned int dotTime = DEF_DOTTIME; //The time in ms for each Morse Code dot in the LED.
char number[20]; //Array to hold the ASCII representation of the dot length value.
unsigned int dotScale; //the value to scale the dotTime, provided by analog input.
MorseCode morse; //Morse Code converter
unsigned char ascii[USERENTRYSIZE]; //array to hold the entered text.
MorseStack stack(ascii,USERENTRYSIZE); //we will place the user entry into a stack.
unsigned char morsecode[USERENTRYSIZE*4]; //array to hold the Morse Code
MorseStack mc(morsecode,USERENTRYSIZE*4); //stack for the Morse Code
volatile unsigned int pulses[MAXPULSECOUNT]; //array to hold the received Digital Input timestamps.
volatile unsigned int pulseCount = 0; //the number of time stamps in pulses[].

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

  // configure our Interrupt routines
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  attachInterrupt(digitalPinToInterrupt(2),pulse,RISING);
  attachInterrupt(digitalPinToInterrupt(3),pulse,FALLING);
  interrupts(); //enable interrupts
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

  //Process any received pulses over Digtial Input, those are Morse Code signals
  if(pulseCount > 0)
  {
    int twoAway = pulseCount - 2; //The index value two away from the end of the pulse count.
    for(int i = 0;i<pulseCount;i=i+2)
    {
      if(i < twoAway)
      {
        inputMorseCode((unsigned int)(pulses[i+1] - pulses[i]),(unsigned int)(pulses[i+2] - pulses[i+1]),mc);
      }
      else //we are at the end of the pulseCount and no letter or word gap on the end.
      {
        inputMorseCode((unsigned int)(pulses[i+1] - pulses[i]),0,mc);
      }
    }
    pulseCount = 0; //reset the pulse count

    //Convert the Morse Code to ASCII
    morse.Morse2Ascii(mc,stack);

    unsigned char c;
    do
    {
      c = stack.pop();
      if(c != 0)
      {
        Serial.write(c);
      }
    }while(c != 0);
    Serial.println();
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
 * through blinking the LED on the board and through the
 * speaker.
 */
void displayStack(MorseStack & stack)
{
  unsigned char c; //current Morse Code character.
  do
  {
    c = mc.pop();
    if(c != 0)
    {
      if(c == 'l')
      {
        Serial.write(' '); //one space between each morse letter.
      }
      else if(c == 'w')
      {
        Serial.write("  "); //two spaces between each morse word.
      }
      else
      {
        Serial.write(c);
      }
      generateMorseCode(c);
    }
  }while(c != 0);
  Serial.println();
}

/*
 * Blink the board LED and send a 750hz tone through the speaker, and pulse the digital output pin
 * based on the Morse Code character provided.
 */
 void generateMorseCode(unsigned char c)
{
  switch(c)
  {
    case '.':
      digitalWrite(LED_BUILTIN,HIGH); //set the LED on for the duration of the dot.
      tone(SPK_PIN,750); //Speaker on
      digitalWrite(DO_PIN,HIGH); //Digital on
      delay(dotTime);
      digitalWrite(LED_BUILTIN,LOW);
      noTone(SPK_PIN); //Speaker off
      digitalWrite(DO_PIN,LOW); //Digital off
      delay(dotTime); //delay between the signals for the same letter.
      break;
    case '-':
      digitalWrite(LED_BUILTIN,HIGH); //set the LED on for three dots.
      tone(SPK_PIN,750); //Speaker on
      digitalWrite(DO_PIN,HIGH); //Digital on
      delay(dotTime*3);
      digitalWrite(LED_BUILTIN,LOW);
      noTone(SPK_PIN); //Speaker off
      digitalWrite(DO_PIN,LOW); //Digital off
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

/*
 *  ISR to record the timestamp of when the Digital Input goes high and low.
 */
void pulse()
{
  if(pulseCount < MAXPULSECOUNT) pulses[pulseCount++] = millis();
}

/*
 * Push the appropriate Morse Code character into the input stack, depending upon
 * how long the pulseTime is.
 */
void inputMorseCode(unsigned int pulseTime, unsigned int timeUntilNextPulse, MorseStack & inStack)
{
  unsigned int dashTime = dotTime * 3;
  if(pulseTime > dotTime - 2 && pulseTime < dotTime + 2) //within +-2 ms for a dot, push '.'
  {
    inStack.push('.');
  }
  else if(pulseTime > dashTime - 2 && pulseTime < dashTime + 2) //within +-2 ms for dash, push '-'
  {
    inStack.push('-');
  }

  //Does a letter or word gap exist after the last pulse time?
  if(timeUntilNextPulse > (dotTime*4) - 2 && timeUntilNextPulse < (dotTime*4) + 2) //within +-2 ms for a letter gap.
  {
    inStack.push('l');
  }
  else if(timeUntilNextPulse > (dotTime*8) - 2 && timeUntilNextPulse < (dotTime*8) + 2) //within +-2 ms for a word gap.
  {
    inStack.push('w');
  }
}
