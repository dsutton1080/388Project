#include <Stepper.h>
#include <Wire.h>
#include <LIDARLite.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution for our motor
const int buzzer = 6; // buzzer at pin 6

// initialize the stepper library on pins 8 through 11:
Stepper stepper(stepsPerRevolution, 11, 10, 9, 8);

LIDARLite lidar;

double distance = 0.0;

void setup() {
  
  Serial.begin(9600);
  
  // I think this initializes the digital pot
  Wire.begin();
  
  // initializes the lidar
  lidar.begin(0, true);
  lidar.configure(0);
}

void loop() {
  
  // Clockwise Scan
  for(int i = 0; i < 67; i++) {
    distance = lidar.distance();
    setVolume(64 - distance);
    tone(buzzer, 200 + (2 * i));
    
    stepCW(1);
    delay(50);
  }
  
  // Counter Clockwise Scan
  for(int i = 66; i >= 0; i--) {
    distance = lidar.distance();
    setVolume(64 - distance);
    tone(buzzer, 200 + (2 * i));
    
    stepCCW(1);
    delay(50);
  }
}


void stepCW(int numOfSteps) {
  if(numOfSteps < 0) {
    numOfSteps = (-1) * numOfSteps;
  }
  stepper.step(numOfSteps);
}

void stepCCW(int numOfSteps) {
  if(numOfSteps < 0) {
    numOfSteps = (-1) * numOfSteps;
  }
  stepper.step((-1) * numOfSteps);
}

// level goes from 0 to 64
void setVolume(int level) {
  if(level < 0) {
    level = 0;
  }
  Wire.beginTransmission(44); // transmit to device #44 (0x2c) device address is specified in datasheet
  Wire.write(byte(0x00));            // sends instruction byte
  Wire.write(level);             // sends potentiometer value byte
  Wire.endTransmission(); 
}
