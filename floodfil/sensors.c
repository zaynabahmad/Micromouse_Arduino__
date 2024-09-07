// sketch for the encoder rotary one 

#include "sensors.h"




/*int availableMemory() {
    // Use 1024 with ATmega168
    int size = 2048;
    byte *buf;
    while ((buf = (byte *) malloc(--size)) == NULL);
        free(buf);
    return size;
}*/


// Define orientation constants
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

// Initialize orientation
int orientation = NORTH;
int ForwardThreshold=20;
int RightThreshold=20;
int LeftThreshold=20;




void setup() {
    // for encoders 
    pinMode(leftEncoderPinA,INPUT);
    pinMode(leftEncodertPinB,INPUT);
    pinMode(rightEncoderPinB,INPUT);
    pinMode(rightEncoderPinB,INPUT);

    attachInterrupt(digitalPinToInterrupt(leftEncoderPinA,leftEncoderHandler,CHANGE));
    attachInterrupt(digitalPinToInterrupt(leftEncoderPinA,leftEncoderHandler,CHANGE));
    attachInterrupt(digitalPinToInterrupt(leftEncoderPinA,rightEncoderHandler,CHANGE));
    attachInterrupt(digitalPinToInterrupt(leftEncoderPinA,rightEncoderHandler,CHANGE));


    // for motors 
    pinMode(motor1Dir1,OUTPUT);
    pinMode(motor1Dir2,OUTPUT);
    pinMode(motor2Dir1,OUTPUT);
    pinMode(motor2Dir2,OUTPUT);
    pinMode(motor1PWM,OUTPUT);
    pinMode(motor2PWM,OUTPUT);

    // for ultrasonic 






}

void loop() { 
    // to count the distance continiously 
     // float leftDistance = (leftEncoderCount / countsPerRevelotion) * (2 * PI *wheelRadius );
     // float rightDistance = (rightEncoderCount / countsPerRevelotion) * (2 * PI *wheelRadius );



  
  
   
  }
  


// the ISR  for the encoder 
void handleEncoder() {
  int newEncoderAState = digitalRead(encoderPinA);
  int newEncoderBState = digitalRead(encoderPinB);

  if (newEncoderAState != lastEncoderAState) {
    if (newEncoderBState != newEncoderAState) {
      encoderPos++;
    } else {
      encoderPos--;
    }
  }

  lastEncoderAState = newEncoderAState;
}

void rotateForward()
{
  // make the motors rotate to move forward 
          digitalWrite(motor1Dir1, HIGH);
          digitalWrite(motor1Dir2, LOW);
          digitalWrite(motor2Dir1, HIGH);
          digitalWrite(motor2Dir2, LOW);
}

// for motors 
void moveForward() {
  /* Move the robot forward*/



  switch (orientation) {
        case NORTH:
            // Move forward in the north direction (Y++)
            rotateForward();
            
            break;
        case EAST:
            // Turn left (change orientation) and move forward
            turnLeft();
            rotateForward();
            orientation=NORTH;

            break;
        case SOUTH:
            // Turn around (change orientation) and move forward
            rotate180();
            rotateForward();
            orientation=NORTH;
            
           
            break;
        case WEST:
            // Turn right (change orientation) and move forward
            turnRight();
            rotateForward();
            orientation=NORTH;
            
            
            break;
        default:
            // Handle other orientations (if needed)
            break;
    }
  


}
void rotateRight()
{
  digitalWrite(motor1Dir1, LOW);
  digitalWrite(motor1Dir2, HIGH);
  digitalWrite(motor2Dir1, HIGH);
  digitalWrite(motor2Dir2, LOW);
}

void turnRight() {
  /* Turn the robot right*/
  switch (orientation) {

    case NORTH:
      // turn right directly (x++)
      rotateRight();
      rotateForward();
      orientation=EAST;

    case EAST:
      // move forward directly (x++)   
      rotateForward();



    case WEST:
      // turn right directly (x++)
    
      rotate180();
      rotateForward();
      orientation=EAST;


  
  }
  
}

void rotateLeft()
{
  digitalWrite(motor1Dir1, HIGH);
  digitalWrite(motor1Dir2, LOW);
  digitalWrite(motor2Dir1, LOW);
  digitalWrite(motor2Dir2, HIGH);
}

void turnLeft() {
  /* Turn the robot left*/

   switch (orientation) {

    case NORTH:
      // turn right directly (x--)
      rotateLeft();
      rotateForward();
      orientation=WEST;

    case WEST:
      // move forward directly (x--)   
      rotateForward();



    case EAST:
      // turn right directly (x--)
    
      rotate180();
      rotateForward();
      orientation=WEST;


  
  }



  
}

void stopMotor()
{
  digitalWrite(motor1Dir1, LOW);
  digitalWrite(motor1Dir2, LOW);
  digitalWrite(motor2Dir1, LOW);
  digitalWrite(motor2Dir2, LOW);
}

void setMotorSpeeds(int speed1, int speed2) {
  // Function to set motor speeds
  // Adjust motor control logic based on your motor driver configuration
  analogWrite(motor1PWM, speed1);
  digitalWrite(motor1Dir1, HIGH);
  digitalWrite(motor1Dir2, LOW);

  analogWrite(motor2PWM, speed2);
  digitalWrite(motor2Dir1, HIGH);
  digitalWrite(motor2Dir2, LOW);
}


// for ultrasonic 

float getDistance(TRIGGER_PIN, ECHO_PIN) {

    delayMicroseconds(2);
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);

   long duration =pulseIn(ECHO_PIN,HIGH);

   long distance =(duration /2) /29.1;

    return distance;
}


