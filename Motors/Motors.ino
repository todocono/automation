
//#include <Servo.h>

#define D0 16     //onboard LED 
#define D1 5
#define D2 4
#define D3 0
#define D4 2      //onboard LED
#define D5 14
#define D6 12
#define D7 13
#define D8 15   //needs to be open when flashing
// D9 USB
// D10 USB
//#define pinSD2 9 //reserved
#define pinSD3 10

//pins for ultrasound
#define trigPin D0
#define echoPin D1

//pins for motors
#define PWMA D1
#define DIRA D3
#define PWMB D2
#define DIRB D4

// constants won't change :
const long TIME = 500;           // interval at which to blink (milliseconds)


void setup()
{
  Serial.begin(115200);
  pinMode( D0, OUTPUT);
  pinMode( D1, OUTPUT);
  pinMode( D2, OUTPUT);
  pinMode( D5, OUTPUT);
  pinMode( D6, OUTPUT);
  pinMode( D7, OUTPUT);
  pinMode( D8, OUTPUT);

  pinMode( PWMA, OUTPUT);
  pinMode( DIRA, OUTPUT);
  pinMode( PWMB, OUTPUT);
  pinMode( DIRB, OUTPUT);
  Serial.println("starting...");
}

void loop()
{
  int speed0 = 1024;
  int speed1 = 1024;
  Serial.println("MOTOR 0...");
  motor0 (speed0, 0);
  delay (TIME);
  motor0 (speed0, 1);
  delay (TIME);
  motor0 (0, 0);

  Serial.println("MOTOR 1...");
  motor1 (speed1, 0);
  delay (TIME);
  motor1 (speed1, 1);
  delay (TIME);
  motor1 (0, 0);
}

void motor0 ( int speed, int direction) {
  if (direction) {
    digitalWrite(DIRA, HIGH);
  }
  else {
    digitalWrite(DIRA, LOW);
  }
  analogWrite(PWMA, speed);
}

void motor1 ( int speed, int direction) {
  if (direction) {
    digitalWrite(DIRB, HIGH);
  }
  else {
    digitalWrite(DIRB, LOW);
  }
  analogWrite(PWMB, speed);
}
