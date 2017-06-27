bool nodeAlreadyPlayed(byte value) {
//Serial.println("nodeAlreadyPlayed()");
    for (byte y = 0; y < maze.maxY; y++) {
      
      for (byte x = 0; x < maze.maxX; x++) {
/*
Serial.print(" x: ");
Serial.print(x);
Serial.print(", y: ");
Serial.println(y);
Serial.print(" getNodeValue(x, y): ");
Serial.println(getNodeValue(x, y));
Serial.print(" isNode(x, y): ");
Serial.println(isNode(x, y));
Serial.println(" ");
 */       
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


byte getPipeValue(byte x, byte y) {
  
  return (board[y][x] & 0xF0) >> 4;

}

void setPipeValueXXXX(byte x, byte y, byte value) {
  
  board[y][x] = (board[y][x] & 0x0F) | (value << 4);
  
}


void setPipeValue(byte x, byte y, byte pipeValue, byte nodeValue) {
  
  board[y][x] = (pipeValue << 4) | nodeValue;
  
}

bool validMove(byte selectedNode, byte x, byte y) {


   Serial.println("validMove()");

  // Off the grid!
  if (x < 0 || x > maze.maxX || y < 0 || y > maze.maxY) return false;
    Serial.println("  validMove 2");
    Serial.print("    x: ");
    Serial.println(x);
    Serial.print("    y: ");
    Serial.println(y);
    Serial.print("    selectedNode: ");
    Serial.println(selectedNode);
    Serial.print("    isNode(x,y): ");
    Serial.println(isNode(x,y));
    Serial.print("    getPipeValue(x,y): ");
    Serial.println(getPipeValue(x,y));
    Serial.print("    getNodeValue(x,y): ");
    Serial.println(getNodeValue(x,y));
  
  
  if (!isNode(x,y) && (getPipeValue(x,y) == NOTHING || getNodeValue(x,y) == selectedNode)) return true;
  
   Serial.println("  validMove 3");
  return false;
  
}

/* ----------------------------------------------------------------------------
 *  Draw a horizontal dotted line. 
 *  
 *  So much nicer than a solid line!
 *  
 */
void drawHorizontalLine(byte x1, byte x2, byte y) {

  for (byte x3 = x1; x3 <= x2; x3+=2) {
    arduboy.drawPixel(x3, y, WHITE);
  }
  
}

/* ----------------------------------------------------------------------------
 *  Draw a horizontal dotted line. 
 *  
 *  So much nicer than a solid line!
 *  
 */
void drawVerticalLine(byte x, byte y1, byte y2) {

  for (byte y3 = y1; y3 <= y2; y3+=2) {
    arduboy.drawPixel(x, y3, WHITE);
  }
  
}
