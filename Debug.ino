byte leftValue(byte val) {

  return val >> 4; 
      
}

byte rightValue(byte val) {

  return val & 0x0F; 
      
}

void echoBoard() {

Serial.println("Board ---------------------");
        Serial.print("  gameState: ");
        Serial.println(gameState);
        Serial.print("  player.x: ");
        Serial.println(player.x);
        Serial.print("  player.y: ");
        Serial.println(player.y);
        Serial.print("  player.selectedNode.value: ");
        Serial.println(player.selectedNode.value);
        Serial.print("  player.selectedNode.x: ");
        Serial.println(player.selectedNode.x);
        Serial.print("  player.selectedNode.y: ");
        Serial.println(player.selectedNode.y);


    for (byte y = 0; y < maze.maxY; y++) {
    
    for (byte x = 0; x < maze.maxX; x++) {
        
        Serial.print("  ");
        Serial.print(leftValue(board[y][x]));
        Serial.print(":");
        Serial.print(rightValue(board[y][x]));
        Serial.print(" ");
      
    }

    Serial.println(" ");
    
  }
    Serial.println(" ");
}

