#define ledpin A1
#define buttonpin A3




void setup(){
  pinMode(ledpin, OUTPUT);
  pinMode(buttonpin,INPUT_PULLUP);
  

  Serial.begin(9600);

}



void loop(){
  char zar=digitalRead(buttonpin);
  if (zar==1)
  digitalWrite(ledpin,HIGH);
 
 

  
  

  


}
