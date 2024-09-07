#ifndef A3338D83_4C40_47D2_983E_E450D69119A0
#define A3338D83_4C40_47D2_983E_E450D69119A0



// Pin configuration
const int leftEncoderPinA = 2; // Phase A pin for encoder 1
const int leftEncodertPinB = 3; // Phase B pin for encoder 1 
const int rightEncoderPinA = 3; // Phase B pin for encoder 1 
const int rightEncoderPinB = 3; // Phase B pin for encoder 1 




// Variables for encoder 
volatile long leftEncoderCount= 0;  // to track the number of counts  for the left encoder 
volatile long rightEncoderCount= 0;  // to track the number of counts for the rigth encoder 


const float wheelRadius = 1.0;
const float countsPerRevelotion =360.0;


// pins configration for motors 
const int motor1PWM = 3;   // Motor 1 Speed Control (PWM)
const int motor1Dir1 = 4;  // Motor 1 Direction Control 1
const int motor1Dir2 = 5;  // Motor 1 Direction Control 2
const int motor2PWM = 6;   // Motor 2 Speed Control (PWM)
const int motor2Dir1 = 7;  // Motor 2 Direction Control 1
const int motor2Dir2 = 9;  // Motor 2 Direction Control 2


// pins configration for ultrasonic 

#define TRIGGER_PIN_sensor1 4
#define ECHO_PIN_sensor1 5
#define TRIGGER_PIN_sensor2 4
#define ECHO_PIN_sensor2 5
#define TRIGGER_PIN_sensor3 4
#define ECHO_PIN_sensor3 5









#endif /* A3338D83_4C40_47D2_983E_E450D69119A0 */
