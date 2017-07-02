void drawGameOver() { 
  
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

  arduboy.delayShort(1000);

  arduboy.setTextColor(BLACK);
  arduboy.setTextBackground(WHITE);

  arduboy.fillRect(12, 23, 104, 18, WHITE);
  
  if (puzzleIdx == getNumberOfPuzzles(puzzleType) - 1) {
  
    arduboy.setCursor(21, 28);
    arduboy.print("Level Finished!");
    gameState = STATE_GAME_LEVEL_SELECT;
  
  }
  else {
   
    arduboy.setCursor(18, 28);
    arduboy.print("Congratulations!");
    gameState = STATE_GAME_INIT_GAME;

  }

  puzzleIdx++;
  updateEEPROM(puzzleType, puzzleIdx);
  
  arduboy.display();
  arduboy.setTextColor(WHITE);
  arduboy.setTextBackground(BLACK);

  playPuzzleSolved();

  gameOverDelay(1000, false);

  
}

bool gameOverDelay(int delayLength, bool skip) {

  if (skip) return true;

  arduboy.pollButtons();

  while (delayLength >= 0) {

    if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) { return true; }
    
    arduboy.delayShort(5);  
    delayLength--;

  }

  return false;
  
}

