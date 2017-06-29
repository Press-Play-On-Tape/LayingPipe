byte leftValue(byte val) {

  return val >> 4; 
      
}

byte rightValue(byte val) {

  return val & 0x0F; 
      
}

void initBoard(byte puzzleType, byte puzzleNumber) {

  puzzle.maximum.x = puzzle.maximum.y = puzzleType;
  
  byte x = 0;
  byte y = 0;
  byte z = 0;
  
  byte bytesToRead = (puzzleType % 2 == 0 ? (puzzleType / 2) * puzzleType : ((puzzleType / 2) + 1) * puzzleType);
	
  for (byte i = (puzzleNumber * bytesToRead); i < ((puzzleNumber + 1) * bytesToRead); i++) {

  	switch (puzzleType) {
      
  	  case PUZZLE_5X5:
  		  z = pgm_read_byte(&puzzles_5x5[i]);
  		  break;
  		  
    	  case PUZZLE_7X7:
  		  z = puzzles_7x7[i];
  		  break;
  		  
    	  case PUZZLE_9X9:
  		  z = puzzles_9x9[i];
  		  break;
  
  	}

    puzzle.board[y][x] = 0;
	  
	  if ((x <= puzzle.maximum.x) && leftValue(z) > 0) {
		  
		  puzzle.board[y][x] = 0xF0 | leftValue(z);
		  
	  }
	  
	  x++;

    puzzle.board[y][x] = 0;
	  
	  if ((x <= puzzle.maximum.x) && rightValue(z) > 0) {
		  
		  puzzle.board[y][x] = 0xF0 | rightValue(z);
		  
	  }
	  
	  x++;
	  
	  if (x >= puzzle.maximum.x) { y++; x = 0; }
		  
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

void clearSelection() {

  player.selectedNode.value = 0;
  player.selectedNode.x = 0;
  player.selectedNode.y = 0;

}

bool isPuzzleComplete() {

  for (byte y = 0; y < puzzle.maximum.y; y++) {
    
    for (byte x = 0; x < puzzle.maximum.x; x++) {
      
      if (getNodeValue(x, y) == 0) {
        
        return false;
        
      }
      
    }
    
  }

  return true;
  
}
