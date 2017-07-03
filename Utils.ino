/* ----------------------------------------------------------------------------
 *  Return the upper 4 bits of a byte.
 */
byte leftValue(byte val) {

  return val >> 4; 
      
}


/* ----------------------------------------------------------------------------
 *  Return the lower 4 bits of a byte.
 */
byte rightValue(byte val) {

  return val & 0x0F; 
      
}


/* ----------------------------------------------------------------------------
 *  Initialise the board.
 */
void initBoard(byte puzzleType, byte puzzleNumber) {

  byte x = 0;
  byte y = 0;
  byte z = 0;
  
  byte bytesToRead = (puzzleType % 2 == 0 ? (puzzleType / 2) * puzzleType : ((puzzleType / 2) + 1) * puzzleType);

  puzzle.maximum.x = puzzle.maximum.y = puzzleType;
  puzzle.offset.x = pgm_read_byte(&puzzles_details[(puzzleType - 5) * 8]);
  puzzle.offset.y = pgm_read_byte(&puzzles_details[((puzzleType - 5) * 8) + 1]);
  puzzle.slider.unit = pgm_read_byte(&puzzles_details[((puzzleType - 5) * 8) + 2]);
  puzzle.slider.overall = pgm_read_byte(&puzzles_details[((puzzleType - 5) * 8) + 3]);

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


/* ----------------------------------------------------------------------------
 *  Has the node already been played?
 */
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


/* ----------------------------------------------------------------------------
 *  Clear the board of pipes for a certain node value.
 */
bool clearBoard(byte nodeValue) {

  for (byte y = 0; y < puzzle.maximum.y; y++) {
    
    for (byte x = 0; x < puzzle.maximum.x; x++) {
      
      if (getNodeValue(x, y) == nodeValue && !isNode(x, y)) {
        
        puzzle.board[y][x] = NOTHING;
        
      }
      
    }
    
  }
  
}


/* ----------------------------------------------------------------------------
 *  Is the position nominated a node?
 */
bool isNode(byte x, byte y) {

  return (puzzle.board[y][x] & 0xF0) == 0xF0;
  
}


/* ----------------------------------------------------------------------------
 *  Get the node value for the position.
 */
byte getNodeValue(byte x, byte y) {
  
  return (puzzle.board[y][x] & 0x0F);

}


/* ----------------------------------------------------------------------------
 *  Is the position nominated a pipe?
 */
bool isPipe(byte x, byte y) {

  return (puzzle.board[y][x] & 0xF0) > 0x00 && (puzzle.board[y][x] & 0xF0) != 0xF0;
  
}


/* ----------------------------------------------------------------------------
 *  Get the pipe value for the position.
 */
byte getPipeValue(byte x, byte y) {
  
  return (puzzle.board[y][x] & 0xF0) >> 4;

}


/* ----------------------------------------------------------------------------
 *  Set the pipe value for the position.
 */
void setPipeValue(byte x, byte y, byte pipeValue, byte nodeValue) {
  
  puzzle.board[y][x] = (pipeValue << 4) | nodeValue;
  
}


/* ----------------------------------------------------------------------------
 *  Clear the player's selection.
 */
void clearSelection() {

  player.selectedNode.value = 0;
  player.selectedNode.x = 0;
  player.selectedNode.y = 0;

}


/* ----------------------------------------------------------------------------
 *  Clear the player's highlight and selection.
 */
void clearHighlightAndSelection() {

  player.selectedNode.value = 0;
  player.selectedNode.x = 0;
  player.selectedNode.y = 0;
  player.highlightedNode.x = 0;
  player.highlightedNode.y = 0;

}


/* ----------------------------------------------------------------------------
 *  Is the puzzle complete?  All cells should have a 'node' value.
 */
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


/* ----------------------------------------------------------------------------
 *  Return the number of puzzles for a nominated level.
 */
byte getNumberOfPuzzles(byte puzzleLevel) {

  switch (puzzleLevel) {
    
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


/* ----------------------------------------------------------------------------
 *  Toggle the sound setting and commit to the EEPROM.
 */
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


/* ----------------------------------------------------------------------------
 *  Draw a horizontal dotted line. 
 *  
 *  So much nicer than a solid line!
 */
void drawHorizontalDottedLine(int x1, int x2, int y) {

  for (int x3 = x1; x3 <= x2; x3+=2) {
    arduboy.drawPixel(x3, y, WHITE);
  }
  
}
