
#define ir_sensor_Front 22
#define ir_sensor_Right 22
#define ir_sensor_Left 22
void setup() {
 // setup code for the ir code 

 pinMode (ir_sensor_Front,INPUT);
 pinMode (ir_sensor_Right,INPUT);
 pinMode (ir_sensor_Left,INPUT);

 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // 0 when there is a wall and 1 when no wall 

  if (!digitalRead(ir_sensor_Front)){Serial.println("wall forward");}
  if (!digitalRead(ir_sensor_Right)){Serial.println("wall right");}
  if (!digitalRead(ir_sensor_Left)){Serial.println("wall left");}

  
  

}
