#include "Arduboy2.h" 
#include "Images.h"
#include "Puzzles.h"
#include "Puzzle.h"

Arduboy2 arduboy;
Sprites sprites;

byte board[9][9] = {
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};

struct SelectedNode {
  byte x;
  byte y;
  byte value;
};

struct Player
{
  byte x;
  byte y;
  SelectedNode selectedNode;
};

struct Puzzle
{
  byte maxX;
  byte maxY;
};

#define NOTHING                 0
#define PIPE_HORIZONTAL_LR      1
#define PIPE_HORIZONTAL_RL      2
#define PIPE_VERTICAL_TB        3
#define PIPE_VERTICAL_BT        4
#define PIPE_CORNER_TL          5
#define PIPE_CORNER_LT          6
#define PIPE_CORNER_TR          7
#define PIPE_CORNER_RT          8
#define PIPE_CORNER_BL          9
#define PIPE_CORNER_LB          10
#define PIPE_CORNER_BR          11
#define PIPE_CORNER_RB          12
#define NODE                    15

#define GRID_WIDTH              11
#define GRID_HEIGHT             11

#define UP                      0
#define DOWN                    1
#define LEFT                    2
#define RIGHT                   3

#define PUZZLE_5X5				5
#define PUZZLE_7X7				7
#define PUZZLE_9X9				9

const byte* const nodes[] = {node_0, node_1, node_2, node_3, node_4, node_5, node_6, node_7, node_8, node_9, node_10, node_11, node_12 };
const byte* const pipes[] = {pipe_nothing, pipe_horizontal, pipe_horizontal, pipe_vertical, pipe_vertical, pipe_corner_TL, pipe_corner_TL, pipe_corner_TR, pipe_corner_TR, pipe_corner_BL, pipe_corner_BL, pipe_corner_BR, pipe_corner_BR};

byte frame = 0;

Player player;
Maze maze;


/* ----------------------------------------------------------------------------
    Initialise the Arduboy and get ready ..
*/
void setup() {

  maze.maxX = 5;
  maze.maxY = 5;

  arduboy.boot();
  arduboy.setFrameRate(30);
  arduboy.clear();

}


/* ----------------------------------------------------------------------------
    Define an array of function pointers that represent the various modes of
    game play.  These correspond to the STATE_GAME_ .. constants.
*/

#define STATE_GAME_INTRO                      0
#define STATE_GAME_NO_SELECTION               1
#define STATE_GAME_NODE_SELECTED              2
#define STATE_GAME_GAME_OVER                  3

byte gameState = STATE_GAME_INTRO;

typedef void (*FunctionPointer) ();

const FunctionPointer PROGMEM gameLoop[] = {
  drawSplash,
  play_NoSelection,
  play_NodeSelected,
  drawGameOver
};


/* ----------------------------------------------------------------------------
    Play pipes !
*/
void loop() {

  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  ((FunctionPointer)pgm_read_word(&gameLoop[gameState])) ();
  arduboy.display();

}



void play_NoSelection() {

  if (arduboy.justPressed(LEFT_BUTTON) && player.x > 0)               {
    Serial.println("left");
    player.x--;
  }
  if (arduboy.justPressed(RIGHT_BUTTON) && player.x < maze.maxX - 1)  {
    Serial.println("right");
    player.x++;
  }
  if (arduboy.justPressed(UP_BUTTON) && player.y > 0)                 {
    Serial.println("up");
    player.y--;
  }
  if (arduboy.justPressed(DOWN_BUTTON) && player.y < maze.maxY - 1)   {
    Serial.println("down");
    player.y++;
  }

  if (arduboy.justPressed(A_BUTTON) && isNode(player.x, player.y)) {
    Serial.println("A Button");
    if (nodeAlreadyPlayed(getNodeValue(player.x, player.y))) {
      Serial.println(" nodeAlreadyPlayed()");

      clearBoard(getNodeValue(player.x, player.y));
      player.selectedNode.value = getNodeValue(player.x, player.y);
      player.selectedNode.x = player.x;
      player.selectedNode.y = player.y;
      gameState = STATE_GAME_NODE_SELECTED;

    }
    else {

      Serial.println(" select a node");

      player.selectedNode.value = getNodeValue(player.x, player.y);
      player.selectedNode.x = player.x;
      player.selectedNode.y = player.y;
      gameState = STATE_GAME_NODE_SELECTED;

    }

  }

  if (arduboy.justPressed(B_BUTTON)) {
isPuzzleComplete2();
  }

  renderBoard();
  
}

void play_NodeSelected() {

  if (arduboy.justPressed(LEFT_BUTTON)) {
    
    if (validMove(LEFT, player.selectedNode, player.x - 1, player.y)) {

//echoBoard();

      switch (getPipeValue(player.x, player.y)) {

        case PIPE_HORIZONTAL_LR:
        case PIPE_CORNER_TR:
        case PIPE_CORNER_BR:
          updatePipeWhenReversing(player.x - 1, player.y);
          setPipeValue(player.x, player.y, NOTHING, NOTHING);
          break;

        case PIPE_HORIZONTAL_RL:
        case PIPE_CORNER_TL:
        case PIPE_CORNER_BL:
          if (!isNode(player.x - 1, player.y)) { setPipeValue(player.x - 1, player.y, PIPE_HORIZONTAL_RL, player.selectedNode.value); }
          break;

        case PIPE_CORNER_LT:
        case PIPE_CORNER_RT:
        case PIPE_VERTICAL_BT:
          if (!isNode(player.x - 1, player.y)) { setPipeValue(player.x - 1, player.y, PIPE_HORIZONTAL_RL, player.selectedNode.value); }
          setPipeValue(player.x, player.y, PIPE_CORNER_BL, player.selectedNode.value);
          break;

        case PIPE_CORNER_LB:
        case PIPE_CORNER_RB:
        case PIPE_VERTICAL_TB:
          if (!isNode(player.x - 1, player.y)) { setPipeValue(player.x - 1, player.y, PIPE_HORIZONTAL_RL, player.selectedNode.value); }
          setPipeValue(player.x, player.y, PIPE_CORNER_TL, player.selectedNode.value);
          break;

        case NODE:
          setPipeValue(player.x - 1, player.y, PIPE_HORIZONTAL_RL, player.selectedNode.value);
          break;

      }
  
  
      // Have we selected the original node?  If so clear the board of this pipe ..
      
      if (player.x - 1 == player.selectedNode.x && player.y == player.selectedNode.y) {
    
        clearBoard(player.selectedNode.value);
        clearSelection();
        gameState = STATE_GAME_NO_SELECTION;
        playClearSelectionTune();
          
      }
  
  
      // Have we selected a pair node?  
      
      if (isNode(player.x - 1, player.y)  && getNodeValue(player.x - 1, player.y) == player.selectedNode.value) {
    
        clearSelection();
        gameState = STATE_GAME_NO_SELECTION;
        playMatchTune();
 

        // Is the level finished ?

        if (isPuzzleComplete()) {

          gameState = STATE_GAME_GAME_OVER;
    
        }
                 
      }  
      
      player.x--;
      
    }
//echoBoard();
    
  }

  if (arduboy.justPressed(RIGHT_BUTTON)) {
//echoBoard();
    
    if (validMove(RIGHT, player.selectedNode, player.x + 1, player.y)) {

      switch (getPipeValue(player.x, player.y)) {

        case PIPE_HORIZONTAL_RL:
        case PIPE_CORNER_TL:
        case PIPE_CORNER_BL:
          updatePipeWhenReversing(player.x + 1, player.y);
          setPipeValue(player.x, player.y, NOTHING, NOTHING);
          break;

        case PIPE_HORIZONTAL_LR:
        case PIPE_CORNER_TR:
        case PIPE_CORNER_BR:
          if (!isNode(player.x + 1, player.y)) { setPipeValue(player.x + 1, player.y, PIPE_HORIZONTAL_LR, player.selectedNode.value); }
          break;

        case PIPE_CORNER_RT:
        case PIPE_CORNER_LT:
        case PIPE_VERTICAL_BT:
          if (!isNode(player.x + 1, player.y)) { setPipeValue(player.x + 1, player.y, PIPE_HORIZONTAL_LR, player.selectedNode.value); }
          setPipeValue(player.x, player.y, PIPE_CORNER_BR, player.selectedNode.value);
          break;

        case PIPE_CORNER_RB:
        case PIPE_CORNER_LB:
        case PIPE_VERTICAL_TB:
          if (!isNode(player.x + 1, player.y)) { setPipeValue(player.x + 1, player.y, PIPE_HORIZONTAL_LR, player.selectedNode.value); }
          setPipeValue(player.x, player.y, PIPE_CORNER_TR, player.selectedNode.value);
          break;

        case NODE:
          setPipeValue(player.x + 1, player.y, PIPE_HORIZONTAL_LR, player.selectedNode.value);
          break;

      }
  
  
      // Have we selected the original node?  If so clear the board of this pipe ..
      
      if (player.x + 1 == player.selectedNode.x && player.y == player.selectedNode.y) {
    
        clearBoard(player.selectedNode.value);
        clearSelection();
        gameState = STATE_GAME_NO_SELECTION;
        playClearSelectionTune();
          
      }
  
  
      // Have we selected a pair node?  
      
      if (isNode(player.x + 1, player.y)  && getNodeValue(player.x + 1, player.y) == player.selectedNode.value) {
    
        clearSelection();
        gameState = STATE_GAME_NO_SELECTION;
        playMatchTune();
  

        // Is the level finished ?

        if (isPuzzleComplete()) {

          gameState = STATE_GAME_GAME_OVER;
    
        }
                
      }
    
      player.x++;
  
    }
    
//echoBoard();

  }

  if (arduboy.justPressed(UP_BUTTON)) {
    
    if (validMove(UP, player.selectedNode, player.x, player.y - 1)) {

//echoBoard();

      switch (getPipeValue(player.x, player.y)) {

        case PIPE_VERTICAL_TB:
        case PIPE_CORNER_RB:
        case PIPE_CORNER_LB:
          updatePipeWhenReversing(player.x, player.y - 1);
          setPipeValue(player.x, player.y, NOTHING, NOTHING);
          break;

        case PIPE_VERTICAL_BT:
        case PIPE_CORNER_LT:
        case PIPE_CORNER_RT:
          if (!isNode(player.x, player.y - 1)) { setPipeValue(player.x, player.y - 1, PIPE_VERTICAL_BT, player.selectedNode.value); }
          break;

        case PIPE_CORNER_TR:
        case PIPE_CORNER_BR:
        case PIPE_HORIZONTAL_LR:
          if (!isNode(player.x, player.y - 1)) { setPipeValue(player.x, player.y - 1, PIPE_VERTICAL_BT, player.selectedNode.value); }
          setPipeValue(player.x, player.y, PIPE_CORNER_LT, player.selectedNode.value); 
          break;

        case PIPE_CORNER_TL:
        case PIPE_CORNER_BL:
        case PIPE_HORIZONTAL_RL:
          if (!isNode(player.x, player.y - 1)) { setPipeValue(player.x, player.y - 1, PIPE_VERTICAL_BT, player.selectedNode.value); }
          setPipeValue(player.x, player.y, PIPE_CORNER_RT, player.selectedNode.value);
          break;

        case NODE:
          setPipeValue(player.x, player.y - 1, PIPE_VERTICAL_BT, player.selectedNode.value);
          break;

      }
  
  
      // Have we selected the original node?  If so clear the board of this pipe ..
      
      if (player.x == player.selectedNode.x && player.y - 1 == player.selectedNode.y) {
    
        clearBoard(player.selectedNode.value);
        clearSelection();
        gameState = STATE_GAME_NO_SELECTION;
        playClearSelectionTune();
         
      }
  
  
      // Have we selected a pair node?  
      
      if (isNode(player.x, player.y - 1)  && getNodeValue(player.x, player.y - 1) == player.selectedNode.value) {
    
        clearSelection();
        gameState = STATE_GAME_NO_SELECTION;
        playMatchTune();
 

        // Is the level finished ?

        if (isPuzzleComplete()) {

          gameState = STATE_GAME_GAME_OVER;
    
        }
                 
      }  
    
      player.y--;
    }
//echoBoard();
  }

  if (arduboy.justPressed(DOWN_BUTTON)) {
    
    if (validMove(DOWN, player.selectedNode, player.x, player.y + 1)) {

//Serial.println("down");      
//echoBoard();
//Serial.println(getPipeValue(player.x, player.y));      
      switch (getPipeValue(player.x, player.y)) {

        case PIPE_VERTICAL_BT:
        case PIPE_CORNER_RT:
        case PIPE_CORNER_LT:
          updatePipeWhenReversing(player.x, player.y + 1);
          setPipeValue(player.x, player.y, NOTHING, NOTHING);
          break;

        case PIPE_VERTICAL_TB:
        case PIPE_CORNER_LB:
        case PIPE_CORNER_RB:
          if (!isNode(player.x, player.y + 1)) { setPipeValue(player.x, player.y + 1, PIPE_VERTICAL_TB, player.selectedNode.value); }
          break;

        case PIPE_CORNER_TR:
        case PIPE_CORNER_BR:
        case PIPE_HORIZONTAL_LR:
          if (!isNode(player.x, player.y + 1)) { setPipeValue(player.x, player.y + 1, PIPE_VERTICAL_TB, player.selectedNode.value); }
          setPipeValue(player.x, player.y, PIPE_CORNER_LB, player.selectedNode.value);
          break;

        case PIPE_CORNER_TL:
        case PIPE_CORNER_BL:
        case PIPE_HORIZONTAL_RL:
          if (!isNode(player.x, player.y + 1)) { setPipeValue(player.x, player.y + 1, PIPE_VERTICAL_TB, player.selectedNode.value); }
          setPipeValue(player.x, player.y, PIPE_CORNER_RB, player.selectedNode.value);
          break;

        case NODE:
          setPipeValue(player.x, player.y + 1, PIPE_VERTICAL_TB, player.selectedNode.value);
          break;
        
      }

  
      // Have we selected the original node?  If so clear the board of this pipe ..
      
      if (player.x == player.selectedNode.x && player.y + 1 == player.selectedNode.y) {
    
        clearBoard(player.selectedNode.value);
        clearSelection();
        gameState = STATE_GAME_NO_SELECTION;
        playClearSelectionTune();
          
      }
   
  
      // Have we selected a pair node?  
      
      if (isNode(player.x, player.y + 1)  && getNodeValue(player.x, player.y + 1) == player.selectedNode.value) {
    
        clearSelection();
        gameState = STATE_GAME_NO_SELECTION;
        playMatchTune();


        // Is the level finished ?

        if (isPuzzleComplete()) {

          gameState = STATE_GAME_GAME_OVER;
    
        }
  
      }  
   
      player.y++;
    }
//echoBoard();
  }


  renderBoard();
  
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

void clearSelection() {

  player.selectedNode.value = 0;
  player.selectedNode.x = 0;
  player.selectedNode.y = 0;

}

bool isPuzzleComplete() {

  for (byte y = 0; y < maze.maxY; y++) {
    
    for (byte x = 0; x < maze.maxX; x++) {
      
      if (getNodeValue(x, y) == 0) {
        
        return false;
        
      }
      
    }
    
  }

  return true;
  
}

