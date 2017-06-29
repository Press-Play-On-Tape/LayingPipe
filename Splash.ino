#define ANIMATION_DELAY_SHORT     20

void drawSplash() { 

  bool skipSplash = false;
  
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

  skipSplash = splashDelay(300, skipSplash);

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

  skipSplash = splashDelay(300, skipSplash);

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

  skipSplash = splashDelay(500, skipSplash);
  
  gameState = STATE_GAME_INIT_GAME;
  
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

      if (arduboy.audio.enabled()) {
      
        arduboy.audio.off(); 
        arduboy.audio.saveOnOff();

      }
      else {
      
        arduboy.audio.on(); 
        arduboy.audio.saveOnOff();
        
      }

      arduboy.display();
        
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

    if (arduboy.justPressed(A_BUTTON)) { Serial.println("a2"); return true; }

    if (arduboy.justPressed(B_BUTTON)) { 

      if (arduboy.audio.enabled()) {
      
        arduboy.audio.off(); 
        arduboy.audio.saveOnOff();

      }
      else {
      
        arduboy.audio.on(); 
        arduboy.audio.saveOnOff();
        
      }

      arduboy.display();
        
    }
    
    arduboy.delayShort(5);  
    delayLength--;

  }

  return false;
  
}

void drawGameOver() { 
  
  arduboy.clear();
  arduboy.setCursor(12, 30);
  arduboy.print("Congratulations !");
  arduboy.display();

  playPuzzleSolved();
  delay(2000);

  puzzleIdx++;
  gameState = STATE_GAME_INIT_GAME;
  
}
