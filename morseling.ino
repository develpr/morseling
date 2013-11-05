#include <Bridge.h>
#include <CapacitiveSensor.h>
#include <Console.h>
#include <MemoryFree.h>

/*
 *  Morseling script
 *
 *  Requires a Yun!!!	
 * 
 *  @author Kevin Mitchell
 */

// constants won't change. They're used here to 
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  10;      // the number of the LED pin
const unsigned int pauseToSendLength = 5000;


CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,3);
CapacitiveSensor   cs_4_5 = CapacitiveSensor(4,5);



// variables will change:

int playbackMultiplier = 1;
int buttonState = 0;         // variable for reading the pushbutton status
unsigned long lastChangeMilliseconds = 0;
unsigned long now = 0;
int currentButtonState = LOW;
String output = "";
String toPlay = "";

char value[1000];
char action = ' ';
int playTime = 0;
long timer = 0; //a timer
long replayButton = 0;
long multiplyButton = 0;

void setup() {
  lastChangeMilliseconds = 0;
  Bridge.begin();
  Console.begin(); 
  while(!Console);
  
  Console.println("HELLO!!");
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);     
  timer = millis();
}

void loop(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  replayButton =  cs_4_2.capacitiveSensor(30);
  multiplyButton =  cs_4_5.capacitiveSensor(30);
  
  //Should we change the message playback multiplier?
  if(multiplyButton > 100)
  {
    playbackMultiplier++;
    if(playbackMultiplier > 5)
      playbackMultiplier = 1;
    
    beepXTimes(playbackMultiplier);     
  }

  //Check if replay button has been pressed
  if(replayButton > 100)
  {
    Bridge.get("replay", value, 1000);
    toPlay = String(value);
    play(playbackMultiplier);  
  }
  
  //todo: for some reason without a button actually hooked up the Yun seems to enter this loop and never leave
  
  if(buttonState == HIGH)
  {
    output = ""; 
    
    int count = 1;
    lastChangeMilliseconds = millis();
    while(true)
    {
      digitalWrite(ledPin, HIGH);
    
      currentButtonState = digitalRead(buttonPin);
      
      if(buttonState != currentButtonState)
      {
        buttonState = currentButtonState;
        output = output + "a" + buttonState + "b" + (String)(millis() - lastChangeMilliseconds);
        lastChangeMilliseconds = millis();
      }
      
      if((buttonState == LOW) && ((millis() - lastChangeMilliseconds) >= pauseToSendLength))
      {        
        break;
      }
    }    
  }
  
  digitalWrite(ledPin, LOW);
//    
//  output = "a0b100a1b100a0b100a1b100a0b100a1b300a0b300a1b100a0b300a1b100a0b300a1b300a0b100a1b100a0b100a1b100a0b100";
//  
  if(output != "")
  {

    //Get the first message buffer
    Bridge.get("message1", value, 1000);
    String tsts = String(value);

    //If the first message buffer is free, which it probably will be
    //then we'll go ahead and write our message to it
    if(tsts.length() == 0)
      Bridge.put("message1", output);
    else
    {
      Bridge.put("message2", output);
    }
  }
    
  /* Every 500ms: */
  //todo: TEST THIS!!!!!
  //Here we should check to see if any new messages are here, every few seconds
  //http://jsfiddle.net/8JTLU/4/
  if (millis() - timer > 500) {
    timer = millis();
    Bridge.get("play1", value, 1000);
    toPlay = String(value);

    
    if(toPlay.length() > 0)
    {
      Console.print("freeMemory()=");
      Console.println(freeMemory());
      Console.println(toPlay);
      play(playbackMultiplier);      
      Bridge.put("play1", "");
    }    
    
  }
  
}

void beepXTimes(int times)
{
  for(int i = 0; i < times; i++)
  {
    digitalWrite(ledPin, HIGH);
    delay(400);
    digitalWrite(ledPin, LOW);
    delay(400);
  } 
}

void play(int multiplier)
{
  Console.print("freeMemory()=");
  Console.println(freeMemory());
  //a0b3a1b1a0b1a1b1a0b3a1b3a1b7a0b3a1b1a0b1a1b1a0b3a1b3
  multiplier = 400 * pow(1.2,multiplier);
  action = ' ';
  for(int i = 0; i < toPlay.length(); i+=4)
  {
    action = toPlay.charAt(i+1);
    playTime = toPlay.charAt(i+3) - '0';
    Console.print("playing... ");
  
    if(action == '0')
    {
      playSound(playTime);
    }            
    else
    {
      digitalWrite(ledPin, LOW);
      delay(playTime);
    }      
  }
  Console.println("\nFinished playing\n");
}

/*
 *  Play back a sound for a given length of time
 *  todo: finish this
 */
void playSound(int playTime){
  //play sound!!
  digitalWrite(ledPin, HIGH);
  delay(playTime);
  digitalWrite(ledPin, LOW);
}
