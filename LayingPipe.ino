/* ----------------------------------------------------------------------------
 *   Pipes  by  Simon Holmes, 2017 
 * ---------------------------------------------------------------------------- 
 */
#include <Arduboy2.h> 
#include "Images.h"
#include "Puzzles.h"
#include <ArduboyTones.h>

#define NO_SCREENSHOTS

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


/* ----------------------------------------------------------------------------
 *  Basic structure to hold a node value and coordinates ..
 */
struct Node {
  byte x;
  byte y;
  byte value;
};


/* ----------------------------------------------------------------------------
 *  Player structure to record the highlighted and selected node ..
 */
struct Player {
  Node highlightedNode;
  Node selectedNode;
}
player = 
  { 
    {0, 0, 0}, 
    {0, 0, 0} 
  };

/* ----------------------------------------------------------------------------
 *  Scroll bar structure used to record the scroll bar location and rendering 
 *  properties.  These change depending on the number of rows in the puzzle. 
 */
struct Slider {
  byte unit;                              // Number of pixels / row for the slider.
  byte overall;                           // Height of the slider portion in pixels.
};


/* ----------------------------------------------------------------------------
 *  Puzzle structure.
 */
struct Puzzle {
  byte level;                             // Level being played, eg. PUZZLE_5X5, PUZZLE_6X6 ..
  byte index;                             // Puzzle within the current level being played.
  Node maximum;                           // Used to store the dimensions of the puzzle based
                                          // on the puzzle level, eg. PUZZLE_5X5 has a maximum
                                          // x and y value of 5.
  Node offset;                            // Stores the offest x and y values to ensure the 
                                          // is rendered centrally on the screen.
  Slider slider;                          // Scrollbar slider details.
  byte board[9][9];                       // Actual board details - supports maximum of 9 x 9.
}
puzzle = 
  {  0, 0,
    {0, 0}, 
    {0, 0}, 
    {0, 0}, 
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
    },
    
  };

const byte* nodes[] = {node_0, node_1, node_2, node_3, node_4, node_5, node_6, node_7, node_8, node_9, node_10, node_11, node_12, node_13, node_14 };
const byte* pipes[] = {pipe_nothing, pipe_horizontal, pipe_horizontal, pipe_vertical, pipe_vertical, pipe_corner_TL, pipe_corner_TL, 
                       pipe_corner_TR, pipe_corner_TR, pipe_corner_BL, pipe_corner_BL, pipe_corner_BR, pipe_corner_BR};
const byte levels[] = {PUZZLE_5X5, PUZZLE_6X6, PUZZLE_7X7, PUZZLE_8X8, PUZZLE_9X9};

byte frame = 0;


/* ----------------------------------------------------------------------------
 *   Initialise the Arduboy and get ready ..
 */
void setup() {

  puzzle.level = PUZZLE_5X5;
  puzzle.index = 0;

  if (!isEEPROMInitialised()) { initEEPROM(); }

  arduboy.begin();
  arduboy.setFrameRate(30);
  arduboy.clear();

}


/* ----------------------------------------------------------------------------
 *   Define an array of function pointers that represent the various modes of
 *   game play.  These correspond to the STATE_GAME_ .. constants.
 */

#define STATE_GAME_INTRO                      0
#define STATE_GAME_LEVEL_SELECT               1
#define STATE_GAME_PUZZLE_SELECT              2
#define STATE_GAME_INIT_GAME                  3
#define STATE_GAME_NO_SELECTION               4
#define STATE_GAME_NODE_SELECTED              5
#define STATE_GAME_GAME_OVER                  6

byte gameState = STATE_GAME_INTRO;
byte prevState = STATE_GAME_INTRO;

typedef void (*FunctionPointer) ();

const FunctionPointer PROGMEM gameLoop[] = {
  drawSplash,
  levelSelect,
  puzzleSelect,
  play_InitGame,
  play_NoSelection,
  play_NodeSelected,
  gameOver
};


/* ----------------------------------------------------------------------------
 *  Play pipes !
 */
void loop() {

  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  ((FunctionPointer)pgm_read_word(&gameLoop[gameState])) ();
  arduboy.display();

}



