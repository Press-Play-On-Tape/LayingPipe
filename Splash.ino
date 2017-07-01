#define ANIMATION_DELAY_SHORT     20

void drawSplash() { 

  bool skipSplash = false;
  
  arduboy.clear(); 
  arduboy.display();
    
  skipSplash = splashAnimation(112,  0, logo_straight_TB_noflange, frame, skipSplash);
  skipSplash = splashAnimation(112, 16, logo_elbow_TL, frame, skipSplash);
  skipSplash = splashAnimation(96,  16, logo_elbow_TR, frame, skipSplash);
  skipSplash = splashAnimation(96,   0, logo_elbow_LB, frame, skipSplash);
  skipSplash = splashAnimation(80,   0, logo_straight_LR_noflange, frame, skipSplash);
  skipSplash = splashAnimation(64,   0, logo_straight_LR, frame, skipSplash);
  skipSplash = splashAnimation(48,   0, logo_elbow_RB, frame, skipSplash);
  skipSplash = splashAnimation(48,  16, logo_straight_TB_noflange, frame, skipSplash);
  skipSplash = splashAnimation(48,  32, logo_elbow_TR, frame, skipSplash);
  skipSplash = splashAnimation(64,  32, logo_elbow_LB, frame, skipSplash);
  skipSplash = splashAnimation(64,  48, logo_straight_TB_noflange, frame, skipSplash);

  skipSplash = splashDelay(200, skipSplash);

  skipSplash = splashAnimation(0,    0, logo_straight_TB_noflange, frame, skipSplash);
  skipSplash = splashAnimation(0,   16, logo_straight_TB, frame, skipSplash);
  skipSplash = splashAnimation(0,   32, logo_elbow_TR, frame, skipSplash);
  skipSplash = splashAnimation(16,  32, logo_straight_LR, frame, skipSplash);
  skipSplash = splashAnimation(32,  32, logo_elbow_TL, frame, skipSplash);
  skipSplash = splashAnimation(32,  16, logo_elbow_RB, frame, skipSplash);
  skipSplash = splashAnimation(48,  16, logo_cross_underlap_hflange, frame, skipSplash);
  skipSplash = splashAnimation(64,  16, logo_straight_LR_noflange, frame, skipSplash);
  skipSplash = splashAnimation(80,  16, logo_elbow_LB, frame, skipSplash);
  skipSplash = splashAnimation(80,  32, logo_elbow_TR, frame, skipSplash);
  skipSplash = splashAnimation(96,  32, logo_straight_LR, frame, skipSplash);
  skipSplash = splashAnimation(112, 32, logo_straight_LR_noflange, frame, skipSplash);

  skipSplash = splashDelay(200, skipSplash);

  skipSplash = splashAnimation(0,    0, logo_cross_underlap, frame, skipSplash);
  skipSplash = splashAnimation(16,   0, logo_elbow_LB, frame, skipSplash);
  skipSplash = splashAnimation(16,  16, logo_straight_TB, frame, skipSplash);
  skipSplash = splashAnimation(16,  32, logo_cross_overlap_hflange, frame, skipSplash);
  skipSplash = splashAnimation(16,  48, logo_elbow_TR, frame, skipSplash);
  skipSplash = splashAnimation(32,  48, logo_straight_LR, frame, skipSplash);
  skipSplash = splashAnimation(48,  48, logo_straight_LR_noflange, frame, skipSplash);
  skipSplash = splashAnimation(64,  48, logo_cross_underlap_hflange, frame, skipSplash);
  skipSplash = splashAnimation(80,  48, logo_straight_LR_noflange, frame, skipSplash);
  skipSplash = splashAnimation(96,  48, logo_elbow_LB, frame, skipSplash);

  skipSplash = splashDelay(200, skipSplash);

  arduboy.setTextSize(2);
  arduboy.setCursor(22, 10);
  arduboy.print("Laying");
  arduboy.setCursor(50, 36);
  arduboy.print("Pipe");
  arduboy.display();
  arduboy.setTextSize(1);


  skipSplash = splashDelay(1000, skipSplash);

  
  gameState = STATE_GAME_LEVEL_SELECT;
  
}

bool splashAnimation(byte x, byte y, const uint8_t *bitmap, uint8_t frame, bool skip) {

  if (skip) return true;
  
  int i = ANIMATION_DELAY_SHORT;
  
  sprites.drawOverwrite(x, y, bitmap, frame);
  arduboy.display();
  arduboy.pollButtons();
  
  playSplashSound();

  while (i >= 0) {

    if (arduboy.justPressed(A_BUTTON)) { Serial.println("a1"); return true; }

    if (arduboy.justPressed(B_BUTTON)) { 

    	toggleSoundSettings();
    	
    }
    
    arduboy.delayShort(15);  
    i--;

  }

  return false;
  
}


bool splashDelay(int delayLength, bool skip) {

  if (skip) return true;

  arduboy.pollButtons();

  while (delayLength >= 0) {

    if (arduboy.justPressed(A_BUTTON)) { return true; }

    if (arduboy.justPressed(B_BUTTON)) { 

    	toggleSoundSettings();
        
    }
    
    arduboy.delayShort(5);  
    delayLength--;

  }

  return false;
  
}

void drawGameOver() { 
  
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

  delay(1000);

   arduboy.setTextColor(BLACK);
    arduboy.setTextBackground(WHITE);


  arduboy.fillRect(12, 23, 104, 18, WHITE);
  arduboy.setCursor(18, 28);
  arduboy.print("Congratulations!");
  arduboy.display();

  arduboy.setTextColor(WHITE);
  arduboy.setTextBackground(BLACK);



  puzzleIdx++;
  updateEEPROM(puzzleType, puzzleIdx);

  playPuzzleSolved();
  gameOverDelay(500, false);

  gameState = STATE_GAME_INIT_GAME;
  
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

