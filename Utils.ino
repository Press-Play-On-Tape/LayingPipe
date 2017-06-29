byte leftValue(byte val) {

  return val >> 4; 
      
}

byte rightValue(byte val) {

  return val & 0x0F; 
      
}

void initBoard(byte puzzleType, byte puzzleNumber) {

  puzzle.maximum.x = puzzleType;
  puzzle.maximum.y = puzzleType;
  
  byte x = 0;
  byte y = 0;
  byte z = 0;
  byte bytesToRead = (puzzleType / 2) * puzzleType;
  
  memset(puzzle.board, 0, (sizeof(puzzle.board) / sizeof(puzzle.board[0])));
	
  for (byte i = (puzzleNumber * bytesToRead); i < ((puzzleNumber + 1) * bytesToRead); i++) {

	switch (puzzleType) {
	  
	  case PUZZLE_5X5:
		  z = puzzles_5x5[i];
		  break;
		  
  	  case PUZZLE_7X7:
		  z = puzzles_7x7[i];
		  break;
		  
  	  case PUZZLE_9X9:
		  z = puzzles_9x9[i];
		  break;

	}
	  
	  if ((x <= puzzle.maximum.x) && leftValue(z) > 0) {
		  
		  puzzle.board[y][x] = 0xF0 | leftValue(z);
		  
	  }
	  
	  x++;
	  
	  if ((x <= puzzle.maximum.x) && rightValue(z) > 0) {
		  
		  puzzle.board[y][x] = 0xF0 | rightValue(z);
		  
	  }
	  
	  x++;
	  
	  if (x >= puzzle.maximum.x) { y++; }
		  
  }
	
}


bool nodeAlreadyPlayed(byte value) { 

    for (byte y = 0; y < puzzle.maximum.y; y++) {
      
      for (byte x = 0; x < puzzle.maximum.x; x++) {
        if (getNodeValue(x, y) == value && !isNode(x, y)) {
          
          return true;
          
        }
        
    }
      
  }
    
  return false;
    
}

bool clearBoard(byte nodeValue) {

  for (byte y = 0; y < puzzle.maximum.y; y++) {
    
    for (byte x = 0; x < puzzle.maximum.x; x++) {
      
      if (getNodeValue(x, y) == nodeValue && !isNode(x, y)) {
        
        puzzle.board[y][x] = NOTHING;
        
      }
      
    }
    
  }
  
}

bool isNode(byte x, byte y) {

  return (puzzle.board[y][x] & 0xF0) == 0xF0;
  
}


bool isPipe(byte x, byte y) {

  return (puzzle.board[y][x] & 0xF0) > 0x00 && (puzzle.board[y][x] & 0xF0) != 0xF0;
  
}

byte getNodeValue(byte x, byte y) {
  
  return (puzzle.board[y][x] & 0x0F);

}

byte getPipeValue(byte x, byte y) {
  
  return (puzzle.board[y][x] & 0xF0) >> 4;

}

void setPipeValue(byte x, byte y, byte pipeValue, byte nodeValue) {
  
  puzzle.board[y][x] = (pipeValue << 4) | nodeValue;
  
}

bool validMove(byte direction, Node selectedNode, byte x, byte y) {

	
  // Off the grid!

  if (x < 0 || x >= puzzle.maximum.x || y < 0 || y >= puzzle.maximum.y) return false;
  
  
  // Is it a clear cell or the matching node?
  
  if (
      (!isNode(x,y) && getPipeValue(x,y) == NOTHING) ||
      (isNode(x,y) && getNodeValue(x,y) == selectedNode.value && (x != selectedNode.x || y != selectedNode.y))
     ) return true;
  

  // Is the pipe turning back on itself?

  switch (direction) {

    case (UP):
    
      switch (getPipeValue(player.highlightedNode.x, player.highlightedNode.y)) {

        case PIPE_VERTICAL_TB:
        case PIPE_CORNER_RB:
        case PIPE_CORNER_LB:
          return true;

      }

      break;
      
    case (DOWN):
    
      switch (getPipeValue(player.highlightedNode.x, player.highlightedNode.y)) {
          
        case PIPE_VERTICAL_BT:
        case PIPE_CORNER_LT:
        case PIPE_CORNER_RT:
          return true;

      }

      break;

    case (LEFT):
    
      switch (getPipeValue(player.highlightedNode.x, player.highlightedNode.y)) {
   
        case PIPE_CORNER_TR:
        case PIPE_CORNER_BR:
        case PIPE_HORIZONTAL_LR:
          return true;

      }

      break;

    case (RIGHT):
    
      switch (getPipeValue(player.highlightedNode.x, player.highlightedNode.y)) {

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
