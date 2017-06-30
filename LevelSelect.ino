
#define MENU_ITEM_1_X          50
#define MENU_ITEM_1_Y          12
#define MENU_ITEM_2_X          MENU_ITEM_1_X
#define MENU_ITEM_2_Y          24
#define MENU_ITEM_3_X          MENU_ITEM_1_X
#define MENU_ITEM_3_Y          26
#define MENU_ITEM_4_X          MENU_ITEM_1_X
#define MENU_ITEM_4_Y          48
#define MENU_ITEM_WIDTH        60
#define MENU_ITEM_HEIGHT       16

byte levelSelect_selectedItem = 0;
byte levelSelect_topItem = 0;
byte levelSelect_noOfItem = 4;
byte puzzleSelect_selectedItem = 0;

void levelSelect() {

  arduboy.clear();
  
  if (arduboy.justPressed(UP_BUTTON) && levelSelect_selectedItem > 0) 					        { levelSelect_selectedItem--; }
  if (arduboy.justPressed(DOWN_BUTTON) && levelSelect_selectedItem < sizeof(levels)) 	  { levelSelect_selectedItem++; }
  if (arduboy.justPressed(B_BUTTON)) 												                            { gameState = STATE_GAME_INTRO; }
  
  if (arduboy.justPressed(A_BUTTON)) { 
	  
	  puzzleType = levels[levelSelect_selectedItem];
	  puzzleIdx = 0;
	  gameState = STATE_GAME_PUZZLE_SELECT;
	  
  }
  
  
  // Adjust the top menu item based on selected item ..
  
  if (levelSelect_selectedItem < levelSelect_noOfItem) {

	  levelSelect_topItem = 0;

  }
  else {

    if (levelSelect_selectedItem > sizeof(levels) - levelSelect_noOfItem) {

      levelSelect_topItem = sizeof(levels) - levelSelect_noOfItem - 1;

  	}
  	else {
   
      levelSelect_topItem = levelSelect_selectedItem - levelSelect_noOfItem + 1;
          
  	}

  }
	
  
  // Render menu ..
  
  renderLevelDetail(MENU_ITEM_1_X, MENU_ITEM_1_Y, levelSelect_topItem, (levelSelect_topItem == levelSelect_selectedItem));
  renderLevelDetail(MENU_ITEM_2_X, MENU_ITEM_2_Y, levelSelect_topItem, (levelSelect_topItem + 1 == levelSelect_selectedItem));
  renderLevelDetail(MENU_ITEM_3_X, MENU_ITEM_3_Y, levelSelect_topItem, (levelSelect_topItem + 2 == levelSelect_selectedItem));
  renderLevelDetail(MENU_ITEM_4_X, MENU_ITEM_4_Y, levelSelect_topItem, (levelSelect_topItem + 3 == levelSelect_selectedItem));
    
}

void renderLevelDetail(byte x, byte y, byte level, byte highlight) {

  if (highlight) {
	  
	arduboy.setTextColor(BLACK);
	arduboy.setTextBackground(WHITE);
	arduboy.fillRect(x - 2, y - 2, MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT, WHITE);
	  
  }
	
  arduboy.setCursor(MENU_ITEM_1_X, MENU_ITEM_1_Y);
  
  switch (level) {
  
  	case PUZZLE_5X5:
  		arduboy.print("Practice  ");
  		arduboy.print(readEEPROM(PUZZLE_5X5));
  		arduboy.print(" of ");
  		arduboy.print(puzzles_5x5_count);
  		break;
  	  
  	case PUZZLE_6X6:
  		arduboy.print("Easy     ");
  		arduboy.print(readEEPROM(PUZZLE_6X6));
  		arduboy.print(" of ");
  		arduboy.print(puzzles_6x6_count);
  		break;
  	  
  	case PUZZLE_7X7:
  		arduboy.print("Medium   ");
  		arduboy.print(readEEPROM(PUZZLE_7X7));
  		arduboy.print(" of ");
  		arduboy.print(puzzles_7x7_count);
  		break;
  	  
  	case PUZZLE_8X8:
  		arduboy.print("Hard     ");
  		arduboy.print(readEEPROM(PUZZLE_8X8));
  		arduboy.print(" of ");
  		arduboy.print(puzzles_8x8_count);
  		break;
  	  
  	case PUZZLE_9X9:
  		arduboy.print("Extreme  ");
  		arduboy.print(readEEPROM(PUZZLE_9X9));
  		arduboy.print(" of ");
  		arduboy.print(PUZZLE_9X9);
  		break;  		
  }
  
  arduboy.setTextColor(WHITE);
  arduboy.setTextBackground(BLACK);
  
}


void puzzleSelect() {

  arduboy.clear();
  
  if (arduboy.justPressed(UP_BUTTON) && puzzleSelect_selectedItem > 0)         { puzzleSelect_selectedItem--; }
  if (arduboy.justPressed(DOWN_BUTTON) && puzzleSelect_selectedItem < 1)       { puzzleSelect_selectedItem++; }
  if (arduboy.justPressed(B_BUTTON))                                           { gameState = STATE_GAME_LEVEL_SELECT; }
  
  if (arduboy.justPressed(A_BUTTON)) { 
	  
	  if (puzzleSelect_selectedItem == 1) {
		  
		  puzzleIdx = 0;
		  
	  }
	  
	  if (puzzleSelect_selectedItem == 1) {
		  
		  puzzleIdx = readEEPROM(puzzleType);
		  
	  }
	  
	  gameState = STATE_GAME_INIT_GAME;
	  
  }
  
	
  
  // Render menu ..
  
  renderPuzzleOption(MENU_ITEM_2_X, MENU_ITEM_2_Y, "Continue Playing", (puzzleSelect_selectedItem == 0));
  renderPuzzleOption(MENU_ITEM_3_X, MENU_ITEM_3_Y, "  Reset Level", (puzzleSelect_selectedItem == 1));
    
}


void renderPuzzleOption(byte x, byte y, String message, byte highlight) {

  if (highlight) {
	  
	arduboy.setTextColor(BLACK);
	arduboy.setTextBackground(WHITE);
	arduboy.fillRect(x - 2, y - 2, MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT, WHITE);
	  
  }
	
  arduboy.setCursor(MENU_ITEM_1_X, MENU_ITEM_1_Y);
  arduboy.print(message);
  
  arduboy.setTextColor(WHITE);
  arduboy.setTextBackground(BLACK);
  
}
