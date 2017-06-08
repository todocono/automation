// Processing UDP example to send and receive binary data
// press f to toggel between LED flickering twice per second or not
// the LED will illuminate when any other key is held down and
// turn back off when the key is released.

/**
 * ControlP5 Button
 * this example shows how to create buttons with controlP5.
 * 
 * find a list of public methods available for the Button Controller 
 * at the bottom of this sketch's source code
 *
 * by Andreas Schlegel, 2012
 * www.sojamo.de/libraries/controlp5
 *
 */

import controlP5.*;

ControlP5 cp5;

int myColor = color(255);

int c1, c2;

float n, n1;


import hypermedia.net.*;

UDP udp; // define the UDP object

String ip = "127.0.0.1"; //"192.168.43.84"; // the remote IP address
int port =  8888; // the destination port

long previousMillis = 0;
int light = 0;
long interval = 500;
int flicker = 0;
int held = 0;
int Speed = 100;

void setup() {
  udp = new UDP( this, port ); // create a new datagram connection on port 
  //udp.log( true ); // <– printout the connection activity
  udp.listen( true ); // and wait for incoming message

  size(400, 400);
  noStroke();
  cp5 = new ControlP5(this);

  // create a new button with name 'buttonA'
  cp5.addButton("Front")
    .setValue(0)
    .setPosition(150, 100)
    .setSize(100, 19)
    ;

  // and add another 2 buttons
  cp5.addButton("Back")
    .setValue(100)
    .setPosition(150, 140)
    .setSize(100, 19)
    ;

  cp5.addButton("Left")
    .setPosition(50, 120)
    .setSize(100, 19)
    .setValue(0)
    ;

  cp5.addButton("Right")
    .setPosition(250, 120)
    .setSize(100, 19)
    .setValue(0)
    ;
    
      cp5.addButton("Stop")
    .setPosition(175, 120)
    .setSize(50, 19)
    .setValue(0)
    ;

  cp5.addSlider("Speed")
    .setPosition(200, 200)
    .setRange(0, 255)
    ;
}

void draw()
{
  if (flicker == 1) {
    if (previousMillis < millis() - interval) {
      previousMillis = previousMillis + interval;
      if (light == 0) {
        byte[] message = new byte[2];
        message[0] = 0;
        message[1] = 0;
        udp.send(message, ip, port);
        light = 1;
      } else {
        byte[] message = new byte[2];
        message[0] = 0;
        message[1] = 1;
        udp.send(message, ip, port);
        light = 0;
      }
    }
  }

  background(myColor);
  myColor = lerpColor(c1, c2, n);
  n += (1-n)* 0.1;
}

void keyPressed() {

  if (key == 'f') {
    if (flicker == 1) {
      flicker = 0;
      byte[] message = new byte[2];
      message[0] = 0;
      message[1] = 0;
      udp.send(message, ip, port);
      light = 0;
    } else {
      flicker = 1;
    }
  } else {
    if (flicker == 0 && held == 0) {
      byte[] message = new byte[2];
      message[0] = 0;
      message[1] = 9;
      udp.send(message, ip, port);
      held = 1;
    }
  }
}

void keyReleased() {
  if (key != 'f') {
    if (flicker == 0) {
      byte[] message = new byte[2];
      message[0] = 0;
      message[1] = 0;
      udp.send(message, ip, port);
      held = 0;
    }
  }
}

/*
void mouseReleased() {
  byte[] message = new byte[2];
  message[0] = 0;
  message[1] = 0;
  udp.send(message, ip, port);
}
*/

void receive( byte[] data ) { // <– default handler
  //void receive( byte[] data, String ip, int port ) { // <– extended handler

  for (int i=0; i < data.length; i++)
    print(char(data[i]));
  println();
}


public void controlEvent(ControlEvent theEvent) {
  println(theEvent.getController().getName());
  n = 0;
}

public void Front(int theValue) {
  println("a button event from colorA: "+theValue);
  c1 = c2;
  c2 = color(0, 160, 100);
  byte[] message = new byte[2];
  message[0] = 1;
  message[1] = (byte)Speed;
  udp.send(message, ip, port);
}

public void Back(int theValue) {
  println("a button event from colorB: "+theValue);
  c1 = c2;
  c2 = color(150, 0, 0);
  byte[] message = new byte[2];
  message[0] =2;
  message[1] = (byte)Speed;
  udp.send(message, ip, port);
}

public void Left(int theValue) {
  println("a button event from colorC: "+theValue);
  c1 = c2;
  c2 = color(100, 160, 100);
  byte[] message = new byte[2];
  message[0] = 3;
  message[1] = (byte)Speed;
  udp.send(message, ip, port);
}

public void Right(int theValue) {
  println("a button event from colorC: "+theValue);
  c1 = c2;
  c2 = color(255, 255, 0);
  byte[] message = new byte[2];
  message[0] = 4;
  message[1] = (byte)Speed;
  udp.send(message, ip, port);
}

public void Stop(int theValue) {
  println("a button event from colorB: "+theValue);
  c1 = c2;
  c2 = color(255, 0, 0);
  byte[] message = new byte[2];
  message[0] =0;
  message[1] = 0;
  udp.send(message, ip, port);
}