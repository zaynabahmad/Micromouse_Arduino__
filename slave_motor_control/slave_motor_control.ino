#include <Stepper.h>
#include "Liquid_Crystal.h"
#include <LiquidCrystal.h>
#define outputA 3
#define outputB 4

//for encoder:
LiquidCrystal_I2C lcd (0x27, 16,2);
 
int counter = 0;
int currentStateA;
int lastStateA;
String currentDir ="";

// -----------
 
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
  pinMode(outputA,INPUT);
  pinMode(outputB,INPUT);
  lcd. init ();
// Turn on the backlight on LCD. 
  lcd. backlight ();
  lcd.print ("CIRCUITSCHOOLS..");
  lcd. setCursor (0, 1);
  lcd.print ("ROTARY ENCODER");
  
delay(2000);
lcd.clear();
     lcd.setCursor(0, 0);
lcd.print("Rotate the knob");
  // Read the initial state of outputA
  lastStateA = digitalRead(outputA);

}
 
void loop()
{
while (Serial.available())
 {
 char Direction=Serial.read();
Serial.println(Direction);
   //while(Direction=='R'||Direction=='V'||Direction=='S'){
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
 // Read the current state of outputA
  currentStateA = digitalRead(outputA);
 
 
  // If last and current state of outputA are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateA != lastStateA  && currentStateA == 1){
 
    // If the outputB state is different than the outputA state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(outputB) != currentStateA) {
      counter ++;
      currentDir ="CW";
    } else {
      // Encoder is rotating CW so increment
      counter --;
      currentDir ="ACW";
    }
 
    Serial.print("Direction: ");
    Serial.print(currentDir);
    Serial.print(" | Counter: ");
    Serial.println(counter);
lcd.clear();
    lcd.setCursor(0, 0);
lcd.print("Position: ");
lcd.setCursor(10, 0);
lcd.print(counter);
lcd.setCursor(0, 1);
lcd.print("Dir: ");
lcd.setCursor(5, 1);
lcd.print(currentDir);
  }
 
  // Remember last outputA state
  lastStateA = currentStateA;
 
  // Put in a slight delay to help debounce the reading
  delay(1);

 }
