#ifndef _FLOODFILL_H_
#define _FLOODFILL_H_
/* Constants for flood fill algorithm*/
#define UNEXPLORED 255
#define WALL 254

void initializeMaze();
void floodFill(byte x, byte y, byte distance);


#endif //_FLOODFILL_H_
