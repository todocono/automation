/* Example 5
  by Rodolfo Cossovich http://rudi.plobot.com
  This example code is in the public domain.

  Motors moving in sequences
*/

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

#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

// wifi connection variables
const char* ssid = "IMLab";
const char* password = "";
boolean wifiConnected = false;

// UDP variables
unsigned int localPort = 8888;
WiFiUDP UDP;
boolean udpConnected = false;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char ReplyBuffer[] = "acknowledged"; // a string to send back
boolean stopped = false;

void setup() {
  // Initialise Serial connection
  Serial.begin(115200);

  // Initialise wifi connection
  wifiConnected = connectWifi();
  Serial.println("Starting...");
  // only proceed if wifi connection successful
  if (wifiConnected) {
    udpConnected = connectUDP();
    if (udpConnected) {
      // initialise pins
      pinMode(D0, OUTPUT);
    }
  }
  // initialize digital pin  as an output.
  pinMode(D0, OUTPUT);

  //setup motor driver
  pinMode( PWMA, OUTPUT);
  pinMode( DIRA, OUTPUT);
  pinMode( PWMB, OUTPUT);
  pinMode( DIRB, OUTPUT);
}

void loop() {

  // check if the WiFi and UDP connections were successful
  if (wifiConnected) {
    if (udpConnected) {

      if (stopped)
        breathe(); //makes the light dim if it's not moving
      else
        digitalWrite(D0, LOW);

      // if there’s data available, read a packet
      int packetSize = UDP.parsePacket();
      if (packetSize)
      {
        Serial.println("");
        Serial.print("Received packet of size ");
        Serial.println(packetSize);
        Serial.print("From ");
        IPAddress remote = UDP.remoteIP();
        for (int i = 0; i < 4; i++)
        {
          Serial.print(remote[i], DEC);
          if (i < 3)
          {
            Serial.print(".");
          }
        }
        Serial.print(", port ");
        Serial.println(UDP.remotePort());

        // read the packet into packetBufffer
        UDP.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
        Serial.print("Contents one package of : 0x");

        // hack to connect to Unity
        packetBuffer[0] = packetBuffer[0] & 0x0F;
        packetBuffer[1] = packetBuffer[1] & 0x0F;

        Serial.print(packetBuffer[0], HEX);
        Serial.print(" and another of : 0x");
        Serial.println(packetBuffer[1], HEX);
        Serial.print("Which contents a total of : ");
        int value = packetBuffer[0] * 256 + packetBuffer[1];
        Serial.println(value);

        // send a reply, to the IP address and port that sent us the packet we received
        UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
        UDP.write(ReplyBuffer);
        UDP.endPacket();

        // turn LED on or off depending on value recieved --> it lights if bigger than 0

        if ( packetBuffer[0] == 1 )  forward( packetBuffer[1] * 256 );
        if ( packetBuffer[0] == 2 )  backward( packetBuffer[1] * 256);
        if ( packetBuffer[0] == 3 )  left( packetBuffer[1] * 256 );
        if ( packetBuffer[0] == 4 )  right( packetBuffer[1] * 256 );
        if ( packetBuffer[0] == 0 )  {
          stopped = true;
          stop( );
        }

      }
      delay(10);
    }
  }
}

// connect to UDP – returns true if successful or false if not
boolean connectUDP() {
  boolean state = false;
  Serial.println("");
  Serial.println("Connecting to UDP");

  if (UDP.begin(localPort) == 1) {
    Serial.println("Connection successful");
    state = true;
  }
  else {
    Serial.println("Connection failed");
  }
  return state;
}

// connect to wifi – returns true if successful or false if not
boolean connectWifi() {
  boolean state = true;
  int i = 0;
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 10) {
      state = false;
      break;
    }
    i++;
  }
  if (state) {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("");
    Serial.println("Connection failed.");
  }
  return state;
}


void breathe ( void ) {
  float currentMillis = millis() / 5000.0;
  int value = 512.0 + 512 * sin( currentMillis * 2.0 * PI  );
  analogWrite(D0, value);
}


void forward ( int s_motor ) {
  motor0 (s_motor, 0);
  motor1 (s_motor, 0);
}

void backward ( int s_motor ) {
  motor0 (s_motor, 1);
  motor1 (s_motor, 1);
}

void left ( int s_motor ) {
  motor0 (s_motor, 0);
  motor1 (s_motor, 1);

}

void right ( int s_motor ) {
  motor0 (s_motor, 1);
  motor1 (s_motor, 0);
}


void stop (  ) {
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
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


