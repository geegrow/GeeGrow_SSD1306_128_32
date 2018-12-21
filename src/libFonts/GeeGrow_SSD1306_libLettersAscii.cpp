/*!
 * @file GeeGrow_SSD1306_libLettersAscii.cpp
 *
 * This is an addon library for the GeeGrow SSD1306 128x32 display,
   which implements support of ASCII letters
 * https://geegrow.ru
 *
 * @section author Author
 * Written by Anton Pomazanov
 *
 * @section license License
 * BSD license, all text here must be included in any redistribution.
 *
 */

#include "GeeGrow_SSD1306_libLettersAscii.h"

/**************************************************************************/
/*!
    @brief    Send a bitmap of certain ASCII letter
    @param    _char    Symbol to be sent
    @return   Pointer to bitmap array
*/
/**************************************************************************/
uint8_t* GeeGrow_SSD1306_libLettersAscii::getBitMap(char _char){
    uint16_t idx = 0;
    // Check if letter is uppercase or lowercase
    if ((uint8_t)_char >= 65 && (uint8_t)_char <= 90)            // Uppercase
        idx = ((uint8_t)_char - 65) * FONT_WIDTH;
    else if ((uint8_t)_char >= 97 && (uint8_t)_char <= 122)      // Lowercase
        idx = ((uint8_t)_char - 97 + 26) * FONT_WIDTH;
    else {
        Serial.print(F("getBitMap(): char not supported: "));
        Serial.println((uint8_t)_char, DEC);
        return;
    }
    return (fontLibLettersAscii + idx);
}
