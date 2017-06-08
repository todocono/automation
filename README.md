# Automation examples with ESP8266
Driving Genius - Course designed by Prof. Christian Grewell.
NYU Abu Dhabi - Summer 2017
Examples by Prof. Rodolfo Cossovich


## Pin definitions for NodeMCU using Arduino IDE
D0 16     //onboard LED
D1 5
D2 4
D3 0
D4 2      //onboard LED, also SDA Slave Select
D5 14     //SCK from the hardware SPI
D6 12     //MISO from the hardware SPI
D7 13     //MOSI from the hardware SPI
D8 15     //needs to be open when flashing
// D9 USB
pinSD2 9 //reserved
pinSD3 10


## For these examples, we will use:
 - IDE downloaded from arduino.cc
 - Board definitions (http://arduino.esp8266.com/stable/package_esp8266com_index.json)
 - NodeMCU 0.9 or higher (http://nodemcu.com/index_en.html)
 - Motor driver L293DD from the DOIT company (https://cdn.hackaday.io/files/8856378895104/user-mannual-for-esp-12e-motor-shield.pdf)
 - Ultrasound sensor HC-SR04 (http://www.micropik.com/PDF/HCSR04.pdf)

## Descriptions on the examples:
 - Blink: it has the pin definitions of the NodeMCU.
 - Breathe: same same but not the same. Uses analogWrite instead and starts the serial port.
 - Motors: using a simple function to set up motors speed.
 - Motors2: creates a super function of the vehicle.
 - Ultrasound: gives feedback through the serial port of the distance.
 - UDP: connects to a fix SSID and talks to a fixed IP port. You will need either Processing or Arduino as well.
 - UDP_Processing: used in Processing for UDP example. It needs http://ubaa.net/shared/processing/udp/
 - UDP-motors: controls motors based on UDP messages. You will need either Processing or Arduino as well.
 - UDPmotors-Processing: remote control for motors. Used in Processing for UDP-motors example.
 - UDPmotors-Unity: remote control for motors. (on the works)
