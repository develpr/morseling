#include <MD5.h>

/*
 *  Morse Sender
 */

// constants won't change. They're used here to 
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  10;      // the number of the LED pin
const int secretKey = '12dsf9adf9w39sf032';
const int username = 'develpr';

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
  
  if(output != "")
  {
    //Here is where we send output
    Serial.println(output);
    Serial.println("\n\nHash: ");   
    
    String saltedString = output + secretKey;
    char* testing;
    saltedString.toCharArray(testing, saltedString.length());
    
    unsigned char* test = MD5::make_hash(testing);
    char *md5str = MD5::make_digest(test, 16);
    Serial.println(md5str);
    
    Serial.println("\n\n\n\n");   
  }
  
  //Here we should check to see if any new messages are here, every few seconds

}
