/*!
 * @file GeeGrow_SSD1306_tools.h
 *
 * These are auxiliary structs and defines for GeeGrow SSD1306 library
 * https://www.geegrow.ru
 *
 * @section author Author
 * Written by Anton Pomazanov
 *
 * @section license License
 * BSD license, all text here must be included in any redistribution.
 *
 */

#ifndef _GEEGROW_SSD1306_TOOLS_H_
#define _GEEGROW_SSD1306_TOOLS_H_

/**************************************************************************/
/*!
	@brief	Swap two numbers
*/
/**************************************************************************/
#define SWAP(a, b) {uint8_t t = a; a = b; b = t;}

/**************************************************************************/
/*!
	@brief	Colors
*/
/**************************************************************************/
enum {	WHITE,
		BLACK
	};

/**************************************************************************/
/*!
	@brief	Rotation modes
*/
/**************************************************************************/
enum {	ROTATION_UP,
		ROTATION_DOWN,
		ROTATION_LEFT,
		ROTATION_RIGHT
	};

/**************************************************************************/
/*!
	@brief	Struct to store current display parameters
*/
/**************************************************************************/
struct params_t {
		int16_t width;
		int16_t height;
		uint8_t rotation;
};

#endif /* _GEEGROW_SSD1306_TOOLS_H_ */
