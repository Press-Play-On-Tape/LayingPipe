#define EEPROM_START            200
#define EEPROM_START_C1         EEPROM_START
#define EEPROM_START_C2         EEPROM_START + 1
#define EEPROM_5X5              EEPROM_START + 2
#define EEPROM_6X6              EEPROM_START + 3
#define EEPROM_7X7              EEPROM_START + 4
#define EEPROM_8X8              EEPROM_START + 5
#define EEPROM_9X9              EEPROM_START + 6
#define EEPROM_PUZZLE_OFFSET    EEPROM_START - 3


/* ----------------------------------------------------------------------------
 *   Is the EEPROM initialised? 
 *   
 *   Looks for the characters 'L' and 'P' in the first two bytes of the EEPROM
 *   memory range starting from byte 200.
 */
bool isEEPROMInitialised() {

  byte c1 = EEPROM.read(EEPROM_START_C1);
  byte c2 = EEPROM.read(EEPROM_START_C2);

  return (c1 == 76 && c2 == 80);

}


/* ----------------------------------------------------------------------------
 *   Initialise the EEPROM.
 *   
 *   Sets the first wo bytes of the EEPROM to the characters 'L' and 'P' and 
 *   clears the levels to zero.
 */
void initEEPROM() {

  EEPROM.update(EEPROM_START_C1, 76);
  EEPROM.update(EEPROM_START_C2, 80);
  EEPROM.update(EEPROM_5X5, 0);
  EEPROM.update(EEPROM_6X6, 0);
  EEPROM.update(EEPROM_7X7, 0);
  EEPROM.update(EEPROM_8X8, 0);
  EEPROM.update(EEPROM_9X9, 0);

}


/* ----------------------------------------------------------------------------
 *   Update the saved puzzle index for the nominated level.
 */
void updateEEPROM(byte puzzleLevel, byte index) {

  EEPROM.update(EEPROM_PUZZLE_OFFSET + puzzleLevel, index);

}


/* ----------------------------------------------------------------------------
 *   Read the saved puzzle index for the nominated level.
 */
byte readEEPROM(byte puzzleLevel) {

  return EEPROM.read(EEPROM_PUZZLE_OFFSET + puzzleLevel);

}
