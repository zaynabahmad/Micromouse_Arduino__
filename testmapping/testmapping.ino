#include "DIO.h"
void setup(){
  pinMode(7 ,OUTPUT);
  //Set_PinDirection (PORT_D , Pin_7,Output);
  Set_PinDirection (PORT_D , Pin_6,Output);

}
void loop(){
    
   Set_PinValue (PORT_D , Pin_7 , HIGH);
    //digitalWrite(Pin_7 ,HIGH);
    digitalWrite(Pin_6 ,HIGH);
    




  }




