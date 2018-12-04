/*!
 * @file GeeGrow_SSD1306_libNumbersAscii.h
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

#ifndef _GEEGROW_SSD1306_LIBNUMBERS_ASCII_H_
#define _GEEGROW_SSD1306_LIBNUMBERS_ASCII_H_

#include <Arduino.h>
#include <avr/pgmspace.h>
#include <GeeGrow_SSD1306_defines.h>

/**************************************************************************/
/*!
    @brief  Class that allows to use ASCII numbers
*/
/**************************************************************************/
class GeeGrow_SSD1306_libNumbersAscii {
	public:
		GeeGrow_SSD1306_libNumbersAscii(){}
		~GeeGrow_SSD1306_libNumbersAscii(){}
		uint8_t* getBitMap(char _char);
};

/**************************************************************************/
/*!
    @brief  Bitmaps for ASCII numbers
*/
/**************************************************************************/
const uint8_t fontLibNumbersAscii[] PROGMEM = {
	0x3E, 0x51, 0x49, 0x45, 0x3E,	// 0
	0x00, 0x42, 0x7F, 0x40, 0x00,	// 1
	0x72, 0x49, 0x49, 0x49, 0x46,	// 2
	0x21, 0x41, 0x49, 0x4D, 0x33,	// 3
	0x18, 0x14, 0x12, 0x7F, 0x10,	// 4
	0x27, 0x45, 0x45, 0x45, 0x39,	// 5
	0x3C, 0x4A, 0x49, 0x49, 0x31,	// 6
	0x41, 0x21, 0x11, 0x09, 0x07,	// 7
	0x36, 0x49, 0x49, 0x49, 0x36,	// 8
	0x46, 0x49, 0x49, 0x29, 0x1E	// 9
};

#endif /* _GEEGROW_SSD1306_LIBNUMBERS_ASCII_H_ */
