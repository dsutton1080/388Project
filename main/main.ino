#include <Stepper.h>
#include <Wire.h>
#include <LIDARLite.h>
//initialize variables
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution for our motor
const int buzzer = 6; // buzzer at pin 6
char pos = 't'; //position of lidar
char prev_pos = 'l'; //previous position of stepper

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
  
//  switch(pos){
//    case 't':
//      if(prev_pos == 'l'){
//        distance = lidar.distance();
//        setVolume(64 - distance);
//        tone(buzzer, 200 + (2 * 1), 500);
//        stepCW(67);
//        delay(2000);
//        pos = 'r';
//        break;
//      }
//      else{
//        distance = lidar.distance();
//        setVolume(64 - distance);
//        tone(buzzer, 200 + (2 * 1), 500);
//        stepCCW(-67);
//        delay(2000);
//        pos = 'l';
//        break;
//      }
//    case 'r':
//        distance = lidar.distance();
//        setVolume(64 - distance);
//        tone(buzzer, 200 + (2 * 1), 500);
//        stepCCW(-67);
//        delay(2000);
//        pos = 't';
//        break;
//    case 'l':
//        distance = lidar.distance();
//        setVolume(64 - distance);
//        tone(buzzer, 200 + (2 * 1), 500);
//        stepCW(67);
//        delay(2000);
//        pos = 't';
//        break;
//  }

  
  // Clockwise Scan
  for(int i = 0; i < 67; i++) {
    distance = lidar.distance();
    //setVolume(64 - distance);
      if(i == 0){
        tone(buzzer, 200 + (2* distance), 50);
      }
      else if(i == 33){
        tone(buzzer, 200 + (2* distance), 50);
      }
   
    //tone(buzzer, 200 + (2 * i));
    
    stepCW(1);
    delay(20);
  }
  
  // Counter Clockwise Scan
  for(int i = 66; i >= 0; i--) {
    distance = lidar.distance();
    //setVolume(64 - distance);
    if(i == 0){
        tone(buzzer, 200 + (2* distance), 50);
      }
    else if(i == 66){
        tone(buzzer, 200 + (2* distance), 50);
      }
    
    //tone(buzzer, 200 + (2 * i));
    
    stepCCW(1);
    delay(20);
  }
}


void stepCW(int numOfSteps) {
  if(numOfSteps < 0) {
    numOfSteps = (-1) * numOfSteps;
  }
  stepper.step(numOfSteps);
}

void stepCCW(int numOfSteps) {

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
