
// Logo ..
const byte PROGMEM logo[] = {
  84, 24, 
  0x00, 0x00, 0x6C, 0x6C, 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6C, 0x6C, 0x00, 0x0C, 0x0C, 0x00, 0x0C, 0x0C, 0x00, 0x60, 0x60, 0x00, 0x00, 0x0C, 0x0C, 0x00, 0x6C, 0x6C, 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x00, 0x6C, 0x6C, 0x00, 0x0C, 0x0C, 0x00, 0x0C, 0x0C, 0x00, 0x60, 0x60, 0x00, 0x00, 0x6C, 0x6C, 0x00, 0x0C, 0x0C, 0x00, 0x0C, 0x0C, 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x60, 0x60, 0x00, 0x0C, 0x0C, 0x00, 0x0C, 0x0C, 0x00, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00, 0x6C, 0x6C, 0x00, 0x00,
  0x00, 0x00, 0xDB, 0xDB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDB, 0xDB, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDB, 0xDB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDB, 0xDB, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x03, 0x03, 0x00, 0x00, 0xDB, 0xDB, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDB, 0xDB, 0x00, 0x00,
  0x00, 0x00, 0x36, 0x36, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x36, 0x36, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x36, 0x00, 0x30, 0x30, 0x00, 0x30, 0x30, 0x00, 0x30, 0x30, 0x00, 0x00, 0x06, 0x06, 0x00, 0x30, 0x30, 0x00, 0x30, 0x30, 0x00, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x36, 0x36, 0x00, 0x00,
};


// Sound ..

const byte PROGMEM sound_icon[] = {
  8, 8,
  0x1C, 0x1C, 0x1C, 0x3E, 0x7F, 0x00, 0x2A, 0x49,
};

const byte PROGMEM no_sound_icon[] = {
  8, 8,
  0x1C, 0x14, 0x14, 0x22, 0x7F, 0x00, 0x00, 0x00,
};


// Nodes for game play ..

const byte PROGMEM node_1[] = {
  8, 8, 
  0x7E, 0xE7, 0xE7, 0x81, 0x81, 0xE7, 0xE7, 0x7E,
};

const byte PROGMEM node_2[] = {
  8, 8,
  0x7E, 0xFF, 0xC3, 0xC3, 0xC3, 0xC3, 0xFE, 0x7E,
};

const byte PROGMEM node_3[] = {
  8, 8,
  0x7E, 0xFF, 0xF3, 0xE3, 0xC7, 0xCF, 0xFF, 0x7E,
};

const byte PROGMEM node_4[] = {
  8, 8,
  0x7E, 0xFF, 0xCF, 0xC7, 0xE3, 0xF3, 0xFF, 0x7E,
};

const byte PROGMEM node_5[] = {
  8, 8,
  0x7E, 0xFF, 0x99, 0x99, 0x99, 0x99, 0xFF, 0x7E,
};

const byte PROGMEM node_6[] = {
  8, 8,
  0x7E, 0xC3, 0xC3, 0xFF, 0xFF, 0xC3, 0xC3, 0x7E,
};

const byte PROGMEM node_7[] = {
  8, 8,
  0x7E, 0xFF, 0xF3, 0xF3, 0xCF, 0xCF, 0xFF, 0x7E,
};

const byte PROGMEM node_8[] = {
  8, 8,
  0x7E, 0xFF, 0xCF, 0xCF, 0xF3, 0xF3, 0xFF, 0x7E,
};

const byte PROGMEM node_9[] = {
  8, 8,
  0x7E, 0xFF, 0xFF, 0x81, 0x81, 0xFF, 0xFF, 0x7E,
};

const byte PROGMEM node_10[] = {
  8, 8,
  0x7E, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0x7E,
};

const byte PROGMEM node_11[] = {
  8, 8,
  0x7E, 0xE7, 0xC3, 0x99, 0x99, 0xC3, 0xE7, 0x7E,
};

const byte PROGMEM node_12[] = {
  8, 8,
  0x7E, 0xEF, 0xE7, 0xE3, 0xE3, 0xE7, 0xEF, 0x7E,
};

const byte PROGMEM node_13[] = {
  8, 8,
  0x7E, 0xE7, 0xC3, 0x81, 0x81, 0xC3, 0xE7, 0x7E,
};

const byte PROGMEM node_14[] = {
  8, 8,
  0x7E, 0xE7, 0xE7, 0xF9, 0xF9, 0xFF, 0xFF, 0x7E,
};

const byte PROGMEM node_15[] = {
  8, 8, 
  0x7E, 0xFF, 0xFF, 0x9F, 0x9F, 0xE7, 0xE7, 0x7E,
};

const byte PROGMEM node_16[] = {
  8, 8, 
  0x7E, 0x9F, 0x9F, 0xE7, 0xE7, 0xF9, 0xF9, 0x7E,
};

const byte PROGMEM node_17[] = {
  8, 8, 
  0x7E, 0xF9, 0xF9, 0xE7, 0xE7, 0x9F, 0x9F, 0x7E,
};

const byte PROGMEM node_18[] = {
  8, 8, 
  0x7E, 0x99, 0x99, 0xE7, 0xE7, 0x99, 0x99, 0x7E,
};


// Pipes for game play ..

const byte PROGMEM pipe_nothing[] = {
  7, 8,
  0x80, 0x00, 0x80, 0x00, 0x80, 
};

const byte PROGMEM pipe_horizontal[] = {
  12, 16,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const byte PROGMEM pipe_vertical[] = {
  12, 16,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const byte PROGMEM pipe_corner_TL[] = {
  12, 16,
  0x20, 0x20, 0x20, 0x10, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const byte PROGMEM pipe_corner_TR[] = {
  12, 16,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x10, 0x20, 0x20, 0x20, 0x20,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const byte PROGMEM pipe_corner_BL[] = {
  12, 16,
  0x20, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const byte PROGMEM pipe_corner_BR[] = {
  12, 16,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20, 0x20,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const byte PROGMEM pipe_mask[] = {
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
};


// Pipes for logo ..

const byte PROGMEM logo_elbow_RB[] = {
  16, 16,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x20, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
  0x00, 0x00, 0x00, 0x00, 0xE0, 0xBF, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xB8, 0xE4, 0x04, 0x04,
};

const byte PROGMEM logo_elbow_LB[] = {
  16, 16,
  0xFC, 0x04, 0xFC, 0x08, 0x08, 0x08, 0x08, 0x08, 0x10, 0x10, 0x20, 0xC0, 0x00, 0x00, 0x00, 0x00,
  0x0F, 0x08, 0x0F, 0x04, 0xE4, 0xB8, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xBF, 0xE0, 0x00, 0x00,
};

const byte PROGMEM logo_elbow_TL[] = {
  16, 16,
  0xFC, 0x04, 0xFC, 0x08, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x3F, 0x00, 0x00, 0x00,
  0x0F, 0x08, 0x0F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const byte PROGMEM logo_elbow_TR[] = {
  16, 16,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x08, 0x08,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x02, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
};

const byte PROGMEM logo_straight_TB[] = {
  16, 16,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xE0, 0xBF, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xBF, 0xE0, 0x00, 0x00,
};

const byte PROGMEM logo_straight_TB_noflange[] = {
  16, 16,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
};

const byte PROGMEM logo_straight_LR[] = {
  16, 16,
  0xFC, 0x04, 0xFC, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
  0x0F, 0x08, 0x0F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
};

const byte PROGMEM logo_straight_LR_noflange[] = {
  16, 16,
  0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
  0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
};

const byte PROGMEM logo_tee_TRB[] = {
  16, 16,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x08, 0x08,
  0x00, 0x00, 0x00, 0x00, 0xE0, 0xBF, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xB8, 0xE4, 0x04, 0x04,
};

const byte PROGMEM logo_tee_TLB[] = {
  16, 16,
  0x08, 0x08, 0x08, 0x08, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
  0x04, 0x04, 0x04, 0x04, 0xE4, 0xB8, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xBF, 0xE0, 0x00, 0x00,
};

const byte PROGMEM logo_tee_LRB[] = {
  16, 16,
  0xFC, 0x04, 0xFC, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
  0x0F, 0x08, 0x0F, 0x04, 0xE4, 0xB8, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xB8, 0xE4, 0x04, 0x04,
};

const byte PROGMEM logo_tee_TLR[] = {
  16, 16,
  0xFC, 0x04, 0xFC, 0x08, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x08, 0x08,
  0x0F, 0x08, 0x0F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
};

const byte PROGMEM logo_cross[] = {
  16, 16,
  0xFC, 0x04, 0xFC, 0x08, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x08, 0x08,
  0x0F, 0x08, 0x0F, 0x04, 0xE4, 0xB8, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xB8, 0xE4, 0x04, 0x04,
};

const byte PROGMEM logo_cross_overlap[] = {
  16, 16,
  0x08, 0x08, 0x08, 0x08, 0x08, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x08, 0x08, 0x08,
  0x04, 0x04, 0x04, 0x04, 0x04, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x04, 0x04, 0x04,
};

const byte PROGMEM logo_cross_overlap_hflange[] = {
  16, 16,
  0xFC, 0x04, 0xFC, 0x08, 0x08, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x08, 0x08, 0x08,
  0x0F, 0x08, 0x0F, 0x04, 0x04, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x04, 0x04, 0x04,
};

const byte PROGMEM logo_cross_underlap[] = {
  16, 16,
  0x08, 0x08, 0x08, 0x08, 0x08, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0F, 0x08, 0x08, 0x08,
  0x04, 0x04, 0x04, 0x04, 0x04, 0xFC, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0xFC, 0x04, 0x04, 0x04,
};

const byte PROGMEM logo_cross_underlap_hflange[] = {
  16, 16,
  0xFC, 0x04, 0xFC, 0x08, 0x08, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0F, 0x08, 0x08, 0x08,
  0x0F, 0x08, 0x0F, 0x04, 0x04, 0xFC, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0xFC, 0x04, 0x04, 0x04,
};




// PPOT

const uint8_t PROGMEM PPOT[] = {
#ifndef DEBUG
65, 32, // 65x31 px image
0xfe, 0x01, 0x05, 0xf1, 0xf1, 0xf1, 0x11, 0xd1, 0xb1, 0xd1, 0x11, 0xf1, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x00, 0x00, 0xff, 0x00, 0x00, 0x7f, 0x7f, 0x09, 0x09, 0x0f, 0x06, 0x00, 0x7f, 0x7f, 0x19, 0x39, 0x6f, 0x46, 0x00, 0x7f, 0x7f, 0x49, 0x49, 0x41, 0x41, 0x00, 0x26, 0x6f, 0x49, 0x49, 0x7b, 0x32, 0x00, 0x26, 0x6f, 0x49, 0x49, 0x7b, 0x32, 
0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0x02, 0x79, 0xcd, 0x95, 0xa5, 0xcd, 0x79, 0x01, 0x11, 0x11, 0x11, 0x01, 0xf9, 0xf9, 0x01, 0x01, 0x00, 0x00, 0xff, 0x00, 0x00, 0x7f, 0x7f, 0x09, 0x09, 0x0f, 0x06, 0x00, 0x7f, 0x7f, 0x40, 0x40, 0x40, 0x40, 0x00, 0x7c, 0x7e, 0x0b, 0x0b, 0x7e, 0x7c, 0x00, 0x07, 0x0f, 0x78, 0x78, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0xff, 0x00, 0x00, 0x1f, 0x3f, 0x3f, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3e, 0x36, 0x36, 0x3e, 0x36, 0x3e, 0x36, 0x3e, 0x36, 0x36, 0x3e, 0x36, 0x36, 0x3e, 0x36, 0x00, 0x00, 0xff, 0x00, 0x00, 0x3e, 0x7f, 0x41, 0x41, 0x7f, 0x3e, 0x00, 0x7f, 0x7f, 0x0e, 0x1c, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x3f, 0x40, 0x50, 0x40, 0x40, 0x40, 0x78, 0x46, 0x41, 0x41, 0x59, 0x59, 0x41, 0x41, 0x41, 0x41, 0x59, 0x59, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x01, 0x01, 0x7f, 0x7f, 0x01, 0x01, 0x00, 0x7c, 0x7e, 0x0b, 0x0b, 0x7e, 0x7c, 0x00, 0x7f, 0x7f, 0x09, 0x09, 0x0f, 0x06, 0x00, 0x7f, 0x7f, 0x49, 0x49, 0x41, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#else
1,1,1
#endif
};

const uint8_t PROGMEM PPOT_Arrow[] = {
    5, 8, // 5x7 px image
    
    // #016 Symbol '►' (U+25BA Black Right-Pointing Pointer)
    0x7F,  // ▓░░░░░░░
    0x7F,  // ▓░░░░░░░
    0x3E,  // ▓▓░░░░░▓
    0x1C,  // ▓▓▓░░░▓▓
    0x08   // ▓▓▓▓░▓▓▓
    
};

const uint8_t PROGMEM PPOT_Spindle[] = {
    2, 8,  // 2x8 px image
    
    0xD4,  // ░░▓░▓░▓▓
    0xD2   // ░░▓░▓▓░▓
};
