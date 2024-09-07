

void moveForward() {
  /* Move the robot forward*/
  digitalWrite(MOTOR_PIN1, HIGH);
  digitalWrite(MOTOR_PIN2, LOW);
  digitalWrite(MOTOR_PIN3, HIGH);
  digitalWrite(MOTOR_PIN4, LOW);
  
  /* Delay to allow the robot to move*/
  delay(1000);
  
  /* Stop the robot*/
  digitalWrite(MOTOR_PIN1, LOW);
  digitalWrite(MOTOR_PIN2, LOW);
  digitalWrite(MOTOR_PIN3, LOW);
  digitalWrite(MOTOR_PIN4, LOW);
}

void turnRight() {
  /* Turn the robot right*/
  digitalWrite(MOTOR_PIN1, LOW);
  digitalWrite(MOTOR_PIN2, HIGH);
  digitalWrite(MOTOR_PIN3, HIGH);
  digitalWrite(MOTOR_PIN4, LOW);
  
  /* Delay to allow the robot to turn*/
  delay(500);
  
  /* Stop the robot*/
  digitalWrite(MOTOR_PIN1, LOW);
  digitalWrite(MOTOR_PIN2, LOW);
  digitalWrite(MOTOR_PIN3, LOW);
  digitalWrite(MOTOR_PIN4, LOW);
}

void turnLeft() {
  /* Turn the robot left*/
  digitalWrite(MOTOR_PIN1, HIGH);
  digitalWrite(MOTOR_PIN2, LOW);
  digitalWrite(MOTOR_PIN3, LOW);
  digitalWrite(MOTOR_PIN4, HIGH);
  
  /*Delay to allow the robot to turn*/
  delay(500);
  
  /* Stop the robot*/
  digitalWrite(MOTOR_PIN1, LOW);
  digitalWrite(MOTOR_PIN2, LOW);
  digitalWrite(MOTOR_PIN3, LOW);
  digitalWrite(MOTOR_PIN4, LOW);
}