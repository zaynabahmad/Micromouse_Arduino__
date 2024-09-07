

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