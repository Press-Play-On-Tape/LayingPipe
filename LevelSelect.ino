
#define MENU_ITEM_3_X          19
#define MENU_ITEM_3_1_Y        19
#define MENU_ITEM_3_2_Y        29
#define MENU_ITEM_3_3_Y        39
#define MENU_ITEM_3_WIDTH      92   
#define MENU_ITEM_3_HEIGHT     9

#define MENU_ITEM_2_X          17
#define MENU_ITEM_2_1_Y        23
#define MENU_ITEM_2_2_Y        35
#define MENU_ITEM_2_WIDTH      98   
#define MENU_ITEM_2_HEIGHT     11


byte levelSelect_selectedItem = 0;
byte levelSelect_topItem = 0;
byte levelSelect_noOfItem = 3;
byte puzzleSelect_selectedItem = 0;

void levelSelect() {

  clearHighlightAndSelection();

  arduboy.clear();
  
  sprites.drawOverwrite(-2, -2, logo_elbow_RB, frame);
  sprites.drawOverwrite(14, -2, logo_straight_LR, frame);
  sprites.drawOverwrite(30, -2, logo_straight_LR_noflange, frame);
  sprites.drawOverwrite(46, -2, logo_straight_LR, frame);
  sprites.drawOverwrite(62, -2, logo_straight_LR_noflange, frame);
  sprites.drawOverwrite(78, -2, logo_straight_LR_noflange, frame);
  sprites.drawOverwrite(80, -2, logo_straight_LR, frame);
  sprites.drawOverwrite(84, -2, logo_straight_LR_noflange, frame);
  sprites.drawOverwrite(100, -2, logo_straight_LR_noflange, frame);
  sprites.drawOverwrite(114, -2, logo_elbow_LB, frame);

  sprites.drawOverwrite(-2, 14, logo_straight_TB, frame);
  sprites.drawOverwrite(-2, 24, logo_straight_TB_noflange, frame);
  sprites.drawOverwrite(-2, 17, logo_straight_TB, frame);
  sprites.drawOverwrite(-2, 36, logo_straight_TB, frame);

  sprites.drawOverwrite(114, 14, logo_straight_TB, frame);
  sprites.drawOverwrite(114, 24, logo_straight_TB_noflange, frame);
  sprites.drawOverwrite(114, 17, logo_straight_TB, frame);
  sprites.drawOverwrite(114, 36, logo_straight_TB, frame);

  sprites.drawOverwrite(-2, 52, logo_elbow_TR, frame);
  sprites.drawOverwrite(14, 52, logo_straight_LR, frame);
  sprites.drawOverwrite(30, 52, logo_straight_LR_noflange, frame);
  sprites.drawOverwrite(46, 52, logo_straight_LR, frame);
  sprites.drawOverwrite(62, 52, logo_straight_LR_noflange, frame);
  sprites.drawOverwrite(78, 52, logo_straight_LR_noflange, frame);
  sprites.drawOverwrite(80, 52, logo_straight_LR, frame);
  sprites.drawOverwrite(84, 52, logo_straight_LR_noflange, frame);
  sprites.drawOverwrite(100, 52, logo_straight_LR_noflange, frame);
  sprites.drawOverwrite(114, 52, logo_elbow_TL, frame);


  
  if (arduboy.justPressed(UP_BUTTON) && levelSelect_selectedItem > 0) 					            { levelSelect_selectedItem--; }
  if (arduboy.justPressed(DOWN_BUTTON) && levelSelect_selectedItem < sizeof(levels) - 1) 	  { levelSelect_selectedItem++; }
  if (arduboy.justPressed(B_BUTTON)) 												                                { gameState = STATE_GAME_INTRO; }
  
  if (arduboy.justPressed(A_BUTTON)) { 
	  
	  puzzleType = levels[levelSelect_selectedItem];
	  puzzleIdx = 0;

    if (readEEPROM(puzzleType) > 0) {
      
  	  gameState = STATE_GAME_PUZZLE_SELECT;
      prevState = STATE_GAME_LEVEL_SELECT;
      puzzleSelect_selectedItem = 0;
     
    }
    else {
      
      gameState = STATE_GAME_INIT_GAME;
      
    }
	  
  }
  
  
  // Adjust the top menu item based on selected item ..
  
  if (levelSelect_selectedItem < levelSelect_noOfItem - 1) {

	  levelSelect_topItem = 0;

  }
  else {

    if (levelSelect_selectedItem > sizeof(levels) - levelSelect_noOfItem + 1) {

      levelSelect_topItem = sizeof(levels) - levelSelect_noOfItem;

  	}
  	else {
   
      levelSelect_topItem = levelSelect_selectedItem - 1;
          
  	}

  }
	
  
  // Render menu ..
  
  renderLevelDetail(MENU_ITEM_3_X, MENU_ITEM_3_1_Y, levels[levelSelect_topItem], (levelSelect_topItem == levelSelect_selectedItem));
  renderLevelDetail(MENU_ITEM_3_X, MENU_ITEM_3_2_Y, levels[levelSelect_topItem + 1], (levelSelect_topItem + 1 == levelSelect_selectedItem));
  renderLevelDetail(MENU_ITEM_3_X, MENU_ITEM_3_3_Y, levels[levelSelect_topItem + 2], (levelSelect_topItem + 2 == levelSelect_selectedItem));
    
}

void renderLevelDetail(byte x, byte y, byte level, byte highlight) {

  if (highlight) {
	  
  	arduboy.setTextColor(BLACK);
  	arduboy.setTextBackground(WHITE);
  	arduboy.fillRect(x - 1, y - 1, MENU_ITEM_3_WIDTH, MENU_ITEM_3_HEIGHT, WHITE);
	  
  }
	
  arduboy.setCursor(x, y);
  
  switch (level) {
  
  	case PUZZLE_5X5:
  		arduboy.print("Practice  ");
  		arduboy.print(readEEPROM(PUZZLE_5X5));
  		arduboy.print("/");
  		arduboy.print(puzzles_5x5_count);
  		break;
  	  
  	case PUZZLE_6X6:
  		arduboy.print("Easy      ");
  		arduboy.print(readEEPROM(PUZZLE_6X6));
      arduboy.print("/");
  		arduboy.print(puzzles_6x6_count);
  		break;
  	  
  	case PUZZLE_7X7:
  		arduboy.print("Medium    ");
  		arduboy.print(readEEPROM(PUZZLE_7X7));
      arduboy.print("/");
  		arduboy.print(puzzles_7x7_count);
  		break;
  	  
  	case PUZZLE_8X8:
  		arduboy.print("Hard      ");
  		arduboy.print(readEEPROM(PUZZLE_8X8));
      arduboy.print("/");
  		arduboy.print(puzzles_8x8_count);
  		break;
  	  
  	case PUZZLE_9X9:
  		arduboy.print("Extreme   ");
  		arduboy.print(readEEPROM(PUZZLE_9X9));
  		arduboy.print("/");
  		arduboy.print(puzzles_9x9_count);
  		break;  		
  }
  
  arduboy.setTextColor(WHITE);
  arduboy.setTextBackground(BLACK);
  
}


void puzzleSelect() {

  clearHighlightAndSelection();

  arduboy.clear();
 
  sprites.drawOverwrite(-2, -2, logo_elbow_RB, frame);
  sprites.drawOverwrite(14, -2, logo_straight_LR, frame);
  sprites.drawOverwrite(30, -2, logo_straight_LR_noflange, frame);
  sprites.drawOverwrite(46, -2, logo_straight_LR, frame);
  sprites.drawOverwrite(62, -2, logo_straight_LR_noflange, frame);
  sprites.drawOverwrite(78, -2, logo_straight_LR_noflange, frame);
  sprites.drawOverwrite(80, -2, logo_straight_LR, frame);
  sprites.drawOverwrite(84, -2, logo_straight_LR_noflange, frame);
  sprites.drawOverwrite(100, -2, logo_straight_LR_noflange, frame);
  sprites.drawOverwrite(114, -2, logo_elbow_LB, frame);

  sprites.drawOverwrite(-2, 14, logo_straight_TB, frame);
  sprites.drawOverwrite(-2, 24, logo_straight_TB_noflange, frame);
  sprites.drawOverwrite(-2, 17, logo_straight_TB, frame);
  sprites.drawOverwrite(-2, 36, logo_straight_TB, frame);

  sprites.drawOverwrite(114, 14, logo_straight_TB, frame);
  sprites.drawOverwrite(114, 24, logo_straight_TB_noflange, frame);
  sprites.drawOverwrite(114, 17, logo_straight_TB, frame);
  sprites.drawOverwrite(114, 36, logo_straight_TB, frame);

  sprites.drawOverwrite(-2, 52, logo_elbow_TR, frame);
  sprites.drawOverwrite(14, 52, logo_straight_LR, frame);
  sprites.drawOverwrite(30, 52, logo_straight_LR_noflange, frame);
  sprites.drawOverwrite(46, 52, logo_straight_LR, frame);
  sprites.drawOverwrite(62, 52, logo_straight_LR_noflange, frame);
  sprites.drawOverwrite(78, 52, logo_straight_LR_noflange, frame);
  sprites.drawOverwrite(80, 52, logo_straight_LR, frame);
  sprites.drawOverwrite(84, 52, logo_straight_LR_noflange, frame);
  sprites.drawOverwrite(100, 52, logo_straight_LR_noflange, frame);
  sprites.drawOverwrite(114, 52, logo_elbow_TL, frame);
   
  if (arduboy.justPressed(UP_BUTTON) && puzzleSelect_selectedItem > 0)         { puzzleSelect_selectedItem--; }
  if (arduboy.justPressed(DOWN_BUTTON) && puzzleSelect_selectedItem < 1)       { puzzleSelect_selectedItem++; }
  if (arduboy.justPressed(B_BUTTON))                                           { gameState = STATE_GAME_LEVEL_SELECT; }
  
  if (arduboy.justPressed(A_BUTTON)) { 
	  
	  if (puzzleSelect_selectedItem == 1) {
		  
		  puzzleIdx = 0;
      updateEEPROM(puzzleType, puzzleIdx);
      
	  }
	  
	  if (puzzleSelect_selectedItem == 0) {

		  puzzleIdx = (readEEPROM(puzzleType) == getNumberOfPuzzles(puzzleType) ? readEEPROM(puzzleType) -1 : readEEPROM(puzzleType));
		  
	  }
	  
	  gameState = STATE_GAME_INIT_GAME;
	  
  }
  
	
  
  // Render menu ..
  
  renderPuzzleOption(MENU_ITEM_2_X, MENU_ITEM_2_1_Y, (prevState == STATE_GAME_LEVEL_SELECT ? "Continue Playing" : " Restart Puzzle "), (puzzleSelect_selectedItem == 0));
  renderPuzzleOption(MENU_ITEM_2_X, MENU_ITEM_2_2_Y, "  Reset Level", (puzzleSelect_selectedItem == 1));
    
}


void renderPuzzleOption(byte x, byte y, String message, byte highlight) {

  if (highlight) {
	  
	arduboy.setTextColor(BLACK);
	arduboy.setTextBackground(WHITE);
	arduboy.fillRect(x - 1, y - 2, MENU_ITEM_2_WIDTH, MENU_ITEM_2_HEIGHT, WHITE);
	  
  }
	
  arduboy.setCursor(x, y);
  arduboy.print(message);
  
  arduboy.setTextColor(WHITE);
  arduboy.setTextBackground(BLACK);
  
}
