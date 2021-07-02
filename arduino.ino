#include <Joystick.h>

#include <LedControl.h>
#include <hcsr04.h>
HCSR04 hcsr04(8, 9, 20, 4000);
LedControl lc = LedControl(12, 11, 10, 1);
#include "Joystick.h"


unsigned long startMillis = 0;
//unsigned long startMillis2;
unsigned long currentTime = 0;
unsigned long period = 100;
//unsigned long period2 = 100;
//unsigned long zeroTime = 0;

int VRx = A0;
int VRy = A1;
int SW = 2;



void setup() {
  Serial.begin(9600);
  lc.shutdown(0, false);
  lc.setIntensity(0, 1);
  lc.clearDisplay(0);

  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);
}

byte incomingByte[3]; // for incoming serial data
bool done = false;

int joyX;
int joyY;
int distance;

void loop() {
  joyX = analogRead(VRx);
  joyY = analogRead(VRy);

  Serial.print('0');
  Serial.print(String(joyX));
  Serial.print(',');
  Serial.print(String(joyY));
  Serial.print(';');
  
  distance = hcsr04.distanceInMillimeters();

  Serial.print('1');
  Serial.print(String(distance));
  Serial.print(';');
  
  handleSerial();
}



String distanceString = "";




int currentRow;
int currentColumn;

void handleSerial() {

    
   
    // send data only when you receive data:
    // read the incoming byte:
    if (Serial.available() > 0) {
      Serial.readBytes(incomingByte, 3);
      int col = incomingByte[0] - 48;
      int row = incomingByte[2] - 48;
      if ((currentRow != row) || (currentColumn != col)) {
        currentRow = row;
        currentColumn = col;
        lc.clearDisplay(0);
        lc.setLed(0, col, row, HIGH);
      }
    }
    
}
