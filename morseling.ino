#include <Bridge.h>
#include <CapacitiveSensor.h>

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
long timer = 0; //a timer
CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,3);
CapacitiveSensor   cs_4_5 = CapacitiveSensor(4,5);

const unsigned int pauseToSendLength = 5000;

// variables will change:
int playbackMultiplier = 5;
int buttonState = 0;         // variable for reading the pushbutton status
unsigned long lastChangeMilliseconds = 0;
unsigned long now = 0;
int currentButtonState = LOW;
String output = "";
String tsts = "";
char value[1000];
String buffer = "";
char action = ' ';
char previous = ' ';
char current = ' ';
long replayButton = 0;
long multiplyButton = 0;

void setup() {
  lastChangeMilliseconds = 0;
  Bridge.begin();

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
    playbackMultiplier = playbackMultiplier * 1.2;
    if(playbackMultiplier > 26)
      playbackMultiplier = 5;
      
    if(playbackMultiplier == 5)
      beepXTimes(1);
    else if(playbackMultiplier >= 7 && playbackMultiplier <= 8)
      beepXTimes(2);
    else if(playbackMultiplier >= 11 && playbackMultiplier <= 12)
      beepXTimes(3);
    else if(playbackMultiplier >= 16 && playbackMultiplier <= 17)
      beepXTimes(4);
    else if(playbackMultiplier >= 25 && playbackMultiplier <= 26)
      beepXTimes(5);      
  }

  //Check if replay button has been pressed
  if(replayButton > 100)
  {
    Bridge.get("replay", value, 1000);
    String toPlay = String(value);
    play(toPlay, playbackMultiplier);  
  }
  

  output = "";  
  //todo: for some reason without a button actually hooked up the Yun seems to enter this loop and never leave
  
  if(buttonState == HIGH)
  {
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

      Bridge.get("message2", value, 1000);
      tsts = String(value);
      if(tsts.length() == 0)
        Bridge.put("message2", output);
      else
      {
	Bridge.put("message3", output);
      }

    }
  }
    
  /* Every 500ms: */
  //todo: TEST THIS!!!!!
  //Here we should check to see if any new messages are here, every few seconds
  //http://jsfiddle.net/8JTLU/4/
  if (millis() - timer > 500) {
    timer = millis();
    Bridge.get("play1", value, 1000);
    String toPlay = String(value);
    
    if(toPlay.length() > 0)
    {
      play(toPlay, playbackMultiplier);      
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

void play(String toPlay, int multiplier)
{
  buffer = "";
  action = ' ';
  current = ' ';
  previous = ' ';
  for(int i = 1; i < toPlay.length(); i++)
  {
    current = toPlay.charAt(i);
    previous = toPlay.charAt(i-1);
    if(current == 'a')
    {
      char bufferTime[buffer.length()];
      buffer.toCharArray(bufferTime, buffer.length());   
      int toPlay = atoi(bufferTime);       
      if(action == '0'){

        playSound(toPlay * multiplier);
      }            
      else
      {
        digitalWrite(ledPin, LOW);
        delay(toPlay * multiplier);
      }
      buffer = "";
      action = ' ';
    }
    
    if(previous == 'a')
      action = current;
      
    else if(current == 'b')
      buffer = "";
     
     else
       buffer += String(current);
      
  }
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
