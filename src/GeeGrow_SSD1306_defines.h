#ifndef _GEEGROW_SSD1306_DEFINES_H_
#define _GEEGROW_SSD1306_DEFINES_H_

/**************************************************************************/
/*!
	@brief  I2C address
*/
/**************************************************************************/
#define I2C_ADDRESS		0x3C

/**************************************************************************/
/*!
	@brief  Hardware screen resolution
*/
/**************************************************************************/
#define LCD_WIDTH	128
#define LCD_HEIGHT	32

/**************************************************************************/
/*!
	@brief  Font size
*/
/**************************************************************************/
#define FONT_WIDTH  5
#define FONT_HEIGHT 8

/**************************************************************************/
/*!
	@brief  Encodings
*/
/**************************************************************************/
#define ENCODING_UTF8   1
#define	ENCODING_CP1251 2

/**************************************************************************/
/*!
	@brief  Initialization commands from datasheet
*/
/**************************************************************************/
#define SSD1306_SETCONTRAST 			0x81
#define SSD1306_DISPLAYALLON_RESUME 	0xA4
#define SSD1306_DISPLAYALLON 			0xA5
#define SSD1306_NORMALDISPLAY 			0xA6
#define SSD1306_INVERTDISPLAY 			0xA7
#define SSD1306_DISPLAYOFF 				0xAE
#define SSD1306_DISPLAYON 				0xAF
#define SSD1306_SETDISPLAYOFFSET 		0xD3
#define SSD1306_SETCOMPINS 				0xDA
#define SSD1306_SETVCOMDETECT 			0xDB
#define SSD1306_SETDISPLAYCLOCKDIV 		0xD5
#define SSD1306_SETPRECHARGE 			0xD9
#define SSD1306_SETMULTIPLEX 			0xA8
#define SSD1306_SETLOWCOLUMN 			0x00
#define SSD1306_SETHIGHCOLUMN 			0x10
#define SSD1306_SETSTARTLINE 			0x40
#define SSD1306_MEMORYMODE 				0x20
#define SSD1306_COLUMNADDR 				0x21
#define SSD1306_PAGEADDR   				0x22
#define SSD1306_COMSCANINC 				0xC0
#define SSD1306_COMSCANDEC 				0xC8
#define SSD1306_SEGREMAP 				0xA0
#define SSD1306_CHARGEPUMP 				0x8D
#define SSD1306_EXTERNALVCC 			0x01
#define SSD1306_SWITCHCAPVCC 			0x02

/**************************************************************************/
/*!
	@brief  Libraries that can be attached
*/
/**************************************************************************/
#define LIB_NUMBERS_ASCII		(1 << 1)
#define LIB_LETTERS_ASCII		(1 << 2)
#define LIB_SYMBOLS_ASCII		(1 << 3)
#define LIB_LETTERS_CYRILLIC	(1 << 4)

/**************************************************************************/
/*!
	@brief  Commands for scrolling from datasheet
*/
/**************************************************************************/
#define SSD1306_ACTIVATE_SCROLL                         0x2F
#define SSD1306_DEACTIVATE_SCROLL                       0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA                0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL                 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL                  0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL    0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL     0x2A


#endif /* _GEEGROW_SSD1306_DEFINES_H_ */
