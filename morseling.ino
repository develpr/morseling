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

int playbackMultiplier = 1; //the multiplier to use for playback speed
int buttonState = 0;         // variable for reading the pushbutton status
unsigned long lastChangeMilliseconds = 0;
unsigned long now = 0;
int currentButtonState = LOW;
String output = "";
String toPlay = "";

char value[255];
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
    Console.println("high button state");
    
    //reset the output
    output = ""; 
    
    int count = 1;
    lastChangeMilliseconds = millis();
    while(true)
    {
      Console.print("freeMemory()=");
      Console.println(freeMemory());
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

    Console.println("output != 0");
    //Get the first message buffer
    
    //todo: this would be the spot we'd want to check for an existing message
    //      and use a different output (message2, etc)

    //if the message is less then 250 characters, then we'll write it directly out and move on!

    int writeIndex = 0;
    char writeLocation[] = "message1X";      

    while(output.length() > 0)
    {      

      if(writeIndex < 10)
        writeLocation[8]='0'+writeIndex;
      Console.print("here: ");   
      Console.println(writeLocation);         
   
      int subLength = output.length() > 250 ? 250 : output.length();
      Console.println("goes: ");
      Console.println(output.substring(0, subLength));   
      Bridge.put(writeLocation, output.substring(0, subLength));
      output = output.substring(subLength+1, output.length());  
      writeIndex++;    
    }
    
    output = "";
  }
    
  /* Every 500ms: */
  //todo: TEST THIS!!!!!
  //Here we should check to see if any new messages are here, every few seconds
  //http://jsfiddle.net/8JTLU/4/
  if (millis() - timer > 1000) {
    Console.println("testing every 1000");
    timer = millis();
    
//    toPlay = String(value);
    int readIndex = 0;
    char readLocation[] = "play10";  
    toPlay = "";
        
    Bridge.get(readLocation, value, 255);
    
    while(strlen(value) > 0)
    {
      Console.print("freeMemory()=");
      Console.println(freeMemory());
      Console.print("something to playback in ");
      Console.println(readLocation);
      toPlay = String(value);
      play(playbackMultiplier);  
      Console.print("freeMemory()=");
      Console.println(freeMemory());
      Bridge.put(readLocation, "");
      readIndex++;
      if(readIndex < 10)
        readLocation[5]='0'+readIndex;
      Bridge.get(readLocation, value, 255);
    }  
  }
  
  toPlay = "";
  
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
  Console.print("memory at start of play method: ");
  Console.println(freeMemory());
  //a0b3a1b1a0b1a1b1a0b3a1b3a1b7a0b3a1b1a0b1a1b1a0b3a1b3
  multiplier = 200 * pow(1.2,multiplier);
  action = ' ';
  Console.println("Going to start playing:");
  Console.println(toPlay);
  for(int i = 0; i < toPlay.length(); i+=4)
  {
    action = toPlay.charAt(i+1);
    Console.print("action: ");
    Console.print(action);
    playTime = toPlay.charAt(i+3) - '0';

    if(playTime < 0)
      playTime = 0; 
    Console.print("playTime: ");
    Console.print(playTime);
    Console.print("playing... ");
  
    if(action == '0')
    {
      playSound(multiplier*playTime);
    }            
    else
    {
      digitalWrite(ledPin, LOW);
      delay(multiplier*playTime);
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
