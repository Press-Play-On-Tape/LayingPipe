bool nodeAlreadyPlayed(byte value) { 

    for (byte y = 0; y < maze.maxY; y++) {
      
      for (byte x = 0; x < maze.maxX; x++) {
        if (getNodeValue(x, y) == value && !isNode(x, y)) {
          
          return true;
          
        }
        
    }
      
  }
    
  return false;
    
}

bool clearBoard(byte nodeValue) {

  for (byte y = 0; y < maze.maxY; y++) {
    
    for (byte x = 0; x < maze.maxX; x++) {
      
      if (getNodeValue(x, y) == nodeValue && !isNode(x, y)) {
        
        board[y][x] = NOTHING;
        
      }
      
    }
    
  }
  
}

bool isNode(byte x, byte y) {

  return (board[y][x] & 0xF0) == 0xF0;
  
}


bool isPipe(byte x, byte y) {

  return (board[y][x] & 0xF0) > 0x00 && (board[y][x] & 0xF0) != 0xF0;
  
}

byte getNodeValue(byte x, byte y) {
  
  return (board[y][x] & 0x0F);

}

byte getSolutionValue(byte x, byte y) {
  
  return (solution[y][x] & 0x0F);

}

byte getPipeValue(byte x, byte y) {
  
  return (board[y][x] & 0xF0) >> 4;

}

void setPipeValue(byte x, byte y, byte pipeValue, byte nodeValue) {
  
  board[y][x] = (pipeValue << 4) | nodeValue;
  
}

bool validMove(byte direction, SelectedNode selectedNode, byte x, byte y) {

	
  // Off the grid!

  if (x < 0 || x >= maze.maxX || y < 0 || y >= maze.maxY) return false;
  
  
  // Is it a clear cell or the matching node?
  
  if (
      (!isNode(x,y) && getPipeValue(x,y) == NOTHING) ||
      (isNode(x,y) && getNodeValue(x,y) == selectedNode.value && (x != selectedNode.x || y != selectedNode.y))
     ) return true;
  

  // Is the pipe turning back on itself?

  switch (direction) {

    case (UP):
    
      switch (getPipeValue(player.x, player.y)) {

        case PIPE_VERTICAL_TB:
        case PIPE_CORNER_RB:
        case PIPE_CORNER_LB:
          return true;

      }

      break;
      
    case (DOWN):
    
      switch (getPipeValue(player.x, player.y)) {
          
        case PIPE_VERTICAL_BT:
        case PIPE_CORNER_LT:
        case PIPE_CORNER_RT:
          return true;

      }

      break;

    case (LEFT):
    
      switch (getPipeValue(player.x, player.y)) {
   
        case PIPE_CORNER_TR:
        case PIPE_CORNER_BR:
        case PIPE_HORIZONTAL_LR:
          return true;

      }

      break;

    case (RIGHT):
    
      switch (getPipeValue(player.x, player.y)) {

        case PIPE_CORNER_TL:
        case PIPE_CORNER_BL:
        case PIPE_HORIZONTAL_RL:
          return true;

      }

      break;

  }
  
  return false;
  
}

/* ----------------------------------------------------------------------------
 *  Draw a horizontal dotted line. 
 *  
 *  So much nicer than a solid line!
 *  
 * /
void drawHorizontalLine(byte x1, byte x2, byte y) {

  for (byte x3 = x1; x3 <= x2; x3+=2) {
    arduboy.drawPixel(x3, y, WHITE);
  }
  
}*/

/* ----------------------------------------------------------------------------
 *  Draw a horizontal dotted line. 
 *  
 *  So much nicer than a solid line!
 *  
 * /
void drawVerticalLine(byte x, byte y1, byte y2) {

  for (byte y3 = y1; y3 <= y2; y3+=2) {
    arduboy.drawPixel(x, y3, WHITE);
  }
  
}*/
