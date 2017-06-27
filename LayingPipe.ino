#include "Arduboy2.h" 
#include "Images.h"
#include <StackArray.h>

Arduboy2 arduboy;
Sprites sprites;
StackArray <int> st;

byte board[5][5] = {
  {0x00, 0x00, 0x00, 0xF1, 0xF2},
  {0x00, 0x00, 0xF3, 0xF2, 0x00},
  {0xF1, 0x00, 0x00, 0x00, 0x00},
  {0xF4, 0xF3, 0x00, 0x05, 0xF4},
  {0x00, 0x00, 0x00, 0x00, 0xF5}
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

struct Maze
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

#define GRID_WIDTH              8
#define GRID_HEIGHT             8

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

  arduboy.begin();
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
  drawSplash_Loop,
  play_NoSelection,
  play_NodeSelected,
  drawSplash_Loop
};


/* ----------------------------------------------------------------------------
    Play pipes !
*/
void loop() {

  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  ((FunctionPointer)pgm_read_word(&gameLoop[gameState])) ();
  renderBoard();
  arduboy.display();

}



void play_NoSelection() {

  if (arduboy.justPressed(LEFT_BUTTON) && player.x > 0)               {
    Serial.println("left");
    player.x--;
  }
  if (arduboy.justPressed(RIGHT_BUTTON) && player.x < maze.maxX)      {
    Serial.println("right");
    player.x++;
  }
  if (arduboy.justPressed(UP_BUTTON) && player.y > 0)                 {
    Serial.println("up");
    player.y--;
  }
  if (arduboy.justPressed(DOWN_BUTTON) && player.y < maze.maxY)       {
    Serial.println("down");
    player.y++;
  }

  if (arduboy.justPressed(A_BUTTON) && isNode(player.x, player.y)) {
    Serial.println("A Button");
    if (nodeAlreadyPlayed(getNodeValue(player.x, player.y))) {
      Serial.println(" nodeAlreadyPlayed()");

      clearBoard(getNodeValue(player.x, player.y));

    }
    else {

      Serial.println(" select a node");

      player.selectedNode.value = getNodeValue(player.x, player.y);
      player.selectedNode.x = player.x;
      player.selectedNode.y = player.y;
      gameState = STATE_GAME_NODE_SELECTED;

    }

  }

  arduboy.delayShort(100);

}

void play_NodeSelected() {

  if (arduboy.justPressed(LEFT_BUTTON) && validMove(player.selectedNode.value, player.x - 1, player.y)) {
echoBoard();

    if (player.x - 1 != player.selectedNode.x || player.y != player.selectedNode.y) {

      if (!isNode(player.x, player.y)) {

        switch (getPipeValue(player.x, player.y)) {

          case PIPE_HORIZONTAL_LR:
          case PIPE_CORNER_TR:
          case PIPE_CORNER_BR:
            setPipeValue(player.x, player.y, NOTHING, NOTHING);
            break;

          case PIPE_HORIZONTAL_RL:
          case PIPE_CORNER_TL:
          case PIPE_CORNER_BL:
            setPipeValue(player.x - 1, player.y, PIPE_HORIZONTAL_RL, player.selectedNode.value);
            break;

          case PIPE_CORNER_LT:
          case PIPE_CORNER_RT:
          case PIPE_VERTICAL_BT:
            setPipeValue(player.x - 1, player.y, PIPE_HORIZONTAL_RL, player.selectedNode.value);
            setPipeValue(player.x, player.y, PIPE_CORNER_BL, player.selectedNode.value);
            break;

          case PIPE_CORNER_LB:
          case PIPE_CORNER_RB:
          case PIPE_VERTICAL_TB:
            setPipeValue(player.x - 1, player.y, PIPE_HORIZONTAL_RL, player.selectedNode.value);
            setPipeValue(player.x, player.y, PIPE_CORNER_TL, player.selectedNode.value);
            break;

        }

      }
      else {

        Serial.println(" Not node");
        setPipeValue(player.x - 1, player.y, PIPE_HORIZONTAL_RL, player.selectedNode.value);

      }

      player.x--;

    }
echoBoard();

  }

  if (arduboy.justPressed(RIGHT_BUTTON) && validMove(player.selectedNode.value, player.x + 1, player.y)) {
echoBoard();

    if (player.x != player.selectedNode.x || player.y != player.selectedNode.y) {

      if (!isNode(player.x, player.y)) {

        switch (getPipeValue(player.x, player.y)) {

          case PIPE_HORIZONTAL_RL:
          case PIPE_CORNER_TL:
          case PIPE_CORNER_BL:
            setPipeValue(player.x, player.y, NOTHING, NOTHING);
            break;

          case PIPE_HORIZONTAL_LR:
          case PIPE_CORNER_TR:
          case PIPE_CORNER_BR:
            setPipeValue(player.x + 1, player.y, PIPE_HORIZONTAL_LR, player.selectedNode.value);
            break;

          case PIPE_CORNER_RT:
          case PIPE_CORNER_LT:
          case PIPE_VERTICAL_BT:
            setPipeValue(player.x + 1, player.y, PIPE_HORIZONTAL_LR, player.selectedNode.value);
            setPipeValue(player.x, player.y, PIPE_CORNER_BR, player.selectedNode.value);
            break;

          case PIPE_CORNER_RB:
          case PIPE_CORNER_LB:
          case PIPE_VERTICAL_TB:
            setPipeValue(player.x + 1, player.y, PIPE_HORIZONTAL_LR, player.selectedNode.value);
            setPipeValue(player.x, player.y, PIPE_CORNER_TR, player.selectedNode.value);
            break;

        }

      }
      else {

        setPipeValue(player.x + 1, player.y, PIPE_HORIZONTAL_LR, player.selectedNode.value);

      }

      player.x++;

    }
echoBoard();

  }

  if (arduboy.justPressed(UP_BUTTON) && validMove(player.selectedNode.value, player.x, player.y - 1)) {
echoBoard();
Serial.println(getPipeValue(player.x, player.y));
    if (player.x != player.selectedNode.x || player.y != player.selectedNode.y) {

      if (!isNode(player.x, player.y)) {
  
        switch (getPipeValue(player.x, player.y)) {
  
          case PIPE_VERTICAL_TB:
          case PIPE_CORNER_RB:
          case PIPE_CORNER_LB:
            setPipeValue(player.x, player.y, NOTHING, NOTHING);
            break;
  
          case PIPE_VERTICAL_BT:
          case PIPE_CORNER_LT:
          case PIPE_CORNER_RT:
            setPipeValue(player.x, player.y - 1, PIPE_VERTICAL_BT, player.selectedNode.value);
            break;
  
          case PIPE_CORNER_TR:
          case PIPE_CORNER_BR:
          case PIPE_HORIZONTAL_LR:
            setPipeValue(player.x, player.y - 1, PIPE_VERTICAL_BT, player.selectedNode.value);
            setPipeValue(player.x, player.y, PIPE_CORNER_LT, player.selectedNode.value);
            break;
  
          case PIPE_CORNER_TL:
          case PIPE_CORNER_BL:
          case PIPE_HORIZONTAL_RL:
            setPipeValue(player.x, player.y - 1, PIPE_VERTICAL_BT, player.selectedNode.value);
            setPipeValue(player.x, player.y, PIPE_CORNER_RT, player.selectedNode.value);
            break;
  
        }

      }
      else {

        setPipeValue(player.x + 1, player.y, PIPE_VERTICAL_BT, player.selectedNode.value);

      }
  
      player.y--;
echoBoard();    
    }

  }

  if (arduboy.justPressed(DOWN_BUTTON) && validMove(player.selectedNode.value, player.x, player.y + 1)) {
echoBoard();

    if (player.x != player.selectedNode.x || player.y != player.selectedNode.y) {

      if (!isNode(player.x, player.y)) {
        
        switch (getPipeValue(player.x, player.y)) {
  
          case PIPE_VERTICAL_BT:
          case PIPE_CORNER_RT:
          case PIPE_CORNER_LT:
            setPipeValue(player.x, player.y, NOTHING, NOTHING);
            break;
  
          case PIPE_VERTICAL_TB:
          case PIPE_CORNER_LB:
          case PIPE_CORNER_RB:
            setPipeValue(player.x, player.y + 1, PIPE_VERTICAL_TB, player.selectedNode.value);
            break;
  
          case PIPE_CORNER_TR:
          case PIPE_CORNER_BR:
          case PIPE_HORIZONTAL_LR:
            setPipeValue(player.x, player.y + 1, PIPE_VERTICAL_TB, player.selectedNode.value);
            setPipeValue(player.x, player.y, PIPE_CORNER_LB, player.selectedNode.value);
            break;
  
          case PIPE_CORNER_TL:
          case PIPE_CORNER_BL:
          case PIPE_HORIZONTAL_RL:
            setPipeValue(player.x, player.y + 1, PIPE_VERTICAL_TB, player.selectedNode.value);
            setPipeValue(player.x, player.y, PIPE_CORNER_RB, player.selectedNode.value);
            break;
        }

      }
      else {
  
        setPipeValue(player.x, player.y + 1, PIPE_VERTICAL_BT, player.selectedNode.value);
  
      }
  
      player.y++;

    }
echoBoard();

  }

  if (arduboy.justPressed(A_BUTTON) && isNode(player.x, player.y) && getNodeValue(player.x, player.y) == player.selectedNode.value) {

    player.selectedNode.value = 0;
    gameState = STATE_GAME_NO_SELECTION;

  }

  arduboy.delayShort(100);

}

