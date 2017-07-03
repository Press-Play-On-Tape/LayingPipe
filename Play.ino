/* ----------------------------------------------------------------------------
 *   Initialise the game based on the selected level and puzzle numbers.
 */
void play_InitGame() {

  arduboy.clear();
  initBoard(puzzle.level, puzzle.index);
  gameState = STATE_GAME_NO_SELECTION;
  
}


/* ----------------------------------------------------------------------------
 *   Handle the game play before the user selects a node.
 *   
 *   The user can scroll to any node on the board using the directional arrows.
 *   Clicking the A button on a node selects it.  Clicking the B button returns
 *   the user to the level select (if currently on the first puzzle) or the 
 *   puzzle select screen (if they are currently working on a puzzle).
 */
void play_NoSelection() {

  if (arduboy.justPressed(LEFT_BUTTON) && player.highlightedNode.x > 0)                         { player.highlightedNode.x--; }
  if (arduboy.justPressed(RIGHT_BUTTON) && player.highlightedNode.x < puzzle.maximum.x - 1)     { player.highlightedNode.x++; }
  if (arduboy.justPressed(UP_BUTTON) && player.highlightedNode.y > 0)                           { player.highlightedNode.y--; }
  if (arduboy.justPressed(DOWN_BUTTON) && player.highlightedNode.y < puzzle.maximum.y - 1)      { player.highlightedNode.y++; }

  if (arduboy.justPressed(A_BUTTON) && isNode(player.highlightedNode.x, player.highlightedNode.y)) {

    if (nodeAlreadyPlayed(getNodeValue(player.highlightedNode.x, player.highlightedNode.y))) {

      clearBoard(getNodeValue(player.highlightedNode.x, player.highlightedNode.y));
      player.selectedNode.value = getNodeValue(player.highlightedNode.x, player.highlightedNode.y);
      player.selectedNode.x = player.highlightedNode.x;
      player.selectedNode.y = player.highlightedNode.y;
      gameState = STATE_GAME_NODE_SELECTED;

    }
    else {

      player.selectedNode.value = getNodeValue(player.highlightedNode.x, player.highlightedNode.y);
      player.selectedNode.x = player.highlightedNode.x;
      player.selectedNode.y = player.highlightedNode.y;
      gameState = STATE_GAME_NODE_SELECTED;
      playSelectNodeTune();

    }

  }

  if (arduboy.justPressed(B_BUTTON)) {

    if (puzzle.index == 0) {
        
      gameState = STATE_GAME_LEVEL_SELECT;
      prevState = STATE_GAME_NO_SELECTION;

    }
    else {
        
      gameState = STATE_GAME_PUZZLE_SELECT;
      prevState = STATE_GAME_NO_SELECTION;
        
    }
      
  }
  
  renderBoard(puzzle.offset.x, puzzle.offset.y - calculateTopRow() * GRID_HEIGHT, calculateTopRow());
  
}


/* ----------------------------------------------------------------------------
 *   Calculate the top row of the puzzle to render.
 *   
 *   Games greater than 5 x 5 cannot be rendered on the screen completely.  The
 *   top row to display is calculated based on the player's highlighted cell.
 */
byte calculateTopRow() {

  byte topRow = 0;

  if (player.highlightedNode.y <= 2) {

    topRow = 0;

  }
  else {

    if (player.highlightedNode.y>=3 && player.highlightedNode.y <= puzzle.maximum.y - 4) { 

      topRow = player.highlightedNode.y - 2; 

    }
    else {
    
      topRow = (puzzle.maximum.y - 5 >= 0 ? puzzle.maximum.y - 5 : 0); 

    }

  }

  return topRow;
  
}


/* ----------------------------------------------------------------------------
 *   Handle the game play after the user selects a node.
 *   
 *   The user can only navigate through empty cells or onto the node that matches
 *   the one previously selected.  They can also back-track along the pipe they
 *   have already layed.
 *   
 *   Pressing the B button will clear the pipe that is currently being layed.
 */
void play_NodeSelected() {

  if (arduboy.justPressed(LEFT_BUTTON)) {
    
    if (validMove(LEFT, player.selectedNode, player.highlightedNode.x - 1, player.highlightedNode.y)) {

      switch (getPipeValue(player.highlightedNode.x, player.highlightedNode.y)) {

        case PIPE_HORIZONTAL_LR:
        case PIPE_CORNER_TR:
        case PIPE_CORNER_BR:
          updatePipeWhenReversing(player.highlightedNode.x - 1, player.highlightedNode.y);
          setPipeValue(player.highlightedNode.x, player.highlightedNode.y, NOTHING, NOTHING);
          break;

        case PIPE_HORIZONTAL_RL:
        case PIPE_CORNER_TL:
        case PIPE_CORNER_BL:
          if (!isNode(player.highlightedNode.x - 1, player.highlightedNode.y)) { setPipeValue(player.highlightedNode.x - 1, player.highlightedNode.y, PIPE_HORIZONTAL_RL, player.selectedNode.value); }
          break;

        case PIPE_CORNER_LT:
        case PIPE_CORNER_RT:
        case PIPE_VERTICAL_BT:
          if (!isNode(player.highlightedNode.x - 1, player.highlightedNode.y)) { setPipeValue(player.highlightedNode.x - 1, player.highlightedNode.y, PIPE_HORIZONTAL_RL, player.selectedNode.value); }
          setPipeValue(player.highlightedNode.x, player.highlightedNode.y, PIPE_CORNER_BL, player.selectedNode.value);
          break;

        case PIPE_CORNER_LB:
        case PIPE_CORNER_RB:
        case PIPE_VERTICAL_TB:
          if (!isNode(player.highlightedNode.x - 1, player.highlightedNode.y)) { setPipeValue(player.highlightedNode.x - 1, player.highlightedNode.y, PIPE_HORIZONTAL_RL, player.selectedNode.value); }
          setPipeValue(player.highlightedNode.x, player.highlightedNode.y, PIPE_CORNER_TL, player.selectedNode.value);
          break;

        case NODE:
          setPipeValue(player.highlightedNode.x - 1, player.highlightedNode.y, PIPE_HORIZONTAL_RL, player.selectedNode.value);
          break;

      }
  
  
      // Have we selected the original node?  If so clear the board of this pipe ..
      
      if (player.highlightedNode.x - 1 == player.selectedNode.x && player.highlightedNode.y == player.selectedNode.y) {
    
        clearBoard(player.selectedNode.value);
        clearSelection();
        gameState = STATE_GAME_NO_SELECTION;
        playClearSelectionTune();
          
      }
  
  
      // Have we selected a pair node?  
      
      if (isNode(player.highlightedNode.x - 1, player.highlightedNode.y)  && getNodeValue(player.highlightedNode.x - 1, player.highlightedNode.y) == player.selectedNode.value) {
    
        clearSelection();
        gameState = STATE_GAME_NO_SELECTION;
        playMatchNodeTune();
 

        // Is the level finished ?

        if (isPuzzleComplete()) {

          gameState = STATE_GAME_GAME_OVER;
    
        }
                 
      }  
      
      player.highlightedNode.x--;
      
    }
    
  }

  if (arduboy.justPressed(RIGHT_BUTTON)) {
    
    if (validMove(RIGHT, player.selectedNode, player.highlightedNode.x + 1, player.highlightedNode.y)) {

      switch (getPipeValue(player.highlightedNode.x, player.highlightedNode.y)) {

        case PIPE_HORIZONTAL_RL:
        case PIPE_CORNER_TL:
        case PIPE_CORNER_BL:
          updatePipeWhenReversing(player.highlightedNode.x + 1, player.highlightedNode.y);
          setPipeValue(player.highlightedNode.x, player.highlightedNode.y, NOTHING, NOTHING);
          break;

        case PIPE_HORIZONTAL_LR:
        case PIPE_CORNER_TR:
        case PIPE_CORNER_BR:
          if (!isNode(player.highlightedNode.x + 1, player.highlightedNode.y)) { setPipeValue(player.highlightedNode.x + 1, player.highlightedNode.y, PIPE_HORIZONTAL_LR, player.selectedNode.value); }
          break;

        case PIPE_CORNER_RT:
        case PIPE_CORNER_LT:
        case PIPE_VERTICAL_BT:
          if (!isNode(player.highlightedNode.x + 1, player.highlightedNode.y)) { setPipeValue(player.highlightedNode.x + 1, player.highlightedNode.y, PIPE_HORIZONTAL_LR, player.selectedNode.value); }
          setPipeValue(player.highlightedNode.x, player.highlightedNode.y, PIPE_CORNER_BR, player.selectedNode.value);
          break;

        case PIPE_CORNER_RB:
        case PIPE_CORNER_LB:
        case PIPE_VERTICAL_TB:
          if (!isNode(player.highlightedNode.x + 1, player.highlightedNode.y)) { setPipeValue(player.highlightedNode.x + 1, player.highlightedNode.y, PIPE_HORIZONTAL_LR, player.selectedNode.value); }
          setPipeValue(player.highlightedNode.x, player.highlightedNode.y, PIPE_CORNER_TR, player.selectedNode.value);
          break;

        case NODE:
          setPipeValue(player.highlightedNode.x + 1, player.highlightedNode.y, PIPE_HORIZONTAL_LR, player.selectedNode.value);
          break;

      }
  
  
      // Have we selected the original node?  If so clear the board of this pipe ..
      
      if (player.highlightedNode.x + 1 == player.selectedNode.x && player.highlightedNode.y == player.selectedNode.y) {
    
        clearBoard(player.selectedNode.value);
        clearSelection();
        gameState = STATE_GAME_NO_SELECTION;
        playClearSelectionTune();
          
      }
  
  
      // Have we selected a pair node?  
      
      if (isNode(player.highlightedNode.x + 1, player.highlightedNode.y)  && getNodeValue(player.highlightedNode.x + 1, player.highlightedNode.y) == player.selectedNode.value) {
    
        clearSelection();
        gameState = STATE_GAME_NO_SELECTION;
        playMatchNodeTune();
  

        // Is the level finished ?

        if (isPuzzleComplete()) {

          gameState = STATE_GAME_GAME_OVER;
    
        }
                
      }
    
      player.highlightedNode.x++;
  
    }

  }

  if (arduboy.justPressed(UP_BUTTON)) {
    
    if (validMove(UP, player.selectedNode, player.highlightedNode.x, player.highlightedNode.y - 1)) {

      switch (getPipeValue(player.highlightedNode.x, player.highlightedNode.y)) {

        case PIPE_VERTICAL_TB:
        case PIPE_CORNER_RB:
        case PIPE_CORNER_LB:
          updatePipeWhenReversing(player.highlightedNode.x, player.highlightedNode.y - 1);
          setPipeValue(player.highlightedNode.x, player.highlightedNode.y, NOTHING, NOTHING);
          break;

        case PIPE_VERTICAL_BT:
        case PIPE_CORNER_LT:
        case PIPE_CORNER_RT:
          if (!isNode(player.highlightedNode.x, player.highlightedNode.y - 1)) { setPipeValue(player.highlightedNode.x, player.highlightedNode.y - 1, PIPE_VERTICAL_BT, player.selectedNode.value); }
          break;

        case PIPE_CORNER_TR:
        case PIPE_CORNER_BR:
        case PIPE_HORIZONTAL_LR:
          if (!isNode(player.highlightedNode.x, player.highlightedNode.y - 1)) { setPipeValue(player.highlightedNode.x, player.highlightedNode.y - 1, PIPE_VERTICAL_BT, player.selectedNode.value); }
          setPipeValue(player.highlightedNode.x, player.highlightedNode.y, PIPE_CORNER_LT, player.selectedNode.value); 
          break;

        case PIPE_CORNER_TL:
        case PIPE_CORNER_BL:
        case PIPE_HORIZONTAL_RL:
          if (!isNode(player.highlightedNode.x, player.highlightedNode.y - 1)) { setPipeValue(player.highlightedNode.x, player.highlightedNode.y - 1, PIPE_VERTICAL_BT, player.selectedNode.value); }
          setPipeValue(player.highlightedNode.x, player.highlightedNode.y, PIPE_CORNER_RT, player.selectedNode.value);
          break;

        case NODE:
          setPipeValue(player.highlightedNode.x, player.highlightedNode.y - 1, PIPE_VERTICAL_BT, player.selectedNode.value);
          break;

      }
  
  
      // Have we selected the original node?  If so clear the board of this pipe ..
      
      if (player.highlightedNode.x == player.selectedNode.x && player.highlightedNode.y - 1 == player.selectedNode.y) {
    
        clearBoard(player.selectedNode.value);
        clearSelection();
        gameState = STATE_GAME_NO_SELECTION;
        playClearSelectionTune();
         
      }
  
  
      // Have we selected a pair node?  
      
      if (isNode(player.highlightedNode.x, player.highlightedNode.y - 1)  && getNodeValue(player.highlightedNode.x, player.highlightedNode.y - 1) == player.selectedNode.value) {
    
        clearSelection();
        gameState = STATE_GAME_NO_SELECTION;
        playMatchNodeTune();
 

        // Is the level finished ?

        if (isPuzzleComplete()) {

          gameState = STATE_GAME_GAME_OVER;
    
        }
                 
      }  
    
      player.highlightedNode.y--;
    }

  }

  if (arduboy.justPressed(DOWN_BUTTON)) {
    
    if (validMove(DOWN, player.selectedNode, player.highlightedNode.x, player.highlightedNode.y + 1)) {

      switch (getPipeValue(player.highlightedNode.x, player.highlightedNode.y)) {

        case PIPE_VERTICAL_BT:
        case PIPE_CORNER_RT:
        case PIPE_CORNER_LT:
          updatePipeWhenReversing(player.highlightedNode.x, player.highlightedNode.y + 1);
          setPipeValue(player.highlightedNode.x, player.highlightedNode.y, NOTHING, NOTHING);
          break;

        case PIPE_VERTICAL_TB:
        case PIPE_CORNER_LB:
        case PIPE_CORNER_RB:
          if (!isNode(player.highlightedNode.x, player.highlightedNode.y + 1)) { setPipeValue(player.highlightedNode.x, player.highlightedNode.y + 1, PIPE_VERTICAL_TB, player.selectedNode.value); }
          break;

        case PIPE_CORNER_TR:
        case PIPE_CORNER_BR:
        case PIPE_HORIZONTAL_LR:
          if (!isNode(player.highlightedNode.x, player.highlightedNode.y + 1)) { setPipeValue(player.highlightedNode.x, player.highlightedNode.y + 1, PIPE_VERTICAL_TB, player.selectedNode.value); }
          setPipeValue(player.highlightedNode.x, player.highlightedNode.y, PIPE_CORNER_LB, player.selectedNode.value);
          break;

        case PIPE_CORNER_TL:
        case PIPE_CORNER_BL:
        case PIPE_HORIZONTAL_RL:
          if (!isNode(player.highlightedNode.x, player.highlightedNode.y + 1)) { setPipeValue(player.highlightedNode.x, player.highlightedNode.y + 1, PIPE_VERTICAL_TB, player.selectedNode.value); }
          setPipeValue(player.highlightedNode.x, player.highlightedNode.y, PIPE_CORNER_RB, player.selectedNode.value);
          break;

        case NODE:
          setPipeValue(player.highlightedNode.x, player.highlightedNode.y + 1, PIPE_VERTICAL_TB, player.selectedNode.value);
          break;
        
      }

  
      // Have we selected the original node?  If so clear the board of this pipe ..
      
      if (player.highlightedNode.x == player.selectedNode.x && player.highlightedNode.y + 1 == player.selectedNode.y) {
    
        clearBoard(player.selectedNode.value);
        clearSelection();
        gameState = STATE_GAME_NO_SELECTION;
        playClearSelectionTune();
          
      }
   
  
      // Have we selected a pair node?  
      
      if (isNode(player.highlightedNode.x, player.highlightedNode.y + 1)  && getNodeValue(player.highlightedNode.x, player.highlightedNode.y + 1) == player.selectedNode.value) {
    
        clearSelection();
        gameState = STATE_GAME_NO_SELECTION;
        playMatchNodeTune();


        // Is the level finished ?

        if (isPuzzleComplete()) {

          gameState = STATE_GAME_GAME_OVER;
    
        }
  
      }  
   
      player.highlightedNode.y++;

    }

  }

  if (arduboy.justPressed(B_BUTTON)) {

    clearBoard(player.selectedNode.value);
    clearSelection();
    gameState = STATE_GAME_NO_SELECTION;
      
  }


  renderBoard(puzzle.offset.x, puzzle.offset.y - calculateTopRow() * GRID_HEIGHT, calculateTopRow());
  
}

void updatePipeWhenReversing(byte x, byte y) {

  switch (getPipeValue(x, y)) {

    case PIPE_CORNER_TR:           
    case PIPE_CORNER_TL:                   
    case PIPE_VERTICAL_TB:                 
      setPipeValue(x, y, PIPE_VERTICAL_TB, player.selectedNode.value);
      break;

    case PIPE_CORNER_BR:          
    case PIPE_CORNER_BL:          
    case PIPE_VERTICAL_BT:        
      setPipeValue(x, y, PIPE_VERTICAL_BT, player.selectedNode.value);
      break;

    case PIPE_CORNER_LT:
    case PIPE_CORNER_LB:
    case PIPE_HORIZONTAL_LR:
      setPipeValue(x, y, PIPE_HORIZONTAL_LR, player.selectedNode.value);
      break;
           
    case PIPE_CORNER_RT:                   
    case PIPE_CORNER_RB: 
    case PIPE_HORIZONTAL_RL:        
      setPipeValue(x, y, PIPE_HORIZONTAL_RL, player.selectedNode.value);
      break;
 
  }
 
}


/* ----------------------------------------------------------------------------
 *   Is the nominated move valid?
 *   
 *   The user can only navigate through empty cells or onto the node that matches
 *   the one previously selected.  They can also back-track along the pipe they
 *   have already layed.
 *   
 *   direction:     The button the user clicked, eg. UP, DOWN, LEFT and Right.
 *   selectedNode:  The node previously selected.
 *   x and y:       Coordinates to test.
 */
bool validMove(byte direction, Node selectedNode, byte x, byte y) {

  
  // Off the grid!

  if (x < 0 || x >= puzzle.maximum.x || y < 0 || y >= puzzle.maximum.y) return false;
  
  
  // Is it a clear cell or the matching node?
  
  if (
      (!isNode(x,y) && getPipeValue(x,y) == NOTHING) ||
      (isNode(x,y) && getNodeValue(x,y) == selectedNode.value && (x != selectedNode.x || y != selectedNode.y))
     ) return true;
  

  // Is the pipe turning back on itself?

  switch (direction) {

    case (UP):
    
      switch (getPipeValue(player.highlightedNode.x, player.highlightedNode.y)) {

        case PIPE_VERTICAL_TB:
        case PIPE_CORNER_RB:
        case PIPE_CORNER_LB:
          return true;

      }

      break;
      
    case (DOWN):
    
      switch (getPipeValue(player.highlightedNode.x, player.highlightedNode.y)) {
          
        case PIPE_VERTICAL_BT:
        case PIPE_CORNER_LT:
        case PIPE_CORNER_RT:
          return true;

      }

      break;

    case (LEFT):
    
      switch (getPipeValue(player.highlightedNode.x, player.highlightedNode.y)) {
   
        case PIPE_CORNER_TR:
        case PIPE_CORNER_BR:
        case PIPE_HORIZONTAL_LR:
          return true;

      }

      break;

    case (RIGHT):
    
      switch (getPipeValue(player.highlightedNode.x, player.highlightedNode.y)) {

        case PIPE_CORNER_TL:
        case PIPE_CORNER_BL:
        case PIPE_HORIZONTAL_RL:
          return true;

      }

      break;

  }
  
  return false;
  
}
