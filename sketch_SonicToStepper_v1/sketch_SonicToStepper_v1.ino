/*
 * Copyright 2015 Wang Yinghao
 *
 * Control Stepper from Ultra Sonic Distance Sensor
 *
 */

#define STEP_OF_MOTOR 200
#define SPEED_OF_MOTOR 30

//ultrasonic sensor timeout set as 30000 microseconds
//based on time that sound costs travelling in 10m
//ultrasonic sensor max working range is 5m
#define ULTRA_SONIC_TIMEOUT 30000 

#include <Stepper.h>

const int trigPin = 2;
const int echoPin = 3;
const int stpPin1 = 4;
const int stpPin2 = 5;
const int stpPin3 = 6;
const int stpPin4 = 7;

float pingTime; //sonic ping time in microseconds
float prevDistance = 10000; //previous distance in meters, default is infinity
float distance; //calculated distance in meters

const float speedOfSound = 343.4; //speed of sound in meters per second @ 1atm, 20 degree Celcius - needs fabricate

int currentStep = 0;
int stepsToTurn; //calculated turn steps

//init stepper instance with steps and control pins
Stepper stepper(STEP_OF_MOTOR, stpPin1, stpPin2, stpPin3, stpPin4);

double toFeet(double meters) {
  return meters * 3.2808;
}

//triggering sonic sensor to get distance
void triggerSonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2000);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
}

//Mapping distance to step motor steps, need fabricating
int distanceToStep (double distance) {
  int stepsToTurn = 0;

  //put in functions to convert

  return stepsToTurn;
}

//Printing values, only for developing
void printVal(float t, float s, int steps) {
  String pingTime = String(t, 9);
  String distance = String(s, 9);
  String stepsToTurn = String(steps);
  String prevDist = String(prevDistance, 9);
  String curStp = String(currentStep);

  Serial.print("From Test: \n");
  Serial.print("Prev Distance: " + prevDist + "m\t" + "Current Steps: " + curStp + "steps\n");
  Serial.print("Ping Time: " + pingTime + "s\t" "Distance: " + distance + "m\t" + "Steps To Turn: " + stepsToTurn + "steps\t");
  Serial.print("\n");

}

void setup() {

  stepper.setSpeed(SPEED_OF_MOTOR);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {

  triggerSonic();

  //Get pingTime as seconds, TIMEOUT time set as 5ms - needs fabricating
  pingTime = pulseIn(echoPin, HIGH, ULTRA_SONIC_TIMEOUT);

  pingTime = pingTime / 1000000;

  //pulseIn returns 0 if no results received within TIMEOUT time
  //If pingTime acquired, turn motor according to function of turn.
  if (pingTime) {
    distance = pingTime * speedOfSound / 2;

    //convert distance to step
    stepsToTurn = distanceToStep(distance);

    stepper.step(stepsToTurn);

    printVal(pingTime, distance, stepsToTurn);

    currentStep += stepsToTurn;
    prevDistance = distance;

   // Serial.print(pingTime, 9);
    //Serial.print("\n");
   // Serial.print(distance, 9);
   // Serial.print("\n");

  }

  else {
    stepper.step(currentStep); //turn stepper back to infinity
  }

  delay(10000); //pause system for 5ms, to reduce computing pressure *needs fabricating*

}
