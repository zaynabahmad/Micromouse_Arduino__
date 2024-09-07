const int lm35Vout=1;
#define LED A0
const byte degreeSymbol="B11011111";

#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);



void setup() 
{
    pinMode(LED,HIGH);
    lcd.begin(16,2);
    Serial.begin(9600);

}
void loop() 
{
    long degree;
    degree=lm35(lm35Vout);
    Serial.print("degrees Celsius = ");
    Serial.print(degree);
    Serial.println("c");
    lcd.setCursor(0,0);
    lcd.print(degree);
    lcd.print(degreeSymbol);
    lcd.print("C");
    delay(1000);

}
long lm35(int lm35Vout)
{
  int value;
  long degree;
  value=analogRead(lm35Vout);     
  degree=(long)value*500/1024;
    if(degree>=90){
      digitalWrite(LED,HIGH);
    }
  return degree;
}