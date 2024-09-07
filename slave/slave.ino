#include <Stepper.h>
 
// Define Constants
 
// Number of steps per internal motor revolution 
const float STEPS_PER_REV = 32; 
 
//  Amount of Gear Reduction
const float GEAR_RED = 64;
 
// Number of steps per geared output rotation
const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED;
 
// Define Variables
 
// Number of Steps Required
int StepsRequired;
 
// Create Instance of Stepper Class
// Specify Pins used for motor coils
// The pins used are 8,9,10,11 
// Connected to ULN2003 Motor Driver In1, In2, In3, In4 
// Pins entered in sequence 1-3-2-4 for proper step sequencing
 
Stepper steppermotor(STEPS_PER_REV, 6, 7, 8,9);
 
void setup()
{
  while (!Serial);
  Serial.begin(9600);

}
 
void loop()
{
while (Serial.available())
 {
 char Direction=Serial.read();
Serial.println(Direction);
   while(Direction=='R'||Direction=='V'||Direction=='S'){
   if (Direction=='R')
  {
 //Serial.println(" CW");
    StepsRequired  =  STEPS_PER_OUT_REV ; 
    steppermotor.setSpeed(700);   
    steppermotor.step(StepsRequired);
  }

  if (Direction== 'V')
  {
 //Serial.println("CCW");
  // Rotate CCW 1/2 turn quickly
  StepsRequired  =  - STEPS_PER_OUT_REV*2;  
  steppermotor.setSpeed(700);  
  steppermotor.step(StepsRequired);
 
}
 if (Direction== 'S')
 {
 //Serial.println("Stop");
  StepsRequired  =  0;  
  steppermotor.setSpeed(700);  
  steppermotor.step(StepsRequired);

 
}

 }
 }}
