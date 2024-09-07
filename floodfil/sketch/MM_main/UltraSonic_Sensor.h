#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_

/*Ultrasonic sensor pins*/
#define TRIGGER_PIN1 2
#define ECHO_PIN1 3
#define TRIGGER_PIN2 4
#define ECHO_PIN2 5
#define TRIGGER_PIN3 6
#define ECHO_PIN3 7

float getDistance(char TRIGGER_PIN,char ECHO_PIN);

#endif // _ULTRASONIC_H_