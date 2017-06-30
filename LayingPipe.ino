#include <Arduboy2.h> 
#include "Images.h"
#include "Puzzles.h"
#include <ArduboyTones.h>

#define DEBUG

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

#define PUZZLE_5X5              5
#define PUZZLE_6X6              6
#define PUZZLE_7X7              7
#define PUZZLE_8X8              8
#define PUZZLE_9X9              9

Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);
Sprites sprites;

struct Node {
  byte x;
  byte y;
  byte value;
};

struct Player {
  Node highlightedNode;
  Node selectedNode;
}
player = 
  { 
    {0, 0, 0}, 
    {0, 0, 0} 
  };
  
struct Puzzle {
  Node maximum;
  byte board[9][9];
} 
puzzle = 
  { {0, 0}, 
    {
      {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
    }
  };

const byte* nodes[] = {node_0, node_1, node_2, node_3, node_4, node_5, node_6, node_7, node_8, node_9, node_10, node_11, node_12, node_13, node_14 };
const byte* pipes[] = {pipe_nothing, pipe_horizontal, pipe_horizontal, pipe_vertical, pipe_vertical, pipe_corner_TL, pipe_corner_TL, pipe_corner_TR, pipe_corner_TR, pipe_corner_BL, pipe_corner_BL, pipe_corner_BR, pipe_corner_BR};
const byte levels[] = {PUZZLE_5X5, PUZZLE_6X6, PUZZLE_7X7, PUZZLE_8X8, PUZZLE_9X9};

byte frame = 0;

byte puzzleType = PUZZLE_5X5;
byte puzzleIdx = 0;



/* ----------------------------------------------------------------------------
    Initialise the Arduboy and get ready ..
*/
void setup() {

  if (!isEEPROMInitialised()) { initEEPROM(); }

  arduboy.begin();
  arduboy.setFrameRate(30);
  arduboy.clear();
  arduboy.audio.begin();

}


/* ----------------------------------------------------------------------------
    Define an array of function pointers that represent the various modes of
    game play.  These correspond to the STATE_GAME_ .. constants.
*/

#define STATE_GAME_INTRO                      0
#define STATE_GAME_LEVEL_SELECT               1
#define STATE_GAME_PUZZLE_SELECT              2
#define STATE_GAME_INIT_GAME                  3
#define STATE_GAME_NO_SELECTION               4
#define STATE_GAME_NODE_SELECTED              5
#define STATE_GAME_GAME_OVER                  6

byte gameState = STATE_GAME_INTRO;

typedef void (*FunctionPointer) ();

const FunctionPointer PROGMEM gameLoop[] = {
  drawSplash,
  levelSelect,
  puzzleSelect,
  play_InitGame,
  play_NoSelection,
  play_NodeSelected,
  drawGameOver
};


/* ----------------------------------------------------------------------------
 *  Lay pipes !
 */
void loop() {

  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  ((FunctionPointer)pgm_read_word(&gameLoop[gameState])) ();
  arduboy.display();

}



