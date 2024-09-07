/*
* encoder test for the speed and distance in cm 
*  
*
*
*/




#define encoderLeft 2  // Left motor encoder pin
#define encoderRight 3 // Right motor encoder pin

unsigned int rpmLeft;
unsigned int rpmRight;
volatile byte pulsesLeft;
volatile byte pulsesRight;
unsigned long TIME;
unsigned int pulse_per_turn = 20; // Depends on the number of slots on the slotted disc
float wheel_circumference = 20.0; // 2*pi*radius

// calculating the number of pulses 

void countLeft() {
  
  pulsesLeft++;
}

void countRight() {
  
  pulsesRight++;
}



void setup() {
  // Reset all to 0
  rpmLeft = 0;
  rpmRight = 0;
  pulsesLeft = 0;
  pulsesRight = 0;
  TIME = 0;

  Serial.begin(9600);
  pinMode(encoderLeft, INPUT);  
  pinMode(encoderRight, INPUT); 
  // Triggering count function for left motor encoder every time it turns from HIGH to LOW
  attachInterrupt(digitalPinToInterrupt(encoderLeft), countLeft, FALLING);
  // Triggering count function for right motor encoder every time it turns from HIGH to LOW
  attachInterrupt(digitalPinToInterrupt(encoderRight), countRight, FALLING);
}


float calculateSpeedLeft() {
  // Calculate speed for the left motor in cm/s
  return (rpmLeft * wheel_circumference) / 6000.0; // RPM to cm/s conversion
}

float calculateSpeedRight() {
  // Calculate speed for the right motor in cm/s
  return (rpmRight * wheel_circumference) / 6000.0; // RPM to cm/s conversion
}

float calculateDistanceLeft() {
  // Calculate distance traveled for the left motor in cm
  return (pulsesLeft * wheel_circumference) / pulse_per_turn;
}

float calculateDistanceRight() {
  // Calculate distance traveled for the right motor in cm
  return (pulsesRight * wheel_circumference) / pulse_per_turn;
}

void loop() {
  if (millis() - TIME >= 100) { // checks every 0.1 seconds 
    detachInterrupt(digitalPinToInterrupt(encoderLeft));  // Turn off left motor encoder trigger
    detachInterrupt(digitalPinToInterrupt(encoderRight)); // Turn off right motor encoder trigger
    // Calculate RPM for both motors
    rpmLeft = (60 * 100 / pulse_per_turn) / (millis() - TIME) * pulsesLeft;
    rpmRight = (60 * 100 / pulse_per_turn) / (millis() - TIME) * pulsesRight;

    TIME = millis();
    pulsesLeft = 0;
    pulsesRight = 0;
    // Print output for left motor
    Serial.print("Left Motor RPM: ");
    Serial.println(rpmLeft);
    Serial.print("Left Motor Speed (cm/s): ");
    Serial.println(calculateSpeedLeft());
    Serial.print("Left Motor Distance (cm): ");
    Serial.println(calculateDistanceLeft());

    // Print output for right motor
    Serial.print("Right Motor RPM: ");
    Serial.println(rpmRight);
    Serial.print("Right Motor Speed (cm/s): ");
    Serial.println(calculateSpeedRight());
    Serial.print("Right Motor Distance (cm): ");
    Serial.println(calculateDistanceRight());

    // Trigger count function for both encoders every time they turn from HIGH to LOW
    attachInterrupt(digitalPinToInterrupt(encoderLeft), countLeft, FALLING);
    attachInterrupt(digitalPinToInterrupt(encoderRight), countRight, FALLING);
  }
}
