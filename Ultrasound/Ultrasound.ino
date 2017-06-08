/* Example 3
  by Rodolfo Cossovich http://rudi.plobot.com
  This example code is in the public domain.
  RGB LED connected to D5, D6 & D7
*/

#include <Servo.h>

#define D0 16     //onboard LED 
#define D1 5
#define D2 4
#define D3 0
#define D4 2      //onboard LED
#define D5 14
#define D6 12
#define D7 13
#define D8 15   //needs to be open when flashing
// pin9 USB
// D10 USB
//#define pinSD2 9 //reserved
#define SD3 10



#define trigPin D5
#define echoPin D6


Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 500;           // interval at which to blink (milliseconds)


void setup()
{
  //
  Serial.begin(115200);

  pinMode( D0, OUTPUT);
  pinMode( D1, OUTPUT);
  pinMode( D2, OUTPUT);
  pinMode( D5, OUTPUT);
  pinMode( D6, OUTPUT);
  pinMode( D7, OUTPUT);
  pinMode( D8, OUTPUT);


  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.println("starting...");
}

void loop()
{
  // servo();
  breathe();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    int distance = ultra();
    Serial.println ( distance );
    if (distance < 4) {  // This is where the LED On/Off happens
      Serial.print("really close!");
      servo();
    }
    else {
      //do nothing
    }
    Serial.print(distance);
    Serial.println(" cm");
    delay(500);
  }

 //  Serial.println(" works... ");
 //  delay(500);
}

void servo (void) {
  myservo.attach(D3);
  for (pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees
  { // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) // goes from 180 degrees to 0 degrees
  {
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  myservo.detach();
}

void breathe ( void ) {
  float currentMillis = millis() / 5000.0;
  int value = 512.0 + 512 * sin( currentMillis * 2.0 * PI  );
  analogWrite(D6, value);
  analogWrite(D7, value);
  analogWrite(D5, value);
}


int ultra() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 29) ;
  return (int)distance;
}

