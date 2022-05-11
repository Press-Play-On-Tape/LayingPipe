#define ANIMATION_DELAY_SHORT     20


/* ----------------------------------------------------------------------------
 *   Render the Splash screen.
 *   
 *   The pipes are rendered one-by-one to simulate the laying of pipe.  The
 *   rendering function allows the user to press the A button to skip past the
 *   animations or the B button to toggle sounds.
 */
void drawSplash() { 

  bool skipSplash = false;
  
  arduboy.clear(); 
  sprites.drawOverwrite(120, 56, sound_icon, (arduboy.audio.enabled() ? 0 : 1));
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

  if (!skipSplash) {

    arduboy.fillRect(19, 18, 92, 30, BLACK);
    drawHorizontalDottedLine(20, 110, 19);
    drawHorizontalDottedLine(20, 110, 46);
    sprites.drawOverwrite(23, 21, logo, frame);
    arduboy.display();

    splashWaitForever();
    
  }

  gameState = STATE_LEVEL_SELECT;
  
}


/* ----------------------------------------------------------------------------
 *   Render the a single pipe animation.
 *   
 *   The pipes are rendered one-by-one to simulate the laying of pipe.  The
 *   rendering function allows the user to press the A button to skip past the
 *   animations or the B button to toggle sounds.
 */
bool splashAnimation(byte x, byte y, const uint8_t *bitmap, uint8_t frame, bool skip) {

  if (skip) return true;
  
  int i = ANIMATION_DELAY_SHORT;
  
  sprites.drawOverwrite(x, y, bitmap, frame);
  arduboy.display();
  
  playSplashTune();

  while (i >= 0) {

    arduboy.pollButtons();

    if (arduboy.justPressed(A_BUTTON)) { return true; }

    if (arduboy.justPressed(B_BUTTON)) { 

    	toggleSoundSettings();
      sprites.drawOverwrite(120, 56, sound_icon, (arduboy.audio.enabled() ? 0 : 1));
      arduboy.display();
    	
    }
    
    arduboy.delayShort(15);  
    i--;

  }

  return false;
  
}


/* ----------------------------------------------------------------------------
 *   Delay the screen for a period of time.  
 *   
 *   The delay can be cancelled by clicking either the A button.  Clicking the
 *   B button will toggle the sound on or off.
 */
bool splashDelay(int delayLength, bool skip) {

  if (skip) return true;


  while (delayLength >= 0) {

    arduboy.pollButtons();

    if (arduboy.justPressed(A_BUTTON)) { return true; }

    if (arduboy.justPressed(B_BUTTON)) { 

    	toggleSoundSettings();
      sprites.drawOverwrite(120, 56, sound_icon, (arduboy.audio.enabled() ? 0 : 1));
      arduboy.display();
        
    }
    
    arduboy.delayShort(5);  
    delayLength--;

  }

  return false;
  
}


/* ----------------------------------------------------------------------------
 *   Delay the screen forever.  
 *   
 *   The delay can be cancelled by clicking either the A button.  Clicking the
 *   B button will toggle the sound on or off.
 */
void splashWaitForever() {

  while (true) {

    arduboy.pollButtons();

    if (arduboy.justPressed(A_BUTTON)) { break; }

    if (arduboy.justPressed(B_BUTTON)) { 

      toggleSoundSettings();
      sprites.drawOverwrite(120, 56, sound_icon, (arduboy.audio.enabled() ? 0 : 1));
      arduboy.display();
       
    }
    
    arduboy.delayShort(5);  

  }
  
}
