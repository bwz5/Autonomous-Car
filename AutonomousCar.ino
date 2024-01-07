#include <Servo.h>

Servo leftWheel; 
Servo rightWheel; 
Servo turnWheel; // steering servo. 0 direction is left, and 180 is right. 90 is going forward. 

const int trigPinLeft = 10;  // stores trig pin for hc sr04 
const int echoPinLeft = 11; // stores echo pin for hc sr04

const int trigPinRight = 12; 
const int echoPinRight = 13; 

float durationLeft, distanceLeft; 

float durationRight, distanceRight; 

void setup() {
  pinMode(trigPinLeft, OUTPUT); // eastablishes the hc sr04 with their respective pins 
  pinMode(echoPinLeft, INPUT); 

  pinMode(trigPinRight, OUTPUT); 
  pinMode(echoPinRight, INPUT); 

  leftWheel.attach(6); 

  rightWheel.attach(3); 

  turnWheel.attach(9); 

  turnWheel.write(90); 

  Serial.begin(9600); 
}

int distanceMeasure(int trigPin, int echoPin){ // uses the hc sr04 to measure the distance to a target in front of it via ultrasound
  digitalWrite(trigPin, LOW);  

	delayMicroseconds(2);  

	digitalWrite(trigPin, HIGH);  

	delayMicroseconds(10);  

	digitalWrite(trigPin, LOW);

  int duration = pulseIn(echoPin, HIGH);

  return  (duration *.0343)/2;  
}

void turnBackWheels(){ 
  leftWheel.write(180); 
  rightWheel.write(0); 
  delay(15); 
}

void loop() {
  // Left distance sensor

  distanceLeft = distanceMeasure(trigPinLeft, echoPinLeft);  
  Serial.println(distanceLeft);   

  // Right distance sensor 
  distanceRight = distanceMeasure(trigPinRight, echoPinRight); 
  Serial.println(distanceRight); 

  turnWheel.write(90); 
  delay(15); 
  if (distanceLeft > 10 && distanceRight <= 10){ // turn left; 
    turnWheel.write(45); 
  } else if (distanceRight > 10 && distanceLeft <= 10){ // turn right; 
    turnWheel.write(135); 
  }
  else if (distanceRight > 10 && distanceLeft > 10){ // stop movement; 
    turnWheel.write(90); 
    turnBackWheels(); 
  } else {
    leftWheel.write(90); // go forward; 
    rightWheel.write(90); 
    delay(15);
  }

  delay(100); 

}