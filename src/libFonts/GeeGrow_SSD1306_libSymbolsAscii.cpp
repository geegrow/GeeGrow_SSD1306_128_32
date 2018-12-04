/*!
 * @file GeeGrow_SSD1306_libSymbolsAscii.cpp
 *
 * This is an addon library for the GeeGrow SSD1306 128x32 display,
   which implements support of ASCII special symbols
 * https://www.geegrow.ru
 *
 * @section author Author
 * Written by Anton Pomazanov
 *
 * @section license License
 * BSD license, all text here must be included in any redistribution.
 *
 */

#include "GeeGrow_SSD1306_libSymbolsAscii.h"

/**************************************************************************/
/*!
    @brief  Send a bitmap of certain ASCII special symbol
	@param	_char	Symbol to be sent
	@return Pointer to bitmap array
*/
/**************************************************************************/
uint8_t* GeeGrow_SSD1306_libSymbolsAscii::getBitMap(char _char){
	uint8_t idx = 0;
	// Check the number of "block" in ASCII which contains the synbol
	if ((uint8_t)_char >= 32 && (uint8_t)_char <= 47)
		idx = ((uint8_t)_char - 32) * FONT_WIDTH;
	else if ((uint8_t)_char >= 58 && (uint8_t)_char <= 64)
		idx = ((uint8_t)_char - 58 + 16) * FONT_WIDTH;
	else if ((uint8_t)_char >= 91 && (uint8_t)_char <= 96)
		idx = ((uint8_t)_char - 91 + 16 + 7) * FONT_WIDTH;
	else if ((uint8_t)_char >= 123 && (uint8_t)_char <= 126)
		idx = ((uint8_t)_char - 123 + 16 + 7 + 6) * FONT_WIDTH;
	else {
		Serial.print(F("getBitMap(): char not supported: "));
		Serial.println((uint8_t)_char, DEC);
		return;
	}
	return (fontLibSymbolsAscii + idx);
}
