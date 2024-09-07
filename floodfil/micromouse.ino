

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
//#include <SoftwareSerial.h>



// Pin configuration
/*const int leftEncoderPinA = 2; // Phase A pin for encoder 1
const int leftEncodertPinB = 3; // Phase B pin for encoder 1 
const int rightEncoderPinA = 3; // Phase B pin for encoder 1 
const int rightEncoderPinB = 3; // Phase B pin for encoder 1 
*/
// Variables for encoder 
volatile long leftEncoderCount= 0;  // to track the number of counts  for the left encoder 
volatile long rightEncoderCount= 0;  // to track the number of counts for the rigth encoder 


const float wheelRadius = 1.0;
const float countsPerRevelotion =360.0;


// pins configration for motors 
const int motor1PWM = 13;   // Motor 1 Speed Control (PWM)
const int motor1Dir1 = 9;  // Motor 1 Direction Control 1
const int motor1Dir2 = 10;  // Motor 1 Direction Control 2
const int motor2PWM = 12;   // Motor 2 Speed Control (PWM)
const int motor2Dir1 = 68;  // Motor 2 Direction Control 1
const int motor2Dir2 = 69;  // Motor 2 Direction Control 2


// pins configration for ultrasonic 

//#define TRIGGER_PIN_sensor1 28 // f
#define ECHO_PIN_sensor1 26
#define TRIGGER_PIN_sensor2 54   // r  //A0
#define ECHO_PIN_sensor2 55    // A1
#define TRIGGER_PIN_sensor3 22  // l
#define ECHO_PIN_sensor3 24


// config 

typedef struct point
{
    int x, y;
} POINT;

#define MAZE_WEDTH 16
#define MAZE_HEIGHT 16
#define MAZE_GOAL_X 8
#define MAZE_GOAL_Y 8


// srnsors .h 
// Define orientation constants
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

// Initialize orientation
int orientation = NORTH;
int ForwardThreshold=20;
int RightThreshold=20;
int LeftThreshold=20;

// ir_sensor

#define IR_sensor 28




// queue 

   #define QueueEntry POINT

    typedef struct queueNode {
        QueueEntry entry;
        struct queueNode *next;
    } QueueNode;

    typedef struct queue {
        QueueNode *front;
        QueueNode *rear;
        int size;
    } Queue;




// global variable 

int Distance[MAZE_WEDTH][MAZE_HEIGHT]={0};
//int WALLS [MAZE_WEDTH][MAZE_HEIGHT]={0};
#define MAX_NEIGHBORS 4

 // main before the loop 
    POINT start ={0,0};     
    POINT *nextcell= malloc(sizeof(POINT));    
  

// for test 

// for bluetooth 
//SoftwareSerial mine(0,1);

void setup()
{
    /*pinMode(leftEncoderPinA,INPUT);
    pinMode(leftEncodertPinB,INPUT);
    pinMode(rightEncoderPinB,INPUT);
    pinMode(rightEncoderPinB,INPUT);*/

    //attachInterrupt(digitalPinToInterrupt(leftEncoderPinA,leftEncoderHandler,CHANGE));
    //attachInterrupt(digitalPinToInterrupt(leftEncoderPinA,leftEncoderHandler,CHANGE));
    //attachInterrupt(digitalPinToInterrupt(leftEncoderPinA,rightEncoderHandler,CHANGE));
    //attachInterrupt(digitalPinToInterrupt(leftEncoderPinA,rightEncoderHandler,CHANGE));


    // for motors 
    pinMode(motor1Dir1,OUTPUT);
    pinMode(motor1Dir2,OUTPUT);
    pinMode(motor2Dir1,OUTPUT);
    pinMode(motor2Dir2,OUTPUT);
    pinMode(motor1PWM,OUTPUT);
    pinMode(motor2PWM,OUTPUT);

    // for ultrasonic 
   // pinMode(TRIGGER_PIN_sensor1,OUTPUT);
    pinMode(ECHO_PIN_sensor1,INPUT);
    pinMode(TRIGGER_PIN_sensor2,OUTPUT);
    pinMode(ECHO_PIN_sensor2,INPUT);
    pinMode(TRIGGER_PIN_sensor3,OUTPUT);
    pinMode(ECHO_PIN_sensor3,INPUT);

    // IR 
    pinMode(IR_sensor,INPUT);

  

    nextcell->x=-1;     
    nextcell->y=-1;
    digitalWrite(motor1PWM,HIGH);
    digitalWrite(motor2PWM,HIGH);
    //Serial.begin(9600);
    //mine.begin(9600);
    
    setMotorSpeeds(166,120);


  Serial.begin(9600);

     
}
    void loop ()
    {
      //mine.println("hereeee");
      

      /*if(wallForward())
      {
        Serial.println("wall Forward");
      }
      if(wallRight())
      {
        Serial.println("wall Right");
      }
      if(wallLeft())
      {
        Serial.println("wall Left");
      }*/

     // rotateForward();
      /*delay(1000);
rotateRight();
delay(1000);
rotateLeft();
delay(1000);
*/



/*while (!wallForward())
{
  rotateForward();

  
}
if(wallRight())
{
  rotateRight();
}
else if(wallLeft())
rotateLeft();

else {
  rotate180();
}
*/



       

      //mySerial.write("the front distance is ");
      //mySerial.print(distance);
      //delay(500);

    
      //turnRight();
     // turnLeft();
  //mine.println("get into the main loop ");
  
        if (start.x == MAZE_GOAL_X && start.y == MAZE_GOAL_Y) {
        //printf("Cell (%d, %d) is the maze goal: the robot has reached the goal\n", start.x, start.y);
    //    mine.println("the robot has reached the goal should stop");
        stopMotor();
        delay(5000);
        return 0; // The robot has reached the goal, stop.
        }
        
      // check the next move if it is valid 
      if (nextmove(start,nextcell))
      {
        //log1("the next move is valid without floodfil ");
      //  mine.print("the nextmove is ");
       // mine.println(nextcell->x);
        //mine.println(nextcell->y);

         
        //printf("the next move is %d %d ", nextcell->x ,nextcell->y);  // to print the next move 
         // until here all thing is good 
        // move to the next cell 
        if ((nextcell->x)==((start.x )+1) && (nextcell->y) ==(start.y))
        {
            // move right  
          //  log1("move right");  // to ensure that it should turn right  
        //  mine.println("the robot should move in the right direction ");
            turnRight();      // replace this with turn right with code of the motor (call of the function  )
            start.x++;   // update the data that the robot has moved right (use the encoder )
        }

        else if ((nextcell->x)==(start.x -1) && (nextcell->y) == (start.y))
        {
            // move left 
           // log1("move left"); // to ensure that it shout turn left 
          // mine.println("the robot should move in the left direction ");
            turnLeft();  // replace this with the code of the motor  (call of the function )
            start.x--;  // update the data that the robot has moved left (use the encoder )
        }

        else if ((nextcell->x)==(start.x ) && (nextcell->y) == ((start.y)+1))
        {
            // move straight
            //log1("move forward"); // to ensure that it should move forward 

            moveForward();  // replace this with the code of the motor (call of the function )
            //mine.println("it should move straight");
            
            

            start.y++;  // update the data that the robot has moved forwared (use the encoder )
        }

        else {
              //  mine.println("should backtrack ");
                stopMotor();
                delay(5000);
                return 0 ;
                // backtrack  (the algorithim with use all the function of the motors )
        }
      }
      
      else {
        
        // floodfil
        //mine.println("should perform floodfil now");
        floodFil(start);
        //printf("go to th flood fill for the cell %d ,%d",start.x, start.y);   // all printfs we could use the serial monitor 
      
      }
    
    free(nextcell);
    
   
  
    
}



//function to calculate the manhaten distance  
int getManhatenDistance(int x1 ,int y1 , int x2 ,int y2)   // passed the test successfully 
{
    if(Distance[x1][y1]!=0) return Distance[x1][y1]; 
    else return abs(x1 - x2) + abs(y1 - y2);
}

// function to get the neighbores 
int getNeighbors(POINT point, POINT* result) {         // passed the test successfully 
    int resultCount = 0;

    // Define the four possible neighbor offsets
    int neighborOffsets[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (int i = 0; i < 4; i++) {
        POINT neighbor = {point.x + neighborOffsets[i][0], point.y + neighborOffsets[i][1]};
        if (isValid(neighbor)) {
            result[resultCount] = neighbor;
            (resultCount)++;
        }
    } return resultCount;
}

// function to obtain that this cell is valid in the maze 
bool isValid(POINT point) {       // passed
    // check if this cell is in the boundries 
    return (point.x >= 0 && point.x < MAZE_WEDTH && point.y >= 0 && point.y < MAZE_HEIGHT );
    
}

// function to get the cell the next cell if it is available 

bool nextmove(POINT current, POINT* nextmove) {
    bool flag = false;

    POINT result[MAX_NEIGHBORS];

    //getNeighbors(current, result);

    int leastdistance = getManhatenDistance(current.x, current.y, MAZE_GOAL_X, MAZE_GOAL_Y);
    
   

    for (int i = 0; i < (getNeighbors(current, result)); i++) {
        if (result[i].x == current.x + 1 && result[i].y == current.y) {   // the right cell
            if (!wallRight()) {
                if (getManhatenDistance(result[i].x, result[i].y, MAZE_GOAL_X, MAZE_GOAL_Y) < leastdistance) {
                    leastdistance = getManhatenDistance(result[i].x, result[i].y, MAZE_GOAL_X, MAZE_GOAL_Y);
                    nextmove->x = result[i].x;
                    nextmove->y = result[i].y;
                    flag =  true; // 
                }
            }
        }
        else if (result[i].x == current.x - 1 && result[i].y == current.y) {   // the left cell
            if (!wallLeft()) {
                if (getManhatenDistance(result[i].x, result[i].y, MAZE_GOAL_X, MAZE_GOAL_Y) < leastdistance) {
                    leastdistance = getManhatenDistance(result[i].x, result[i].y, MAZE_GOAL_X, MAZE_GOAL_Y);
                    nextmove->x = result[i].x;
                    nextmove->y = result[i].y;
                    flag = true;
                }
            }
        }
        else if (result[i].x == current.x && result[i].y == current.y + 1) {   // the forward cell
            if (!wallForward()) {
                if (getManhatenDistance(result[i].x, result[i].y, MAZE_GOAL_X, MAZE_GOAL_Y) < leastdistance) {
                    leastdistance = getManhatenDistance(result[i].x, result[i].y, MAZE_GOAL_X, MAZE_GOAL_Y);
                    nextmove->x = result[i].x;
                    nextmove->y = result[i].y;
                    flag = true;
                }
            }
        }

    }
    printf("flag : %d",flag);

    return flag;

}



// function for floodfil 
void floodFil(POINT current)
{
    // check if it is in the goal or not 
    if (current.x==MAZE_GOAL_X &&current.y==MAZE_GOAL_Y){
        // stop 
        // backtracking
        return;
    }
    // start the floodfil 
    Queue *queueCells =(Queue *)malloc(sizeof(Queue));
    CreateQueue( queueCells);
    Append(current,queueCells);
    int minimumValue;
    while (!QueueEmpty(queueCells))
    {
        POINT *outcellfromqueue= malloc(sizeof(POINT));
        serve(outcellfromqueue, queueCells);
        minimumValue=getMinimumvalueofNeighbor(*outcellfromqueue);
        if (minimumValue>=getManhatenDistance(outcellfromqueue->x,outcellfromqueue->y, MAZE_GOAL_X, MAZE_GOAL_Y))
        {
            Distance[outcellfromqueue->x][outcellfromqueue->y]=minimumValue+1;
            // adding all the neighbors in the queue
             POINT result[MAX_NEIGHBORS];
            int numNeighbors = getMinimumvalueofNeighbor(current);
            getNeighbors(*outcellfromqueue, result);

            printf("Adding neighbors of cell (%d, %d) to the queue:\n", outcellfromqueue->x, outcellfromqueue->y);
            for (int i = 0; i < numNeighbors; i++) {
                printf("  - Neighbor (%d, %d)\n", result[i].x, result[i].y);
                Append(result[i], queueCells);
            }
        }
            free(outcellfromqueue);
    }

    ClearQueue(queueCells);

}

// function to get the minimum value amongest neighbor using in floodfil 
int getMinimumvalueofNeighbor(POINT current)   //passed 
{
    POINT result[4];
    getNeighbors(current, result);
    int leastdistance=255;
    for (int i=0;i<4;i++)
    {
        if(getManhatenDistance(result[i].x, result[i].y, MAZE_GOAL_X, MAZE_GOAL_Y)<leastdistance)
        {
            leastdistance=getManhatenDistance(result[i].x, result[i].y, MAZE_GOAL_X, MAZE_GOAL_Y);
        }
        
    }

    return leastdistance;
}


/*int backTrack(POINT goal)
{
    POINT current = goal;
    int minDistance = Distance[goal.x][goal.y]; // Initialize minDistance to 0 (goal cell's Distance value)
    
    while (current.x != 0 && current.y != 0) { // Backtrack until you reach the starting point
        POINT result[MAX_NEIGHBORS];
        int numNeighbors = getNeighbors(current, result);
        POINT nextCell = current;

        for (int i = 0; i < numNeighbors; i++) {
            if (Distance[result[i].x][result[i].y] > minDistance) {
                minDistance = Distance[result[i].x][result[i].y];
                nextCell = result[i];
            }
        }


        // Move the robot to the next cell ()
        // Update the current position
        current = nextCell;

        if ((nextcell->x)==((start.x )+1) && (nextcell->y) ==(start.y))
        {
            // move right  
          //  log1("move right");  // to ensure that it should turn right  
            moveRight();      // replace this with turn right with code of the motor (call of the function  )
            start.x++;   // update the data that the robot has moved right (use the encoder )
        }

        else if ((nextcell->x)==(start.x -1) && (nextcell->y) == (start.y))
        {
            // move left 
            log1("move left"); // to ensure that it shout turn left 
            moveLeft();  // replace this with the code of the motor  (call of the function )
            start.x--;  // update the data that the robot has moved left (use the encoder )
        }

        else if ((nextcell->x)==(start.x ) && (nextcell->y) == ((start.y)+1))
        {
            // move straight
            //log1("move forward"); // to ensure that it should move forward 

            moveForward();  // replace this with the code of the motor (call of the function )
            
            

            start.y++;  // update the data that the robot has moved forwared (use the encoder )
        }
    }
}*/





int wallRight()
{   
    long distance =getDistance(TRIGGER_PIN_sensor2, ECHO_PIN_sensor2);
    if(distance>0&&distance<=RightThreshold) // right 
    return 1;
    else return 0;
}

int wallForward()
{

  if(digitalRead(IR_sensor))
  return 0;
  else return 1;

  /*long distance =getDistance(TRIGGER_PIN_sensor1, ECHO_PIN_sensor1);
    if(distance>0&&distance<=ForwardThreshold) */ // forward


}

int wallLeft()
{   
    long distance =getDistance(TRIGGER_PIN_sensor3, ECHO_PIN_sensor3);
    if(distance>0&&distance<=LeftThreshold) //left
    return 1;
    else return 0;

}

/*

    handling t junctione , deadends , cornersc , crossroads 

*/






// queue code


/**
 * Initializes the queue by setting its front and rear pointers and size to default values.
 *
 * @param pq pointer to the queue
 */
void CreateQueue(Queue *pq){
    pq->front=NULL;
    pq->rear=NULL;
    pq->size=0;

}

/**
 * Appends an element to the rear of the queue.
 *
 * @param e the element to be appended
 * @param pq pointer to the queue
 * @return 1 if the element is successfully appended, 0 otherwise
 */
int Append(QueueEntry e , Queue * pq){
    QueueNode *pn = (QueueNode *)malloc(sizeof( QueueNode));
    if (!pn)
        return 0;
    else {
    pn->next=NULL;
    pn->entry=e;
    if(!pq->rear)
      pq->front=pn;
      else
      {
        pq->rear->next =pn;
      }
      pq->rear=pn;
      pq->size++;
      return 1;
    }

}

/**
 * Removes the front element from the queue and assigns it to the given variable.
 *
 * @param pe pointer to the variable that will hold the removed element
 * @param pq pointer to the queue
 */
void serve (QueueEntry *pe, Queue * pq){
    QueueNode * pn = pq->front;
    *pe =pn->entry ;
    pq->front=pn->next;
    free(pn);
    if(!pq->front)
    pq->rear=NULL;
    pq->size--;


}

/**
 * Determines if the queue is empty.
 *
 * @param pq pointer to the queue
 * @return 1 if the queue is empty, 0 otherwise
 */
int QueueEmpty(Queue* pq){
    return !pq->front;
}


/**
 * Removes all elements from the queue.
 *
 * @param pq pointer to the queue
 * @return 1 if the queue is successfully cleared, 0 otherwise
 */
int ClearQueue (Queue *pq){    //again
    while (pq->front){
        pq->rear =pq->front->next;
        free(pq->front);
        pq->front=pq->rear;
    }
    pq->size =0;
    // Return 1 to indicate success
    return 1;
}


// the ISR  for the encoder 
/*void handleEncoder() {
  int newEncoderAState = digitalRead(encoderPinA);
  int newEncoderBState = digitalRead(encoderPinB);

  if (newEncoderAState != lastEncoderAState) {
    if (newEncoderBState != newEncoderAState) {
      encoderPos++;
    } else {
      encoderPos--;
    }
  }

  lastEncoderAState = newEncoderAState;
}*/

void rotateForward()
{
  // make the motors rotate to move forward 
          digitalWrite(motor1Dir1, HIGH);
          digitalWrite(motor1Dir2, LOW);
          digitalWrite(motor2Dir1, HIGH);
          digitalWrite(motor2Dir2, LOW);
          
        
  delay(400);

}

void rotateBack()
{
  // make the motors rotate to move forward 
          digitalWrite(motor1Dir1, LOW);
          digitalWrite(motor1Dir2, HIGH);
          digitalWrite(motor2Dir1, LOW);
          digitalWrite(motor2Dir2, HIGH);
          
        
  //delay(300);

}

// for motors 
void moveForward() {
  /* Move the robot forward*/



  switch (orientation) {
        case NORTH:
            // Move forward in the north direction (Y++)
            rotateForward();
            
            break;
        case EAST:
            // Turn left (change orientation) and move forward
            turnLeft();
            rotateForward();
            orientation=NORTH;

            break;
        case SOUTH:
            // Turn around (change orientation) and move forward
            rotate180();
            rotateForward();
            orientation=NORTH;
            
           
            break;
        case WEST:
            // Turn right (change orientation) and move forward
            turnRight();
            rotateForward();
            orientation=NORTH;
            
            
            break;
        default:
            // Handle other orientations (if needed)
            break;
    }
  


}
void rotateRight()
{
  digitalWrite(motor1Dir1, LOW);
  digitalWrite(motor1Dir2, HIGH);
  digitalWrite(motor2Dir1, HIGH);
  digitalWrite(motor2Dir2, LOW);
  delay(300);
  stopMotor();
  
}

void turnRight() {
  /* Turn the robot right*/
  switch (orientation) {

    case NORTH:
      // turn right directly (x++)
      rotateRight();
      rotateForward();
      orientation=EAST;

    case EAST:
      // move forward directly (x++)   
      rotateForward();



    case WEST:
      // turn right directly (x++)
    
      rotate180();
      rotateForward();
      orientation=EAST;


  
  }
  
}

void rotateLeft()
{
  digitalWrite(motor1Dir1, HIGH);
  digitalWrite(motor1Dir2, LOW);
  digitalWrite(motor2Dir1, LOW);
  digitalWrite(motor2Dir2, HIGH);
  delay(300);
  stopMotor();
  

}

void turnLeft() {
  /* Turn the robot left*/

   switch (orientation) {

    case NORTH:
      // turn right directly (x--)
      rotateLeft();
      rotateForward();
      orientation=WEST;

    case WEST:
      // move forward directly (x--)   
      rotateForward();



    case EAST:
      // turn right directly (x--)
    
      rotate180();
      rotateForward();
      orientation=WEST;


  
  }



  
}

void stopMotor()
{
  digitalWrite(motor1Dir1, LOW);
  digitalWrite(motor1Dir2, LOW);
  digitalWrite(motor2Dir1, LOW);
  digitalWrite(motor2Dir2, LOW);
  

}

void setMotorSpeeds(int speed1, int speed2) {
  // Function to set motor speeds
  // Adjust motor control logic based on your motor driver configuration
  analogWrite(motor1PWM, speed1);


  analogWrite(motor2PWM, speed2);

}

void rotate180()
{
  rotateRight();
  rotateRight();
  delay(20);

  
}


// for ultrasonic 

float getDistance(char TRIGGER_PIN, char ECHO_PIN) {

    delayMicroseconds(2);
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);

   long duration =pulseIn(ECHO_PIN,HIGH);

   long distance =(duration /2) /29.1;

    return distance;
}













