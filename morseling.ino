#include <Bridge.h>

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

const unsigned int pauseToSendLength = 5000;

// variables will change:
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
  if (millis() - timer > 5/00) {
    timer = millis();
    Bridge.get("play1", value, 1000);
    String toPlay = String(value);
    
    if(toPlay.length() > 0)
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

            playSound(toPlay);
          }            
          else
            delay(toPlay);
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
      Bridge.put("play1", "");
    }    
    
  }
  


}

/*
 *  Play back a sound for a given length of time
 *  todo: finish this
 */
void playSound(int playTime){
  //play sound!!
}
