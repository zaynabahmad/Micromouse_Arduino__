
#include "Floodfill.h"
#include"UltraSonic_Sensor.h"
#include "motors.h"
#include "config.h"

// Maze array 
byte maze[MAZE_WIDTH][MAZE_HEIGHT];

// innitialize currunt position 
byte currentX = 0;   
byte currentY = 0;

//global variables 
extern "C" char* sbrk(int incr); // for function free memory


int main (){
  //setup 
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(MOTOR_PIN3, OUTPUT);
  pinMode(MOTOR_PIN4, OUTPUT);

  pinMode(TRIGGER_PIN1, OUTPUT);
  pinMode(TRIGGER_PIN2, OUTPUT);
  pinMode(TRIGGER_PIN3, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);
  pinMode(ECHO_PIN2, INPUT);
  pinMode(ECHO_PIN3, INPUT);

  /* Initialize the maze*/
  initializeMaze();
  
  /* Start flood fill algorithm*/
  floodFill(0, 0, 0);
  freeMemory();


while (1) {
  /* Move forward if there is no wall ahead*/
  if (maze[currentX][currentY + 1] == maze[currentX][currentY] - 1) {
    moveForward();
    currentY++;
  }
  /* Turn right if there is no wall on the right*/
  else if (maze[currentX + 1][currentY] == maze[currentX][currentY] - 1) {
    turnRight();
    currentX++;
  }
  /* Turn left if there is no wall on the left*/
  else if (maze[currentX - 1][currentY] == maze[currentX][currentY] - 1) {
    turnLeft();
    currentX--;
  }
  /* Turn around if there is no other option*/
  else {
    turnRight();
    turnRight();
    currentX--;
  }
}
}

int freeMemory() {
  char top;
  return &top - reinterpret_cast<char*>(sbrk(0));
}




