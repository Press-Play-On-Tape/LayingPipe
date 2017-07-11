#define SCROLLBAR_X          119
#define SCROLLBAR_Y          0
#define SCROLLBAR_WIDTH      9
#define SCROLLBAR_HEIGHT     64

/* ----------------------------------------------------------------------------
 *   Render the board.
 */
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

  if (puzzle.slider.unit > 0) {
    
    arduboy.fillRect(SCROLLBAR_X - 1, SCROLLBAR_Y, SCROLLBAR_WIDTH + 1, SCROLLBAR_HEIGHT, BLACK);
    arduboy.drawRect(SCROLLBAR_X, SCROLLBAR_Y, SCROLLBAR_WIDTH, SCROLLBAR_HEIGHT, WHITE);
    arduboy.fillRect(SCROLLBAR_X + 2, SCROLLBAR_Y + 6 + (topRow * puzzle.slider.unit), SCROLLBAR_WIDTH - 4, puzzle.slider.overall, WHITE);


    // Top arrow ..

    arduboy.fillTriangle(SCROLLBAR_X + 4, SCROLLBAR_Y + 2, SCROLLBAR_X + 2, SCROLLBAR_Y + 4, SCROLLBAR_X + 6, SCROLLBAR_Y + 4, WHITE);


    // Bottom arrow ..
    
    arduboy.fillTriangle(SCROLLBAR_X + 2, SCROLLBAR_Y + SCROLLBAR_HEIGHT - 5, SCROLLBAR_X + 6, SCROLLBAR_Y + SCROLLBAR_HEIGHT - 5, SCROLLBAR_X + 4, SCROLLBAR_Y + SCROLLBAR_HEIGHT - 3, WHITE);

  }
    
}
