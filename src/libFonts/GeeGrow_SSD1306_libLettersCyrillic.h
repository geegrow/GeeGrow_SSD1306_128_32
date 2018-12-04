/*!
 * @file GeeGrow_SSD1306_libLettersCyrillic.h
 *
 * This is an addon library for the GeeGrow SSD1306 128x32 display,
   which implements support of cyrillic letters
 * https://www.geegrow.ru
 *
 * @section author Author
 * Written by Anton Pomazanov
 *
 * @section license License
 * BSD license, all text here must be included in any redistribution.
 *
 */

#ifndef _GEEGROW_SSD1306_LIBLETTERS_CYRILLIC_H_
#define _GEEGROW_SSD1306_LIBLETTERS_CYRILLIC_H_

#include <Arduino.h>
#include <avr/pgmspace.h>
#include <GeeGrow_SSD1306_defines.h>

/**************************************************************************/
/*!
	@brief  Class that allows to use cyrillic letters
*/
/**************************************************************************/
class GeeGrow_SSD1306_libLettersCyrillic {
	public:
		GeeGrow_SSD1306_libLettersCyrillic(){}
		~GeeGrow_SSD1306_libLettersCyrillic(){}
		uint8_t* getBitMap(char _char, uint8_t _encoding);
};

/**************************************************************************/
/*!
	@brief  Bitmaps for cyrillic letters
*/
/**************************************************************************/
const uint8_t fontLibLettersCyrillic[] PROGMEM = {
	0x7C, 0x12, 0x11, 0x12, 0x7C,	// А (A)
	0x7F, 0x49, 0x49, 0x49, 0x79,	// Б (B)
	0x7F, 0x49, 0x49, 0x49, 0x36,	// В (W)
	0x00, 0x7F, 0x01, 0x01, 0x01,	// Г (G)
	0x60, 0x3F, 0x21, 0x3F, 0x60,	// Д (D)
	0x7F, 0x49, 0x49, 0x49, 0x41, 	// Е (E)
	0x63, 0x1C, 0x7F, 0x1C, 0x63,	// Ж (ZH)
	0x22, 0x41, 0x49, 0x4D, 0x32,	// З (Z)
	0x7F, 0x10, 0x08, 0x04, 0x7F, 	// И (I)
	0x7F, 0x10, 0x09, 0x04, 0x7F,	// Й (IY)
	0x7F, 0x08, 0x14, 0x22, 0x41,	// К (K)
	0x40, 0x3F, 0x01, 0x01, 0x7F,	// Л (L)
	0x7F, 0x02, 0x1C, 0x02, 0x7F,	// М (M)
	0x7F, 0x08, 0x08, 0x08, 0x7F,	// Н (N)
	0x3E, 0x41, 0x41, 0x41, 0x3E,	// О (O)
	0x7F, 0x01, 0x01, 0x01, 0x7F,	// П (P)
	0x7F, 0x09, 0x09, 0x09, 0x06,	// Р (R)
	0x3E, 0x41, 0x41, 0x41, 0x22,	// С (S)
	0x03, 0x01, 0x7F, 0x01, 0x03,	// Т (T)
	0x47, 0x28, 0x10, 0x08, 0x07,	// У (U)
	0x1E, 0x21, 0x7F, 0x21, 0x1E,	// Ф (F)
	0x63, 0x14, 0x08, 0x14, 0x63,	// Х (H)
	0x7F, 0x40, 0x40, 0x7F, 0xC0,	// Ц (TS)
	0x07, 0x08, 0x08, 0x08, 0x7F,	// Ч (CH)
	0x7F, 0x40, 0x7F, 0x40, 0x7F,	// Ш (SH)
	0x7F, 0x40, 0x7F, 0x40, 0xFF,	// Щ (soft SH)
	0x01, 0x7F, 0x48, 0x48, 0x38,	// Ъ (HARD SIGN)
	0x7F, 0x48, 0x78, 0x00, 0x7F,	// Ы (hard I)
	0x7F, 0x48, 0x48, 0x48, 0x78,	// Ь (SOFT SIGN)
	0x41, 0x49, 0x49, 0x2A, 0x1C,	// Э (hard E)
	0x7F, 0x08, 0x3E, 0x41, 0x3E,	// Ю (YU)
	0x46, 0x29, 0x19, 0x09, 0x7F,	// Я (YA)

	0x20, 0x54, 0x54, 0x78, 0x40,	// a (a)
	0x00, 0x38, 0x54, 0x54, 0x22,	// б (b)
	0x00, 0x7C, 0x54, 0x54, 0x28,	// в (w)
	0x00, 0x7C, 0x04, 0x04, 0x00,	// г (g)
	0x60, 0x3C, 0x24, 0x3C, 0x60,	// д (d)
	0x38, 0x54, 0x54, 0x54, 0x18,	// e (e)
	0x44, 0x38, 0x7C, 0x38, 0x44,	// ж (zh)
	0x00, 0x44, 0x54, 0x54, 0x28,	// з (z)
	0x7C, 0x20, 0x10, 0x08, 0x7C,	// и (i)
	0x7C, 0x20, 0x12, 0x08, 0x7C,	// й (iy)
	0x00, 0x7C, 0x10, 0x28, 0x44,	// к (k)
	0x40, 0x38, 0x04, 0x04, 0x7C,	// л (l)
	0x7C, 0x10, 0x20, 0x10, 0x7C,	// м (m)
	0x7C, 0x10, 0x10, 0x10, 0x7C,	// н (n)
	0x38, 0x44, 0x44, 0x44, 0x38,	// o (o)
	0x00, 0x7C, 0x04, 0x04, 0x7C,	// п (p)
	0x00, 0x7C, 0x14, 0x14, 0x08,	// p (r)
	0x38, 0x44, 0x44, 0x44, 0x28,	// c (s)
	0x04, 0x04, 0x7C, 0x04, 0x04,	// т (t)
	0x00, 0x4C, 0x30, 0x10, 0x0C,	// y (u)
	0x18, 0x24, 0x7C, 0x24, 0x18,	// ф (f)
	0x44, 0x28, 0x10, 0x28, 0x44,	// x (h)
	0x00, 0x7C, 0x40, 0x7C, 0xC0,	// ц (ts)
	0x00, 0x0C, 0x10, 0x10, 0x7C,	// ч (ch)
	0x7C, 0x40, 0x7C, 0x40, 0x7C,	// ш (sh)
	0x7C, 0x40, 0x7C, 0x40, 0xFC,	// щ (soft sh)
	0x04, 0x7C, 0x50, 0x50, 0x20,	// ъ (hard sign)
	0x7C, 0x50, 0x70, 0x00, 0x7C,	// ы (hard i)
	0x00, 0x7C, 0x50, 0x50, 0x20,	// ь (soft sign)
	0x00, 0x44, 0x54, 0x54, 0x38,	// э (hard e)
	0x7C, 0x10, 0x38, 0x44, 0x38,	// ю (yu)
	0x00, 0x48, 0x34, 0x14, 0x7C	// я (ya)
};

#endif /* _GEEGROW_SSD1306_LIBLETTERS_CYRILLIC_H_ */
