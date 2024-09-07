#include "functions.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include "queue.h"
#include "API.h"
#include <stdlib.h>
// include the sensors file 

// define the thresholde distance that if the distance is greatar than this is a wall 

// 

int getManhatenDistance(int x1 ,int y1 , int x2 ,int y2);
int getNeighbors(POINT point, POINT* result);
bool isValid(POINT point);
bool nextmove (POINT current, POINT *nextmove);
int getMinimumvalueofNeighbor(POINT current);
void floodFil(POINT current);



// global variable 

int Distance[MAZE_WEDTH][MAZE_HEIGHT]={0};
//int WALLS [MAZE_WEDTH][MAZE_HEIGHT]={0};
#define MAX_NEIGHBORS 4




// for test 


int	main(int argc, char *argv[])
{
    POINT start ={0,0};     
    POINT *nextcell= malloc(sizeof(POINT));    
    nextcell->x=-1;     
    nextcell->y=-1;     
    
    while (1)
    {
        if (start.x == MAZE_GOAL_X && start.y == MAZE_GOAL_Y) {
        //printf("Cell (%d, %d) is the maze goal: the robot has reached the goal\n", start.x, start.y);
        return 0; // The robot has reached the goal, stop.
        }
        
      // check the next move if it is valid 
      if (nextmove(start,nextcell))
      {
        //log1("the next move is valid without floodfil ");

         
        //printf("the next move is %d %d ", nextcell->x ,nextcell->y);  // to print the next move 
         // until here all thing is good 
        // move to the next cell 
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

        else {
               // printf("should backtrack ");
                return 0 ;
                // backtrack  (the algorithim with use all the function of the motors )
        }
      }
      
      else {
        
        // floodfil
        //log1("should perform floodfil now");
        floodFil(start);
        //printf("go to th flood fill for the cell %d ,%d",start.x, start.y);   // all printfs we could use the serial monitor 
      
      }
    }
    free(nextcell);
    
   
  
    return 0;
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
            if (!API_wallLeft()) {
                if (getManhatenDistance(result[i].x, result[i].y, MAZE_GOAL_X, MAZE_GOAL_Y) < leastdistance) {
                    leastdistance = getManhatenDistance(result[i].x, result[i].y, MAZE_GOAL_X, MAZE_GOAL_Y);
                    nextmove->x = result[i].x;
                    nextmove->y = result[i].y;
                    flag = true;
                }
            }
        }
        else if (result[i].x == current.x && result[i].y == current.y + 1) {   // the forward cell
            if (!API_wallFront()) {
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
    if(getDistance(TRIGGER_PIN_sensor2, ECHO_PIN_sensor2)>=0&&getDistance(TRIGGER_PIN_sensor2, ECHO_PIN_sensor2)<=RightThreshold)
    return 1;
}

int wallForward()
{
    if(getDistance(TRIGGER_PIN_sensor1, ECHO_PIN_sensor1)>=0&&getDistance(TRIGGER_PIN_sensor1, ECHO_PIN_sensor1)<=ForwardThreshold)
    return 1;
}

int wallLeft()
{
    if(getDistance(TRIGGER_PIN_sensor3, ECHO_PIN_sensor3)>=0&&getDistance(TRIGGER_PIN_sensor3, ECHO_PIN_sensor3)<=LeftThreshold)
    return 1;
}

/*

    handling t junctione , deadends , cornersc , crossroads 

*/




















