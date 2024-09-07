/*
*  a code to test the motors 
*
*
*/
#define Motor1A 22
#define Motor1B 22
#define Motor2A 22
#define Motor2B 22
 
void setup() {

  pinMode (Motor1A, OUTPUT);
  pinMode (Motor1B, OUTPUT);
  pinMode (Motor2A, OUTPUT);
  pinMode (Motor2B, OUTPUT);

  
  

}

void loop() {

  // MOVE FORWARD FOR 2 MINUTES 
  moveForward();
  delay(2000);
  // THEN RIGHT FOR TWO MINUTES 
  moveRight();
  delay(2000);
  // THEN LEFT FOR TWO MINUTES 
  moveLeft();
  delay(2000); 
  
}

void moveForward()
{
  digitalWrite(Motor1A,HIGH);
  digitalWrite(Motor1A,LOW);
  digitalWrite(Motor1A,HIGH);
  digitalWrite(Motor1A,LOW);
  
}

void moveRight()
{
  digitalWrite(Motor1A,HIGH);
  digitalWrite(Motor1A,LOW);
  digitalWrite(Motor1A,LOW);
  digitalWrite(Motor1A,LOW);
}

void moveLeft()
{
  digitalWrite(Motor1A,LOW);
  digitalWrite(Motor1A,LOW);
  digitalWrite(Motor1A,HIGH);
  digitalWrite(Motor1A,LOW);
}
