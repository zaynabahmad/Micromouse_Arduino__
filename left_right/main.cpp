#include <stdbool.h>
#include "config.h"
#include "sensors.h"
#include <Stack.h> // Include the Arduino Stack library for managing movement history

Stack<int> movementHistory; 



bool rightWallFollower = false;
bool leftWallFollower = false;

// Initialize encoder variables
volatile long leftEncoderCount = 0;
volatile long rightEncoderCount = 0;

void setup() {
  // Initialize ultrasonic sensors
  pinMode(FRONT_SENSOR_TRIG, OUTPUT);
  pinMode(FRONT_SENSOR_ECHO, INPUT);
  pinMode(LEFT_SENSOR_TRIG, OUTPUT);
  pinMode(LEFT_SENSOR_ECHO, INPUT);
  pinMode(RIGHT_SENSOR_TRIG, OUTPUT);
  pinMode(RIGHT_SENSOR_ECHO, INPUT);
  
  // Initialize motor driver pins
  pinMode(MOTOR_A1, OUTPUT);
  pinMode(MOTOR_A2, OUTPUT);
  pinMode(MOTOR_B1, OUTPUT);
  pinMode(MOTOR_B2, OUTPUT);
  
  // Attach interrupts for encoder counting
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER_A), leftEncoderISR, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER_A), rightEncoderISR, RISING);
  
  // Initialize the switch pin
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  

}

void loop() {
  // Read the switch state
  /*if (digitalRead(SWITCH_PIN) == LOW) {
    leftWallFollower = false;
    rightWallFollower = true;
  } else {
    leftWallFollower = true;
    rightWallFollower = false;
  }*/
  
  // Read ultrasonic sensor values
  /*int frontDistance = readUltrasonic(FRONT_SENSOR_TRIG, FRONT_SENSOR_ECHO);
  int leftDistance = readUltrasonic(LEFT_SENSOR_TRIG, LEFT_SENSOR_ECHO);
  int rightDistance = readUltrasonic(RIGHT_SENSOR_TRIG, RIGHT_SENSOR_ECHO);
  */
  // Implement the left wall follower or right wall follower algorithm
  if (leftWallFollower) {
    // Implement left wall following logic here
    // Adjust motor speeds and servo angle as needed
  } else if (rightWallFollower) {
    // If there is an opening on the right, turn right
     if (rightDistance > MIN_RIGHT_DISTANCE) {
      turnRight();
      movementHistory.push(2); // Push the movement direction (2 = right) to the stack
    }
    // If there is a wall in front, turn left
    else if (frontDistance < MIN_FRONT_DISTANCE) {
      turnLeft();
      movementHistory.push(3); // Push the movement direction (3 = left) to the stack
    }
    // If there is no wall in front or on the right, move forward
    else {
     // forward 
      movementHistory.push(1); // Push the movement direction (1 = forward) to the stack
    }
    // Check if you have reached the goal (center of the maze)
    if (atGoal()) {
      // Implement logic to indicate success and stop the robot
      // You might flash LEDs or make a sound, then halt the motors
      
      break;
  }

  }


}

int readUltrasonic(int trigPin, int echoPin) {
  // Implement ultrasonic sensor reading logic here
  // Calculate and return the distance
}

void leftEncoderISR() {
  // Increment left encoder count
  leftEncoderCount++;
}

void rightEncoderISR() {
  // Increment right encoder count
  rightEncoderCount++;
}


void backtrack() {
  // Pop the last movement direction from the stack
  turnLeft();
  turnLeft();
  int lastMovement = movementHistory.pop();

  // Perform the reverse movement to backtrack
  if (lastMovement == 1) { // Forward
    // Implement logic to move backward
  } else if (lastMovement == 2) { // Right
    turnLeft(); // Reverse the last right turn by making a left turn
  } else if (lastMovement == 3) { // Left
    turnRight(); // Reverse the last left turn by making a right turn
  }
}