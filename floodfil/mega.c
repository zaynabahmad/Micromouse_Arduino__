#include <NewPing.h>
/*Ultrasonic sensor pins*/
#define TRIGGER_PIN1 2
#define ECHO_PIN1 3
#define TRIGGER_PIN2 4
#define ECHO_PIN2 5
#define TRIGGER_PIN3 6
#define ECHO_PIN3 7

/*Motor control pins*/
#define MOTOR_PIN1 8
#define MOTOR_PIN2 9
#define MOTOR_PIN3 10
#define MOTOR_PIN4 11

/*Constants for maze dimensions*/
#define MAZE_WIDTH 18
#define MAZE_HEIGHT 18
/*constant for robot dimensions*/
#define Robot_width 11

/* Constants for flood fill algorithm*/
#define UNEXPLORED 255
#define WALL 254

/* Maze array*/
byte maze[MAZE_WIDTH][MAZE_HEIGHT];

/*Initialize ultrasonic sensors*/
NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1);
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2);
NewPing sonar3(TRIGGER_PIN3, ECHO_PIN3);

/*Initialize current position*/
byte currentX = 0;
byte currentY = 0;

/*Function prototypes*/
void initializeMaze();
void floodFill(byte x, byte y, byte distance);
void moveForward();
void turnRight();
void turnLeft();

//function to know the free mwmory in the arduino 
extern "C" char* sbrk(int incr);

int freeMemory() {
  char top;
  return &top - reinterpret_cast<char*>(sbrk(0));
}
//---------------------

void setup() {
  /*/ Initialize motor control pins as outputs*/
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(MOTOR_PIN3, OUTPUT);
  pinMode(MOTOR_PIN4, OUTPUT);

  /* Initialize the maze*/
  initializeMaze();
  
  /* Start flood fill algorithm*/
  floodFill(0, 0, 0);
}

void loop() {
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

void initializeMaze() {
  /* Set all cells in the maze to unexplored*/
  for (byte x = 0; x < MAZE_WIDTH; x++) {
    for (byte y = 0; y < MAZE_HEIGHT; y++) {
      maze[x][y] = UNEXPLORED;
    }
  }
  
  /*Set walls on the outer edges of the maze*/
  for (byte x = 0; x < MAZE_WIDTH; x++) {
    maze[x][0] = WALL;
    maze[x][MAZE_HEIGHT - 1] = WALL;
  }
  for (byte y = 0; y < MAZE_HEIGHT; y++) {
    maze[0][y] = WALL;
    maze[MAZE_WIDTH - 1][y] = WALL;
  }
  
  /*Set current position to the starting cell*/
  currentX = 0;
  currentY = 0;
  
  /* Set starting cell as distance 0*/
  maze[currentX][currentY] = 0;
}

void floodFill(byte x, byte y, byte distance) {
  /* Check if the specified cell is valid and unexplored*/
  if (x >= 0 && x < MAZE_WIDTH && y >= 0 && y < MAZE_HEIGHT && maze[x][y] == UNEXPLORED) {
    /*Set the distance of the cell*/
    maze[x][y] = distance;
    
    /* Recursively call floodFill for neighboring cells*/
    floodFill(x + 1, y, distance + 1);
    floodFill(x - 1, y, distance + 1);
    floodFill(x, y + 1, distance + 1);
    floodFill(x, y - 1, distance + 1);
  }
}

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