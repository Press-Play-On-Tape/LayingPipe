#define EEPROM_START            200
#define EEPROM_START_C1         EEPROM_START
#define EEPROM_START_C2         EEPROM_START + 1
#define EEPROM_5X5              EEPROM_START + 2
#define EEPROM_6X6              EEPROM_START + 3
#define EEPROM_7X7              EEPROM_START + 4
#define EEPROM_8X8              EEPROM_START + 5
#define EEPROM_9X9              EEPROM_START + 6
#define EEPROM_PUZZLE_OFFSET    EEPROM_START - 3

bool isEEPROMInitialised() {

  byte c1 = EEPROM.read(EEPROM_START_C1);
  byte c2 = EEPROM.read(EEPROM_START_C2);

  return (c1 == 76 && c2 == 80);

}

void initEEPROM() {

  EEPROM.write(EEPROM_START_C1, 76);
  EEPROM.write(EEPROM_START_C2, 80);
  EEPROM.write(EEPROM_5X5, 0);
  EEPROM.write(EEPROM_6X6, 0);
  EEPROM.write(EEPROM_7X7, 0);
  EEPROM.write(EEPROM_8X8, 0);
  EEPROM.write(EEPROM_9X9, 0);

}

void updateEEPROM(byte puzzleType, byte val) {

  EEPROM.write(EEPROM_PUZZLE_OFFSET + puzzleType, val);

}


byte readEEPROM(byte puzzleType) {

  return EEPROM.read(EEPROM_PUZZLE_OFFSET + puzzleType);

}

/*
  hi = EEPROM.read(address + (5*j));
        lo = EEPROM.read(address + (5*j) + 1);

        if ((hi == 0xFF) && (lo == 0xFF))
        {
        tmpScore = 0;
        }
        else
        {
          tmpScore = (hi << 8) | lo;
        }
 */


