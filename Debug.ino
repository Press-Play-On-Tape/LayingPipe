
void echoBoard() {

Serial.println("Board ---------------------");
        Serial.print("  gameState: ");
        Serial.println(gameState);
        Serial.print("  player.highlightedNode.x: ");
        Serial.println(player.highlightedNode.x);
        Serial.print("  player.highlightedNode.y: ");
        Serial.println(player.highlightedNode.y);
        Serial.print("  player.selectedNode.value: ");
        Serial.println(player.selectedNode.value);
        Serial.print("  player.selectedNode.x: ");
        Serial.println(player.selectedNode.x);
        Serial.print("  player.selectedNode.y: ");
        Serial.println(player.selectedNode.y);


    for (byte y = 0; y < puzzle.maximum.y; y++) {
    
    for (byte x = 0; x < puzzle.maximum.x; x++) {
        
        Serial.print("  ");
        Serial.print(leftValue(puzzle.board[y][x]));
        Serial.print(":");
        Serial.print(rightValue(puzzle.board[y][x]));
        Serial.print(" ");
      
    }

    Serial.println(" ");
    
  }
    Serial.println(" ");
}

