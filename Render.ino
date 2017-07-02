void renderBoard(int xOffset, int yOffset, byte topRow) { 

  arduboy.clear();

  // Draw stripey background ..
  
  for (int y = 0; y < 256; y+=3) {
    arduboy.drawLine(y, 0, 0, y, WHITE);
  }
  

  // Clear background of actual board ..
  
  arduboy.fillRect(xOffset - 3, yOffset - 3 , (puzzle.maximum.x * GRID_WIDTH) + 7, (puzzle.maximum.y * GRID_HEIGHT) + 7, BLACK);
  arduboy.drawRect(xOffset - 2, yOffset - 2 , (puzzle.maximum.x * GRID_WIDTH) + 5, (puzzle.maximum.y * GRID_HEIGHT) + 5, WHITE);


  // Draw placed pipes ..
  
  for (int y = 0; y < puzzle.maximum.y; y++) {
      
    for (int x = 0; x < puzzle.maximum.x; x++) {
      
      if (isPipe(x,y)) {
        
        sprites.drawExternalMask((x * GRID_WIDTH) + xOffset, (y * GRID_HEIGHT) + yOffset, pipes[getPipeValue(x, y)], pipe_mask, frame, frame);

      }
        
    }
      
  }



  // Draw placed pipes ..
  
  for (int y = 0; y < puzzle.maximum.y; y++) {
      
    for (int x = 0; x < puzzle.maximum.x; x++) {
      
      if (isNode(x, y)) {
        
        sprites.drawOverwrite((x * GRID_WIDTH + 2) + xOffset, (y * GRID_HEIGHT + 2) + yOffset, nodes[getNodeValue(x,y)], frame);
        
      }
        
    }
      
  }

  
  // Draw grid marks ..

  for (int y = 0; y <= puzzle.maximum.y; y++) {
    for (int x = 0; x <= puzzle.maximum.x; x++) {
      arduboy.drawPixel((x * GRID_WIDTH) + xOffset, (y * GRID_HEIGHT) + yOffset, WHITE);
    }
  }

  
  // Draw selected cell ..
  
  arduboy.drawRect((player.highlightedNode.x * GRID_WIDTH) + xOffset, (player.highlightedNode.y * GRID_HEIGHT) + yOffset, GRID_WIDTH + 1, GRID_HEIGHT + 1, WHITE);


  // Draw scrollbar if one is needed ..

  if (puzzle.scrollbar.width > 0) {
    
    arduboy.fillRect(puzzle.scrollbar.x - 1, puzzle.scrollbar.y, puzzle.scrollbar.width + 1, puzzle.scrollbar.height, BLACK);
    arduboy.drawRect(puzzle.scrollbar.x, puzzle.scrollbar.y, puzzle.scrollbar.width, puzzle.scrollbar.height, WHITE);
    arduboy.fillRect(puzzle.scrollbar.x + 2, puzzle.scrollbar.y + 6 + (topRow * puzzle.scrollbar.slider.unit), puzzle.scrollbar.width - 4, puzzle.scrollbar.slider.overall, WHITE);


    // Top arrow ..
    
    arduboy.drawPixel(puzzle.scrollbar.x + 4, puzzle.scrollbar.y + 2, WHITE);
    arduboy.drawLine(puzzle.scrollbar.x + 3, puzzle.scrollbar.y + 3, puzzle.scrollbar.x + 5, puzzle.scrollbar.y + 3, WHITE);
    arduboy.drawLine(puzzle.scrollbar.x + 2, puzzle.scrollbar.y + 4, puzzle.scrollbar.x + 6, puzzle.scrollbar.y + 4, WHITE);


    // Bottom arrow ..
    
    arduboy.drawLine(puzzle.scrollbar.x + 2, puzzle.scrollbar.y + puzzle.scrollbar.height - 5, puzzle.scrollbar.x + 6, puzzle.scrollbar.y + puzzle.scrollbar.height - 5, WHITE);
    arduboy.drawLine(puzzle.scrollbar.x + 3, puzzle.scrollbar.y + puzzle.scrollbar.height - 4, puzzle.scrollbar.x + 5, puzzle.scrollbar.y + puzzle.scrollbar.height - 4, WHITE);
    arduboy.drawPixel(puzzle.scrollbar.x + 4, puzzle.scrollbar.y + puzzle.scrollbar.height - 3, WHITE);

  }
    
}
