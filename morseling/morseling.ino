/*
  Button
 
 Turns on and off a light emitting diode(LED) connected to digital  
 pin 13, when pressing a pushbutton attached to pin 2. 
 
 
 The circuit:
 * LED attached from pin 13 to ground 
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground
 
 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.
 
 
 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/Button
 */

// constants won't change. They're used here to 
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  10;      // the number of the LED pin
const unsigned int pauseToSendLength = 5000;

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
unsigned long lastChangeMilliseconds = 0;
unsigned long now = 0;
int currentButtonState = LOW;
String output = "";

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  
  lastChangeMilliseconds = 0;

  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);     
}

void loop(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  output = "";
  
  
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
        output = output + "\n..." + buttonState + " for " + (String)(millis() - lastChangeMilliseconds);
        lastChangeMilliseconds = millis();
      }
      
      if((buttonState == LOW) && ((millis() - lastChangeMilliseconds) >= pauseToSendLength))
      {
        Serial.println("*****" + (String)lastChangeMilliseconds + "*******"); 
        break;
      }
    }    
  }
//  
//  while(buttonState != LOW && (millis()-lastChangeMilliseconds) <= pauseToSendLength)
//  {
//    
//
//  }
  
  digitalWrite(ledPin, LOW);
  
  if(output != "")
  {
    Serial.println(output);
    Serial.println("\n\n\n\n");   
  }

  

}
