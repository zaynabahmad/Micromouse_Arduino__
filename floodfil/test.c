#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "queue.h"
#include <stddef.h>



int MAZZE_GOAL_X = 8;  // Define the maze goal X and Y coordinates for testing
int MAZZE_GOAL_Y = 8;
int MAZZE_WEDTH =16;
int MAZZE_HEIGHT= 16;
#define MAX_NEIGHBORS 4


// Define API_wallRight, API_wallLeft, API_wallFront, getManhatenDistance, and getNeighbors functions
bool API_wallRight =false ;
bool API_wallLeft= false ;
bool API_wallFront =false ;


bool isValid(POINT point);
int getMinimumvalueofNeighbor(POINT current);
void mappinAndPathplanning(POINT current);

// Function to allocate memory for Distance array
int Distance[16][16]={0};





int getManhatenDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int getNeighbors(POINT point, POINT* result) {
    int resultCount = 0;

    // Define the four possible neighbor offsets
    int neighborOffsets[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (int i = 0; i < 4; i++) {
        POINT neighbor = {point.x + neighborOffsets[i][0], point.y + neighborOffsets[i][1]};
        if (isValid(neighbor)) {
            result[resultCount] = neighbor;
            (resultCount)++;
        }
    }
    return resultCount;
}



// Define the 'nextmove' function
bool nextmove(POINT current, POINT* nextmove) {
    bool flag = false;

    POINT result[MAX_NEIGHBORS];

    //getNeighbors(current, result);

    int leastdistance = getManhatenDistance(current.x, current.y, MAZZE_GOAL_X, MAZZE_GOAL_Y);
    
   

    for (int i = 0; i < (getNeighbors(current, result)); i++) {
        if (result[i].x == current.x + 1 && result[i].y == current.y) {   // the right cell
            if (!API_wallRight) {
                if (getManhatenDistance(result[i].x, result[i].y, MAZZE_GOAL_X, MAZZE_GOAL_Y) < leastdistance) {
                    leastdistance = getManhatenDistance(result[i].x, result[i].y, MAZE_GOAL_X, MAZE_GOAL_Y);
                    nextmove->x = result[i].x;
                    nextmove->y = result[i].y;
                    flag =  true; // 
                }
            }
        }
        else if (result[i].x == current.x - 1 && result[i].y == current.y) {   // the left cell
            if (!API_wallLeft) {
                if (getManhatenDistance(result[i].x, result[i].y, MAZZE_GOAL_X, MAZZE_GOAL_Y) < leastdistance) {
                    leastdistance = getManhatenDistance(result[i].x, result[i].y, MAZZE_GOAL_X, MAZZE_GOAL_Y);
                    nextmove->x = result[i].x;
                    nextmove->y = result[i].y;
                    flag = true;
                }
            }
        }
        else if (result[i].x == current.x && result[i].y == current.y + 1) {   // the forward cell
            if (!API_wallFront) {
                if (getManhatenDistance(result[i].x, result[i].y, MAZZE_GOAL_X, MAZZE_GOAL_Y) < leastdistance) {
                    leastdistance = getManhatenDistance(result[i].x, result[i].y, MAZZE_GOAL_X, MAZZE_GOAL_Y);
                    nextmove->x = result[i].x;
                    nextmove->y = result[i].y;
                    flag=  true;
                }
            }
        }

    }
    printf("flag : %d",flag);

    return flag;

}


void floodFil(POINT current)
{
    // Check if it is in the goal or not 
    printf("Entering floodFil for cell (%d, %d)\n", current.x, current.y);

    if (current.x == MAZZE_GOAL_X && current.y == MAZZE_GOAL_Y) {
        printf("Cell (%d, %d) is the maze goal: the robot has reached the goal\n", current.x, current.y);
        return; // The robot has reached the goal, stop.
    }

    // Start the flood-fill 
    Queue *queueCells = (Queue *)malloc(sizeof(Queue));
    CreateQueue(queueCells);
    Append(current, queueCells);

    while (!QueueEmpty(queueCells)) {
        POINT *outcellfromqueue = (POINT*)malloc(sizeof(POINT));
        serve(outcellfromqueue, queueCells);

        printf("Processing cell (%d, %d) from the queue\n", outcellfromqueue->x, outcellfromqueue->y);

        int minimumValue = getMinimumvalueofNeighbor(*outcellfromqueue);
        printf("Minimum value among neighbors of cell (%d, %d) is %d\n", outcellfromqueue->x, outcellfromqueue->y, minimumValue);

        if (minimumValue >= getManhatenDistance(outcellfromqueue->x, outcellfromqueue->y, MAZZE_GOAL_X, MAZZE_GOAL_Y)) {
            printf("Cell (%d, %d) is on a path to the goal. Updating distance.\n", outcellfromqueue->x, outcellfromqueue->y);

            Distance[outcellfromqueue->x][outcellfromqueue->y] = minimumValue + 1;

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
    printf("Flood-fill completed for cell (%d, %d)\n", current.x, current.y);
}




   int	main(int argc, char *argv[])
{

        // Test Case 1: Simple maze with a direct path to the goal
    int mazeLayout1[16][16] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    // Set wall variables based on mazeLayout1
    // Define starting point
    POINT start1 = {0, 0};
    API_wallRight = mazeLayout1[start1.x][start1.y + 1] == 1;
    API_wallLeft = mazeLayout1[start1.x][start1.y - 1] == 1;
    API_wallFront = mazeLayout1[start1.x + 1][start1.y] == 1;

    // Run your code and check if it reaches the goal correctly
    mappinAndPathplanning(start1);
    if (Distance[MAZZE_GOAL_X][MAZZE_GOAL_Y] == 5) {
        printf("Test Case 1: Reached the goal correctly.\n");
    } else {
        printf("Test Case 1: Did not reach the goal as expected.\n");
        printf("the distance of the goal cell is %d ",Distance[MAZZE_GOAL_X][MAZZE_GOAL_Y]);
        printf("the distance of the start cell  %d ",Distance[start1.x][start1.y]);

    }

    // Test Case 2: More complex maze with obstacles
    /*int mazeLayout2[16][16] = {
        // Define your maze layout here
    };

    // Set wall variables based on mazeLayout2
    // Define starting point
    POINT start2 = {1, 1};
    API_wallRight = mazeLayout2[start2.x][start2.y + 1] == 1;
    API_wallLeft = mazeLayout2[start2.x][start2.y - 1] == 1;
    API_wallFront = mazeLayout2[start2.x + 1][start2.y] == 1;

    // Run your code and check if it reaches the goal correctly
    floodFil(start2);
    if (Distance[MAZZE_GOAL_X][MAZZE_GOAL_Y] == expectedDistance) {
        printf("Test Case 2: Reached the goal correctly.\n");
    } else {
        printf("Test Case 2: Did not reach the goal as expected.\n");
    }
*/
    // Add more test cases as needed to cover different scenarios

    return 0;
}



bool isValid(POINT point) {       // passed
    // check if this cell is in the boundries 
    return (point.x >= 0 && point.x < MAZZE_WEDTH && point.y >= 0 && point.y < MAZZE_HEIGHT );
    
}



int getMinimumvalueofNeighbor(POINT current)   //passed 
{
    POINT result[4];
    getNeighbors(current, result);
    int leastdistance=255;
    for (int i=0;i<4;i++)
    {
        if(getManhatenDistance(result[i].x, result[i].y, MAZZE_GOAL_X, MAZZE_GOAL_Y)<leastdistance)
        {
            leastdistance=getManhatenDistance(result[i].x, result[i].y, MAZZE_GOAL_X, MAZZE_GOAL_Y);
        }
        
    }

    return leastdistance;
}

void mappinAndPathplanning(POINT current)
{
         
    POINT *nextcell= malloc(sizeof(POINT));    
    nextcell->x=-1;     
    nextcell->y=-1;     
    
    while (1)
    {
        if (current.x == MAZZE_GOAL_X && current.y == MAZZE_GOAL_Y) {
        printf("Cell (%d, %d) is the maze goal: the robot has reached the goal\n", current.x, current.y);
        return; // The robot has reached the goal, stop.
        }
        
      // check the next move if it is valid 
        if (nextmove(current,nextcell))
        {
        printf("the next move is valid without floodfil ");

         
        //printf("the next move is %d %d ", nextcell->x ,nextcell->y);  // to print the next move 
         // until here all thing is good 
        // move to the next cell 
            if ((nextcell->x)==((current.x )+1) && (nextcell->y) ==(current.y))
            {
                // move right 
                current.x++;   // update the data that the robot has moved right (use the encoder )
            }

            else if ((nextcell->x)==(current.x -1) && (nextcell->y) == (current.y))
            {
                // move left 
        
                current.x--;  // update the data that the robot has moved left (use the encoder )
            }

            else if ((nextcell->x)==(current.x ) && (nextcell->y) == ((current.y)+1))
            {
                // move straight
        

            // API_moveForward();  // replace this with the code of the motor (call of the function )
                
                

                current.y++;  // update the data that the robot has moved forwared (use the encoder )
            }

            else {
                printf("should backtrack ");
                return;
                    // backtrack  (the algorithim with use all the function of the motors )
            }
        }
      
        else {
        
        // floodfil
        
        floodFil(current);
        printf("go to th flood fill for the cell %d ,%d",current.x, current.y);   // all printfs we could use the serial monitor 
      
      }
    }
    free(nextcell);
    
   
  
}