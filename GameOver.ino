/* ----------------------------------------------------------------------------
 *   Render the Game Over screen.
 *   
 *   If this is the last puzzle in the level, the message 'Level Finished' is
 *   displayed otherwise a simple 'Congratulations' is shown.
 */
void gameOver() { 
  
  arduboy.delayShort(1000);

  arduboy.clear();
      
  sprites.drawOverwrite(112,  0, logo_straight_TB_noflange, frame);
  sprites.drawOverwrite(112, 16, logo_elbow_TL, frame);
  sprites.drawOverwrite(96,  16, logo_elbow_TR, frame);
  sprites.drawOverwrite(96,   0, logo_elbow_LB, frame);
  sprites.drawOverwrite(80,   0, logo_straight_LR_noflange, frame);
  sprites.drawOverwrite(64,   0, logo_straight_LR, frame);
  sprites.drawOverwrite(48,   0, logo_elbow_RB, frame);
  sprites.drawOverwrite(48,  16, logo_straight_TB_noflange, frame);
  sprites.drawOverwrite(48,  32, logo_elbow_TR, frame);
  sprites.drawOverwrite(64,  32, logo_elbow_LB, frame);
  sprites.drawOverwrite(64,  48, logo_straight_TB_noflange, frame);

  sprites.drawOverwrite(0,    0, logo_straight_TB_noflange, frame);
  sprites.drawOverwrite(0,   16, logo_straight_TB, frame);
  sprites.drawOverwrite(0,   32, logo_elbow_TR, frame);
  sprites.drawOverwrite(16,  32, logo_straight_LR, frame);
  sprites.drawOverwrite(32,  32, logo_elbow_TL, frame);
  sprites.drawOverwrite(32,  16, logo_elbow_RB, frame);
  sprites.drawOverwrite(48,  16, logo_cross_underlap_hflange, frame);
  sprites.drawOverwrite(64,  16, logo_straight_LR_noflange, frame);
  sprites.drawOverwrite(80,  16, logo_elbow_LB, frame);
  sprites.drawOverwrite(80,  32, logo_elbow_TR, frame);
  sprites.drawOverwrite(96,  32, logo_straight_LR, frame);
  sprites.drawOverwrite(112, 32, logo_straight_LR_noflange, frame);

  sprites.drawOverwrite(0,    0, logo_cross_underlap, frame);
  sprites.drawOverwrite(16,   0, logo_elbow_LB, frame);
  sprites.drawOverwrite(16,  16, logo_straight_TB, frame);
  sprites.drawOverwrite(16,  32, logo_cross_overlap_hflange, frame);
  sprites.drawOverwrite(16,  48, logo_elbow_TR, frame);
  sprites.drawOverwrite(32,  48, logo_straight_LR, frame);
  sprites.drawOverwrite(48,  48, logo_straight_LR_noflange, frame);
  sprites.drawOverwrite(64,  48, logo_cross_underlap_hflange, frame);
  sprites.drawOverwrite(80,  48, logo_straight_LR_noflange, frame);
  sprites.drawOverwrite(96,  48, logo_elbow_LB, frame);
  arduboy.display();

  
  // Play 'puzzle solved' tune before the message is shown ..

  playPuzzleSolved();
  arduboy.delayShort(1000);

  arduboy.setTextColor(BLACK);
  arduboy.setTextBackground(WHITE);

  arduboy.fillRect(12, 23, 104, 18, BLACK);
  arduboy.fillRect(13, 24, 102, 16, WHITE);
  
  if (puzzle.index == getNumberOfPuzzles(puzzle.level) - 1) {
  
    arduboy.setCursor(21, 28);
    arduboy.print("Level Finished!");
    gameState = STATE_LEVEL_SELECT;
  
  }
  else {
   
    arduboy.setCursor(18, 28);
    arduboy.print("Congratulations!");
    gameState = STATE_INIT_GAME;

  }

  puzzle.index++;
  updateEEPROM(puzzle.level, puzzle.index);
  
  arduboy.display();
  arduboy.setTextColor(WHITE);
  arduboy.setTextBackground(BLACK);

  gameOverDelay(1000);
  
}


/* ----------------------------------------------------------------------------
 *   Delay the screen for a period of time.  
 *   
 *   The delay can be cancelled by clicking either the A or B button.
 */
void gameOverDelay(int delayLength) {

  arduboy.pollButtons();

  while (delayLength >= 0) {

    if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) { break; /* return true;*/ }
    
    arduboy.delayShort(5);  
    delayLength--;

  }
  
}

