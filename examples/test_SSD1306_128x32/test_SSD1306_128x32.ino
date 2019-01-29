#include <GeeGrow_SSD1306_128x32.h>

// Speed of "filling" the display
#define FILL_SPEED  4

// LUcase
#define LUCASE_UPPER  1
#define LUCASE_LOWER  2

GeeGrow_SSD1306_128x32 *display;
//GeeGrow_SSD1306_128x32_I2Cimprvd *display;
uint8_t x = 0;
uint8_t y = 0;

void lettersABC_rus(uint8_t color, uint8_t LUcase);
void lines(uint8_t color);
void filling(uint8_t color);
void numbers123(uint8_t color);
void lettersABC(uint8_t color, uint8_t LUcase);
void specSymbols(uint8_t color);
void checkRotation();

void setup() {

//    Serial.begin(9600);
//    while(!Serial);

    display = new GeeGrow_SSD1306_128x32();

    //I2C i2c_cli;
    //I2CTransport::me().setClient(&i2c_cli);
    //display = new GeeGrow_SSD1306_128x32_I2Cimprvd();

    display->attachLibs(LIB_LETTERS_ASCII | LIB_NUMBERS_ASCII | LIB_SYMBOLS_ASCII | LIB_LETTERS_CYRILLIC);
    display->initialize();
    display->fillDisplay(BLACK);
    display->refresh();

    // TESTS

//    checkRotation();                            // OK
//    lines(WHITE);                               // OK
//    numbers123(WHITE);                          // OK
//    lettersABC(WHITE, LUCASE_UPPER);            // OK
//    lettersABC(WHITE, LUCASE_LOWER);            // OK
//    specSymbols(WHITE);                         // OK
//    lettersABC_rus(WHITE, LUCASE_UPPER);        // OK
//    lettersABC_rus(WHITE, LUCASE_LOWER);        // OK
//    display->drawCircle(64, 20, 10, WHITE);     // OK
//    display->drawRect(10, 5, 50, 20, WHITE);    // OK
//    display->fillRect(10, 5, 50, 20, WHITE);    // OK
//    display->fillCircle(64, 20, 10, WHITE);     // OK
    display->printStr("Geegrow", 5, 0, 2, 2, WHITE);     // OK
    display->refresh();

    display->startScrollDiagLeft(0x00, 0x0F);       // OK
}

void loop() {}

void lettersABC_rus(uint8_t color, uint8_t LUcase) {
    uint8_t offset = 0;
    uint8_t x0 = 1;
    uint8_t y0 = 1;

    display->setRotation(ROTATION_UP);
    display->setEncoding(ENCODING_CP1251);

    if (LUcase == LUCASE_UPPER)
        offset = 192;
    if (LUcase == LUCASE_LOWER)
        offset = 224;

    if (color == WHITE)
        display->fillDisplay(BLACK);
    if (color == BLACK)
        display->fillDisplay(WHITE);

    for (uint8_t i = 0; i < 11; i++) {
        display->printChar((char)(offset+i), x0+8*i, y0, 1, color);
        display->printChar((char)(offset+11+i), x0+8*i, y0+9, 1, color);
        display->printChar((char)(offset+21+i), x0+8*i, y0+18, 1, color);
    }

  display->refresh();
}

void lines(uint8_t color) {
    display->setRotation(ROTATION_UP);
    display->fillDisplay(BLACK);
    for (uint8_t i = 0; i < 13; i++) {
        display->drawLine(0, 0, i*10, 31, color);
        display->refresh();
        delay(300);
    }
    display->fillDisplay(BLACK);
    for (uint8_t i = 0; i < 13; i++) {
        display->drawLine(0, 31, i*10, 0, color);
        display->refresh();
        delay(300);
    }
    display->fillDisplay(BLACK);
    for (int8_t i = 12; i >= 0; i--) {
        display->drawLine(127, 0, i*10, 31, color);
        display->refresh();
        delay(300);
    }
    display->fillDisplay(BLACK);
    for (int8_t i = 12; i >= 0; i--) {
        display->drawLine(127, 31, i*10, 0, color);
        display->refresh();
        delay(300);
    }
}

void specSymbols(uint8_t color) {
  uint8_t x0 = 0;
  uint8_t y0 = 0;

  display->setRotation(ROTATION_UP);
  display->fillDisplay(BLACK);

  for (uint8_t i = 0; i < 15; i++)
    display->printChar((char)(33+i), x0+8*i, y0, 1, color);
  for (uint8_t i = 0; i < 7; i++)
    display->printChar((char)(58+i), x0+8*i, y0+8, 1, color);
  for (uint8_t i = 0; i < 6; i++)
    display->printChar((char)(91+i), x0+8*i, y0+16, 1, color);
  for (uint8_t i = 0; i < 4; i++)
    display->printChar((char)(123+i), x0+8*i, y0+24, 1, color);

  display->refresh();
}

void lettersABC(uint8_t color, uint8_t LUcase) {
  uint8_t offset = 0;
  uint8_t x0 = 1;
  uint8_t y0 = 0;

  display->setRotation(ROTATION_UP);

  if (LUcase == LUCASE_UPPER)
    offset = 65;
  if (LUcase == LUCASE_LOWER)
    offset = 97;

  if (color == WHITE)
    display->fillDisplay(BLACK);
  if (color == BLACK)
    display->fillDisplay(WHITE);

  for (uint8_t i = 0; i < 13; i++) {
      display->printChar((char)(offset+i), x0+8*i, y0, 1, color);
      display->printChar((char)(offset+13+i), x0+8*i, y0+9, 1, color);
  }

  display->refresh();
}

void numbers123(uint8_t color) {
    uint8_t x0 = 1;
    uint8_t y0 = 0;

    display->setRotation(ROTATION_UP);

    if (color == WHITE)
        display->fillDisplay(BLACK);
    if (color == BLACK)
        display->fillDisplay(WHITE);

    for (uint8_t i = 0; i < 10; i++)
        display->printChar((char)(48+i), x0+8*i, y0, 1, color);
    display->refresh();
}


void checkRotation() {
  display->setRotation(ROTATION_LEFT);
  filling(WHITE);
  display->fillDisplay(BLACK);
  display->refresh();

  display->setRotation(ROTATION_UP);
  filling(WHITE);
  display->fillDisplay(BLACK);
  display->refresh();

  display->setRotation(ROTATION_DOWN);
  filling(WHITE);
  display->fillDisplay(BLACK);
  display->refresh();

  display->setRotation(ROTATION_RIGHT);
  filling(WHITE);
  display->fillDisplay(BLACK);
  display->refresh();
}

void filling(uint8_t color) {
  uint8_t height = display->getHeight();
  uint8_t width = display->getWidth();

  for (uint8_t j = 0; j < height; j+=8)
    for (uint8_t i = 0; i < width; i+=FILL_SPEED) {
      for (uint8_t s = 0; s < FILL_SPEED; s++)
        for (uint8_t k = 0; k < 8; k++)
          display->drawPixel(i+s, j+k, color);
      display->refresh();
      delay(30);
    }
}
