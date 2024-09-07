
#include "functions.h"




//function to calculate the manhaten distance  
int getManhatenDistance(int x1 ,int y1 , int x2 ,int y2)   // passed
{
    if(Distance[x1][y1]!=0) return Distance[x1][y1]; 
    else return abs(x1 - x2) + abs(y1 - y2);
}

// function to get the neighbores 
void getNeighbors(POINT point, POINT* result) {
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
}

// function to obtain that this cell is valid in the maze 
bool isValid(POINT point) {       // passed
    // check if this cell is in the boundries 
    return (point.x >= 0 && point.x < MAZE_WEDTH && point.y >= 0 && point.y < MAZE_HEIGHT );
    
}

// function to get the cell the next cell if it is available 

bool nextmove (POINT current, POINT *nextmove)
{
    
    bool flag= false;
    
    POINT result[4];
    

    getNeighbors(current, result);
    

    int leastdistance= getManhatenDistance(current.x, current.y, MAZE_GOAL_X, MAZE_GOAL_Y) ;
    
    for(int i=0; i<4;i++)
        {
            if (result[i].x==current.x +1&& result[i].y==current.y)   // the right cell 
            {
                // check if there is no wall at the right 
                if (!API_wallRight()){

                // get the manhatendistance
                if (getManhatenDistance(result[i].x, result[i].y,MAZE_GOAL_X , MAZE_GOAL_Y)<leastdistance)
                {
                    leastdistance=getManhatenDistance(result[i].x, result[i].y,MAZE_GOAL_X , MAZE_GOAL_Y);
                    nextmove->x=result[i].x;
                    nextmove->y=result[i].y;
                    // change the flag that we found a valid cell to move 
                    flag =true;
                    log1("the flag should be true due to the right movs");
                    printf("%d",flag);

                    
                }
               } 

            }

            else if (result[i].x==current.x -1&& result[i].y==current.y)   // the left cell 
            {
                // check if there is no wall at the left 
                if (!API_wallLeft()){
                
                // get the manhatendistance
                if (getManhatenDistance(result[i].x, result[i].y,MAZE_GOAL_X , MAZE_GOAL_Y)<leastdistance)
                {
                    leastdistance=getManhatenDistance(result[i].x, result[i].y,MAZE_GOAL_X , MAZE_GOAL_Y);
                    nextmove->x=result[i].x;
                    nextmove->y=result[i].y;
                    // change the flag that we found a valid cell to move 
                    flag =true;
                    log1("the flag should be true due to the left  movs");

                    
                } 
                }

            }

            else if (result[i].x==current.x && result[i].y==current.y+1)   // the forward cell 
            {
                // check if there is no wall at the forward 
                if (!API_wallFront()){
                
                // get the manhatendistance
                if (getManhatenDistance(result[i].x, result[i].y,MAZE_GOAL_X , MAZE_GOAL_Y)<leastdistance)
                {
                    leastdistance=getManhatenDistance(result[i].x, result[i].y,MAZE_GOAL_X , MAZE_GOAL_Y);
                    nextmove->x=result[i].x;
                    nextmove->y=result[i].y;
                    // change the flag that we found a valid cell to move 
                    flag =true;
                    log1("the flag should be true due to the forward movs");
                    
                } 

            }
            }
        }
    
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
    Queue *queueCells ;
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
            POINT result[4];
            getNeighbors(current, result);
            for (int i=0;i<4;i++){
            Append(result[i], queueCells);
            }


        }


    }


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
