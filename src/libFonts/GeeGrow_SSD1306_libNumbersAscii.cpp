/*!
 * @file GeeGrow_SSD1306_libNumbersAscii.cpp
 *
 * This is an addon library for the GeeGrow SSD1306 128x32 display,
   which implements support of ASCII numbers
 * https://www.geegrow.ru
 *
 * @section author Author
 * Written by Anton Pomazanov
 *
 * @section license License
 * BSD license, all text here must be included in any redistribution.
 *
 */

#include "GeeGrow_SSD1306_libNumbersAscii.h"

/**************************************************************************/
/*!
	@brief  Send a bitmap of certain ASCII number
	@param	_char	Symbol to be sent
	@return Pointer to bitmap array
*/
/**************************************************************************/
uint8_t* GeeGrow_SSD1306_libNumbersAscii::getBitMap(char _char){
	uint8_t idx = 0;
	if ((uint8_t)_char >= 48 && (uint8_t)_char <= 57)
		idx = ((uint8_t)_char - 48) * FONT_WIDTH;
	else {
		Serial.print(F("getBitMap(): char not supported: "));
		Serial.println((uint8_t)_char, DEC);
		return;
	}
	return (fontLibNumbersAscii + idx);
}
