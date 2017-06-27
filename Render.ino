void renderBoard() { 
//Serial.println("renderBoard()");
//Serial.print("  player.x :");
//Serial.println(player.x);
//Serial.print("  player.y :");
//Serial.println(player.y);
  arduboy.clear();

  for (byte y = 0; y <= maze.maxY; y++) {
    drawHorizontalLine(0, maze.maxX * GRID_WIDTH, y * GRID_HEIGHT);
  }
  
  for (byte x = 0; x <= maze.maxX; x++) {
    drawVerticalLine(x * GRID_WIDTH, 0, maze.maxY * GRID_HEIGHT);
  }
  
  for (byte y = 0; y < maze.maxY; y++) {
      
    for (byte x = 0; x < maze.maxX; x++) {
      
      if (isNode(x, y)) {
        sprites.drawOverwrite(x * GRID_WIDTH + 2, y * GRID_HEIGHT + 1, nodes[getNodeValue(x,y)], frame);
      }
      
      if (isPipe(x,y)) {
        sprites.drawOverwrite(x * GRID_WIDTH, y * GRID_HEIGHT + 1, pipes[getPipeValue(x, y)], frame);
      }
        
    }
      
  }
  
  // Draw Selected cell ..
  
  arduboy.drawRect(player.x * GRID_WIDTH, player.y * GRID_HEIGHT, GRID_WIDTH + 1, GRID_HEIGHT + 1, WHITE);
  
}
