byte leftValue(byte val) {

  return val >> 4; 
      
}

byte rightValue(byte val) {

  return val & 0x0F; 
      
}

void initBoard(byte puzzleType, byte puzzleNumber) {

  byte x = 0;
  byte y = 0;
  byte z = 0;
  
  byte bytesToRead = (puzzleType % 2 == 0 ? (puzzleType / 2) * puzzleType : ((puzzleType / 2) + 1) * puzzleType);

  puzzle.maximum.x = puzzle.maximum.y = puzzleType;
  puzzle.offset.x = pgm_read_byte(&puzzles_details[(puzzleType - 5) * 8]);
  puzzle.offset.y = pgm_read_byte(&puzzles_details[((puzzleType - 5) * 8) + 1]);
  puzzle.scrollbar.x = pgm_read_byte(&puzzles_details[((puzzleType - 5) * 8) + 2]);
  puzzle.scrollbar.y = pgm_read_byte(&puzzles_details[((puzzleType - 5) * 8) + 3]);
  puzzle.scrollbar.width = pgm_read_byte(&puzzles_details[((puzzleType - 5) * 8) + 4]);
  puzzle.scrollbar.height = pgm_read_byte(&puzzles_details[((puzzleType - 5) * 8) + 5]);
  puzzle.scrollbar.slider.unit = pgm_read_byte(&puzzles_details[((puzzleType - 5) * 8) + 6]);
  puzzle.scrollbar.slider.overall = pgm_read_byte(&puzzles_details[((puzzleType - 5) * 8) + 7]);

  for (int i = (puzzleNumber * bytesToRead); i < ((puzzleNumber + 1) * bytesToRead); i++) {

  	switch (puzzleType) {
      
  	  case PUZZLE_5X5:
  		  z = pgm_read_byte(&puzzles_5x5[i]);
  		  break;
        
      case PUZZLE_6X6:
        z = pgm_read_byte(&puzzles_6x6[i]);
        break;
        
      case PUZZLE_7X7:
        z = pgm_read_byte(&puzzles_7x7[i]);
        break;
        
      case PUZZLE_8X8:
        z = pgm_read_byte(&puzzles_8x8[i]);
        break;
  		  
  	  case PUZZLE_9X9:
  		  z = pgm_read_byte(&puzzles_9x9[i]);
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

void clearHighlightAndSelection() {

  player.selectedNode.value = 0;
  player.selectedNode.x = 0;
  player.selectedNode.y = 0;
  player.highlightedNode.x = 0;
  player.highlightedNode.y = 0;

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

byte getNumberOfPuzzles(byte puzzleType) {

  switch (puzzleType) {
    
    case PUZZLE_5X5:
      return puzzles_5x5_count;
    
    case PUZZLE_6X6:
      return puzzles_6x6_count;
    
    case PUZZLE_7X7:
      return puzzles_7x7_count;
    
    case PUZZLE_8X8:
      return puzzles_8x8_count;
    
    case PUZZLE_9X9:
      return puzzles_9x9_count;

  }
  
}

void toggleSoundSettings() {

  if (arduboy.audio.enabled()) {
  
    arduboy.audio.off(); 
    arduboy.audio.saveOnOff();
  
  }
  else {
  
    arduboy.audio.on(); 
    arduboy.audio.saveOnOff();
  
  }
    
}

