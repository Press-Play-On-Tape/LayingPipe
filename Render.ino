void renderBoard() { 
//Serial.println("renderBoard()");
//Serial.print("  player.x :");
//Serial.println(player.x);
//Serial.print("  player.y :");
//Serial.println(player.y);
  arduboy.clear();
  
  for (byte y = 0; y < maze.maxY; y++) {
      
    for (byte x = 0; x < maze.maxX; x++) {
      
      if (isPipe(x,y)) {
        sprites.drawOverwrite(x * GRID_WIDTH, y * GRID_HEIGHT, pipes[getPipeValue(x, y)], frame);
      }
        
    }
      
  }
  
  for (byte y = 0; y < maze.maxY; y++) {
      
    for (byte x = 0; x < maze.maxX; x++) {
      
      if (isNode(x, y)) {
        sprites.drawOverwrite(x * GRID_WIDTH + 2, y * GRID_HEIGHT + 2, nodes[getNodeValue(x,y)], frame);
      }
        
    }
      
  }
  
  // Draw Selected cell ..
/*
  for (byte y = 0; y <= maze.maxY; y++) {
    drawHorizontalLine(0, maze.maxX * GRID_WIDTH, y * GRID_HEIGHT);
  }
  
  for (byte x = 0; x <= maze.maxX; x++) {
    drawVerticalLine(x * GRID_WIDTH, 0, maze.maxY * GRID_HEIGHT);;'/l,
  }
*/  

    for (byte y = 0; y <= maze.maxY; y++) {
  for (byte x = 0; x <= maze.maxX; x++) {
//    if (x > 0) arduboy.drawPixel((x * GRID_WIDTH) -2, (y * GRID_HEIGHT), WHITE);
    arduboy.drawPixel((x * GRID_WIDTH), (y * GRID_HEIGHT), WHITE);
//    if (x < maze.maxX) arduboy.drawPixel((x * GRID_WIDTH) + 2, (y * GRID_HEIGHT), WHITE);
//    if (y > 0)arduboy.drawPixel((x * GRID_WIDTH), (y * GRID_HEIGHT) - 2, WHITE);
//    if (y < maze.maxY)arduboy.drawPixel((x * GRID_WIDTH), (y * GRID_HEIGHT) + 2, WHITE);
  }
  }

  
  arduboy.drawRect(player.x * GRID_WIDTH, player.y * GRID_HEIGHT, GRID_WIDTH + 1, GRID_HEIGHT + 1, WHITE);

}
