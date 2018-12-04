/*!
 * @file GeeGrow_SSD1306_128_32.cpp
 *
 * This is a library for the GeeGrow SSD1306 128x32 display
 * https://www.geegrow.ru
 *
 * @section author Author
 * Written by Anton Pomazanov
 *
 * @section license License
 * BSD license, all text here must be included in any redistribution.
 *
 */

#include <GeeGrow_SSD1306_128_32.h>

/**************************************************************************/
/*!
	@brief	Instantiate GeeGrow SSD1306 driver for 128x32 display
*/
/**************************************************************************/
GeeGrow_SSD1306_128_32::GeeGrow_SSD1306_128_32(){
	this->setRotation(ROTATION_UP);
}

/**************************************************************************/
/*!
	@brief	Attach separate libraries with different symbol packs
	@param	_libs	Bitmask which defines libs that should be attached
*/
/**************************************************************************/
void GeeGrow_SSD1306_128_32::attachLibs(uint8_t _libs){
	// Create objects according to libs
	if (_libs & LIB_LETTERS_ASCII){
		if (this->libLettersAscii == NULL)
			this->libLettersAscii = new GeeGrow_SSD1306_libLettersAscii();
		else
			Serial.println(F("attachLibs(): LIB_LETTERS_ASCII already set"));
	}

	if (_libs & LIB_NUMBERS_ASCII){
		if (this->libNumbersAscii == NULL)
			this->libNumbersAscii = new GeeGrow_SSD1306_libNumbersAscii();
		else
			Serial.println(F("attachLibs(): LIB_NUMBERS_ASCII already set"));
	}

	if (_libs & LIB_SYMBOLS_ASCII){
		if (this->libSymbolsAscii == NULL)
			this->libSymbolsAscii = new GeeGrow_SSD1306_libSymbolsAscii();
		else
			Serial.println(F("attachLibs(): LIB_SYMBOLS_ASCII already set"));
	}

	if (_libs & LIB_LETTERS_CYRILLIC){
		if (this->libLettersCyrillic == NULL){
			this->libLettersCyrillic = new GeeGrow_SSD1306_libLettersCyrillic();
			this->encoding = ENCODING_UTF8;
		} else
			Serial.println(F("attachLibs(): LIB_LETTERS_CYRILLIC already set"));
	}
}

/**************************************************************************/
/*!
	@brief	Send command via I2C
	@param	_cmd	Command byte
*/
/**************************************************************************/
void GeeGrow_SSD1306_128_32::ssd1306_command(uint8_t _cmd) {
	uint8_t control = 0x00;   // Co = 0, D/C = 0
	Wire.beginTransmission(I2C_ADDRESS);
	Wire.write(control);
	Wire.write(_cmd);
	Wire.endTransmission();
}

/**************************************************************************/
/*!
	@brief	Init sequence for SSD1306 display
*/
/**************************************************************************/
void GeeGrow_SSD1306_128_32::initialize() {
	// I2C Init
	Wire.begin();

	this->ssd1306_command(SSD1306_DISPLAYOFF);
	this->ssd1306_command(SSD1306_SETDISPLAYCLOCKDIV);
	this->ssd1306_command(0x80);
	this->ssd1306_command(SSD1306_SETMULTIPLEX);
	this->ssd1306_command(LCD_HEIGHT - 1);
	this->ssd1306_command(SSD1306_SETDISPLAYOFFSET);
	this->ssd1306_command(0x0);
	this->ssd1306_command(SSD1306_SETSTARTLINE | 0x0);
	this->ssd1306_command(SSD1306_CHARGEPUMP);
	this->ssd1306_command(0x14);
	this->ssd1306_command(SSD1306_MEMORYMODE);
	this->ssd1306_command(0x00);
	this->ssd1306_command(SSD1306_SEGREMAP | 0x1);
	this->ssd1306_command(SSD1306_COMSCANDEC);
	this->ssd1306_command(SSD1306_SETCOMPINS);
	this->ssd1306_command(0x02);
	this->ssd1306_command(SSD1306_SETCONTRAST);
	this->ssd1306_command(0x8F);
	this->ssd1306_command(SSD1306_SETPRECHARGE);
	this->ssd1306_command(0xF1);
	this->ssd1306_command(SSD1306_SETVCOMDETECT);
	this->ssd1306_command(0x40);
	this->ssd1306_command(SSD1306_DISPLAYALLON_RESUME);
	this->ssd1306_command(SSD1306_NORMALDISPLAY);
	this->ssd1306_command(SSD1306_DEACTIVATE_SCROLL);
	this->ssd1306_command(SSD1306_DISPLAYON);
}

/**************************************************************************/
/*!
	@brief	Refresh image on the screen (copy data from buffer to display RAM)
	@note	Send data by portions of 16 bytes. TX_BUFFER size is 32 bytes (Wire.h),
			but we can't make portions of 32 bytes, as every packet contains
			1 control byte, so packet size will be 33.
*/
/**************************************************************************/
void GeeGrow_SSD1306_128_32::refresh() {
	this->ssd1306_command(SSD1306_COLUMNADDR);
	this->ssd1306_command(0);
	this->ssd1306_command(LCD_WIDTH - 1);

	this->ssd1306_command(SSD1306_PAGEADDR);
	this->ssd1306_command(0);
	this->ssd1306_command(3);

	for (uint16_t i = 0; i < (LCD_WIDTH/8 * LCD_HEIGHT); i += 16) {
		Wire.beginTransmission(I2C_ADDRESS);
		Wire.write(0x40);	// 0b01000000 - control byte, D/C bit is set,
							// determines that next bytes are data
		Wire.write(this->buffer + i, 16);
		Wire.endTransmission();
	}
}

/**************************************************************************/
/*!
	@brief	Fill screen with certain color
	@param	_color	Color to fill screen
*/
/**************************************************************************/
void GeeGrow_SSD1306_128_32::fillDisplay(uint8_t _color) {
	memset(this->buffer, 0xFF, (LCD_WIDTH/8 * LCD_HEIGHT));
}

/**************************************************************************/
/*!
	@brief	Set brightness of screen
	@param	_brightness	Brightness value to set
	@note	Brightness interval is 0x00 - 0xFF
*/
/**************************************************************************/
void GeeGrow_SSD1306_128_32::setBrightness(uint8_t _brightness) {
	this->ssd1306_command(SSD1306_SETCONTRAST);
	this->ssd1306_command(_brightness);
}

/**************************************************************************/
/*!
	@brief	Set current rotation
	@param	_rotation	Rotation mode
*/
/**************************************************************************/
void GeeGrow_SSD1306_128_32::setRotation(uint8_t _rotation) {
	this->params.rotation = _rotation;
	switch (_rotation) {
		case ROTATION_UP:
			this->params.width  = LCD_WIDTH;
			this->params.height = LCD_HEIGHT;
			break;
		case ROTATION_DOWN:
			this->params.width  = LCD_WIDTH;
			this->params.height = LCD_HEIGHT;
			break;
		case ROTATION_LEFT:
			this->params.width  = LCD_HEIGHT;
			this->params.height = LCD_WIDTH;
			break;
		case ROTATION_RIGHT:
			this->params.width  = LCD_HEIGHT;
			this->params.height = LCD_WIDTH;
			break;
		default:
			// error
			break;
	}
}

/**************************************************************************/
/*!
	@brief	Start right handed scrolling
	@param	_start	Start row value
	@param	_stop	End row value
	@note	The display is 16 rows high
*/
/**************************************************************************/
void GeeGrow_SSD1306_128_32::startScrollRight(uint8_t _start, uint8_t _stop){
	this->ssd1306_command(SSD1306_RIGHT_HORIZONTAL_SCROLL);
	this->ssd1306_command(0x00);
	this->ssd1306_command(_start);
	this->ssd1306_command(0x00);
	this->ssd1306_command(_stop);
	this->ssd1306_command(0x00);
	this->ssd1306_command(0xFF);
	this->ssd1306_command(SSD1306_ACTIVATE_SCROLL);
}

/**************************************************************************/
/*!
	@brief	Start left handed scrolling
	@param	_start	Start row value
	@param	_stop	End row value
	@note	The display is 16 rows high
*/
/**************************************************************************/
void GeeGrow_SSD1306_128_32::startScrollLeft(uint8_t _start, uint8_t _stop){
	this->ssd1306_command(SSD1306_LEFT_HORIZONTAL_SCROLL);
	this->ssd1306_command(0x00);
	this->ssd1306_command(_start);
	this->ssd1306_command(0x00);
	this->ssd1306_command(_stop);
	this->ssd1306_command(0x00);
	this->ssd1306_command(0xFF);
	this->ssd1306_command(SSD1306_ACTIVATE_SCROLL);
}

/**************************************************************************/
/*!
	@brief	Start diagonal right handed scrolling
	@param	_start	Start row value
	@param	_stop	End row value
	@note	The display is 16 rows high
*/
/**************************************************************************/
void GeeGrow_SSD1306_128_32::startScrollDiagRight(uint8_t _start, uint8_t _stop){
	this->ssd1306_command(SSD1306_SET_VERTICAL_SCROLL_AREA);
	this->ssd1306_command(0x00);
	this->ssd1306_command(LCD_HEIGHT);
	this->ssd1306_command(SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL);
	this->ssd1306_command(0x00);
	this->ssd1306_command(_start);
	this->ssd1306_command(0x00);
	this->ssd1306_command(_stop);
	this->ssd1306_command(0x01);
	this->ssd1306_command(SSD1306_ACTIVATE_SCROLL);
}

/**************************************************************************/
/*!
	@brief	Start diagonal left handed scrolling
	@param	_start	Start row value
	@param	_stop	End row value
	@note	The display is 16 rows high
*/
/**************************************************************************/
void GeeGrow_SSD1306_128_32::startScrollDiagLeft(uint8_t _start, uint8_t _stop){
	this->ssd1306_command(SSD1306_SET_VERTICAL_SCROLL_AREA);
	this->ssd1306_command(0x00);
	this->ssd1306_command(LCD_HEIGHT);
	this->ssd1306_command(SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL);
	this->ssd1306_command(0x00);
	this->ssd1306_command(_start);
	this->ssd1306_command(0x00);
	this->ssd1306_command(_stop);
	this->ssd1306_command(0x01);
	this->ssd1306_command(SSD1306_ACTIVATE_SCROLL);
}

/**************************************************************************/
/*!
	@brief	Stop scrolling
*/
/**************************************************************************/
void GeeGrow_SSD1306_128_32::stopScroll(){
	this->ssd1306_command(SSD1306_DEACTIVATE_SCROLL);
}

/**************************************************************************/
/*!
	@brief	Get current height of display (depends on rotation mode)
	@return	Current height of display in pixels
*/
/**************************************************************************/
int16_t GeeGrow_SSD1306_128_32::getHeight(){
	return this->params.height;
}

/**************************************************************************/
/*!
	@brief	Get current width of display (depends on rotation mode)
	@return	Current width of display in pixels
*/
/**************************************************************************/
int16_t GeeGrow_SSD1306_128_32::getWidth(){
	return this->params.width;
}

/**************************************************************************/
/*!
	@brief	Get current rotation mode
	@return	Current rotation mode
*/
/**************************************************************************/
uint8_t GeeGrow_SSD1306_128_32::getRotation(){
	return this->params.rotation;
}

/**************************************************************************/
/*!
	@brief	Set a pixel with certain color
	@param	_x0			X coordinate of pixel
	@param	_y0			Y coordinate of pixel
	@param	_color		Color of pixel to set
	@return	Status byte
	@note	Coordinates are counted from top left corner of the screen
			in every rotation mode
*/
/**************************************************************************/
uint8_t GeeGrow_SSD1306_128_32::drawPixel(int16_t _x0, int16_t _y0, uint8_t _color){
	// Check coordinates
	if ((_x0 >= this->params.width) || (_y0 >= this->params.height)
		|| (_x0 < 0) || (_y0 < 0)
	){
		Serial.println(F("drawPixel():  invalid coordinates"));
		return 1;
	}

	int16_t x = 0;
	int16_t y = 0;

	switch (this->params.rotation) {
		case ROTATION_UP:
			x = _x0;
			y = _y0;
			break;
		case ROTATION_DOWN:
			x = this->params.width - _x0 - 1;
			y = this->params.height - _y0 - 1;
			break;
		case ROTATION_LEFT:
			x = _y0;
			y = this->params.width - _x0 - 1;
			break;
		case ROTATION_RIGHT:
			x = this->params.height - _y0 - 1;
			y = _x0;
			break;
		default:
			break;
	}

	switch (_color) {
		case WHITE:
			buffer[x + (y/FONT_HEIGHT)*LCD_WIDTH] |=  (1 << (y & 0b111));
			break;
		case BLACK:
			buffer[x + (y/FONT_HEIGHT)*LCD_WIDTH] &=  ~(1 << (y & 0b111));
			break;
		default:
			break;
	}
	return 0;
}

/**************************************************************************/
/*!
	@brief	Draw a line of certain color
	@param	_x0			X coordinate of start point
	@param	_y0			Y coordinate of start point
	@param	_x1			X coordinate of end point
	@param	_y1			Y coordinate of end point
	@param	_color		Color of line to draw
	@return	Status byte
	@note	Coordinates are counted from top left corner of the screen
			in every rotation mode
*/
/**************************************************************************/
uint8_t GeeGrow_SSD1306_128_32::drawLine(
	int16_t _x0,
	int16_t _y0,
	int16_t _x1,
	int16_t _y1,
	uint8_t _color
){
	// Check coordinates
	if ((_x0 < 0) || (_y0 < 0) || (_x1 < 0) || (_y1 < 0) ||
		(_x0 >= this->params.width) || (_x1 >= this->params.width) ||
		(_y0 >= this->params.height) || (_y1 >= this->params.height)
	){

		Serial.println(F("drawLine(): invalid coordinates"));
		return 1;
	}

	int16_t x = _x1 - _x0;
	int16_t y = _y1 - _y0;
	int16_t dx = abs(x);
	int16_t sx = (_x0 < _x1) ? 1 : -1;
	int16_t dy = -abs(y);
	int16_t sy = (_y0 < _y1) ? 1 : -1;
	int16_t err = dx + dy, e2;
	for (;;) {
		this->drawPixel(_x0, _y0, _color);
		e2 = 2*err;
		if (e2 >= dy) {
			if (_x0 == _x1)
				break;
			err += dy;
			_x0 += sx;
		}
		if (e2 <= dx){
			if (_y0 == _y1)
				break;
			err += dx;
			_y0 += sy;
		}
	}
	return 0;
}

/**************************************************************************/
/*!
	@brief	Draw a rectangle of certain color
	@param	_x0			X coordinate of start point
	@param	_y0			Y coordinate of start point
	@param	_width		Width of the rectangle
	@param	_height		Height of the rectangle
	@param	_color		Color of rectangle to draw
	@return	Status byte
	@note	Coordinates are counted from top left corner of the screen
			in every rotation mode
*/
/**************************************************************************/
uint8_t GeeGrow_SSD1306_128_32::drawRect(
	int16_t _x0,
	int16_t _y0,
	int16_t _width,
	int16_t _height,
	uint8_t _color
){
	// check coordinates
	if  ((_x0 < 0) || (_y0 < 0)
		|| ((_y0 + _height) >= this->params.height)
		|| ((_x0 + _width) >= this->params.width)
	){
		Serial.println(F("drawRect(): invalid coordinates"));
		return 1;
	}

	this->drawLine(_x0, _y0, _x0 + _width, _y0, _color);
	this->drawLine(_x0, _y0, _x0, _y0 + _height, _color);
	this->drawLine(_x0 + _width, _y0, _x0 + _width, _y0 + _height, _color);
	this->drawLine(_x0, _y0 + _height, _x0 + _width, _y0 + _height, _color);
	return 0;
}

/**************************************************************************/
/*!
	@brief	Draw a filled rectangle of certain color
	@param	_x0			X coordinate of start point
	@param	_y0			Y coordinate of start point
	@param	_width		Width of the rectangle
	@param	_height		Height of the rectangle
	@param	_color  	Color of rectangle to fill
	@return	Status byte
	@note	Coordinates are counted from top left corner of the screen
			in every rotation mode
*/
/**************************************************************************/
uint8_t GeeGrow_SSD1306_128_32::fillRect(
	int16_t _x0,
	int16_t _y0,
	int16_t _width,
	int16_t _height,
	uint8_t _color
){
	// check coordinates
	if  ((_x0 < 0) || (_y0 < 0) ||
		((_y0 + _height) > this->params.height) || ((_x0 + _width) > this->params.width)
	){
		Serial.println(F("fillRect(): invalid coordinates"));
		return 1;
	}

	for (uint8_t i = 0; i < _width; i++)
		for (uint8_t j = 0; j < _height; j++)
			this->drawPixel(_x0 + i, _y0 + j, _color);

	return 0;
}

/**************************************************************************/
/*!
	@brief	Draw a circle of certain color
	@param	_x0			X coordinate of center
	@param	_y0			Y coordinate of center
	@param	_radius		Radius of the circle
	@param	_color		Color of circle to draw
	@return	Status byte
	@note	Coordinates are counted from top left corner of the screen
			in every rotation mode
*/
/**************************************************************************/
uint8_t GeeGrow_SSD1306_128_32::drawCircle(
	int16_t _x0,
	int16_t _y0,
	int16_t _radius,
	uint8_t _color
){
	// Check coordinates
	if ((_x0 < 0) || (_y0 < 0) || (_x0 - _radius < 0) || (_y0 - _radius < 0) ||
		(_x0 + _radius >= this->params.width) || (_y0 + _radius >= this->params.height)
	){

		Serial.println(F("drawCircle(): invalid coordinates"));
		return 1;
	}

	int16_t x = -_radius;
	int16_t y = 0;
	int16_t err = 2 - 2*_radius;
	int16_t e2;
	while (x <= 0) {
		this->drawPixel(_x0 - 2*x, _y0 + y, _color);
		this->drawPixel(_x0 + 2*x, _y0 + y, _color);
		this->drawPixel(_x0 + 2*x, _y0 - y, _color);
		this->drawPixel(_x0 - 2*x, _y0 - y, _color);

		e2 = err;
		if (e2 <= y) {
			err += ++y * 2 + 1;
			if (-x == y && e2 <= x)
				e2 = 0;
		}
		if (e2 > x)
			err += ++x * 2 + 1;
	}
	return 0;
}

/**************************************************************************/
/*!
	@brief	Draw a filled circle of certain color
	@param	_x0			X coordinate of center
	@param	_y0			Y coordinate of center
	@param	_radius		Radius of the circle
	@param	_color  	Color of circle to fill
	@return	Status byte
	@note	Coordinates are counted from top left corner of the screen
			in every rotation mode
*/
/**************************************************************************/
uint8_t GeeGrow_SSD1306_128_32::fillCircle(
	int16_t _x0,
	int16_t _y0,
	int16_t _radius,
	uint8_t _color
){
	// Check coordinates
	if ((_x0 < 0) || (_y0 < 0) || (_x0 - _radius < 0) || (_y0 - _radius < 0) ||
		(_x0 + _radius >= this->params.width) || (_y0 + _radius >= this->params.height)
	){

		Serial.println(F("drawCircle(): invalid coordinates"));
		return 1;
	}

	int16_t x = -_radius;
	int16_t y = 0;
	int16_t err = 2 - 2*_radius;
	int16_t e2;
	while (x <= 0) {
		this->drawPixel(_x0 - 2*x, _y0 + y, _color);
		this->drawPixel(_x0 + 2*x, _y0 + y, _color);
		this->drawPixel(_x0 + 2*x, _y0 - y, _color);
		this->drawPixel(_x0 - 2*x, _y0 - y, _color);

		this->drawLine(_x0 - 2*x, _y0 - y, _x0 + 2*x, _y0 - y, _color);
		this->drawLine(_x0 - 2*x, _y0 + y, _x0 + 2*x, _y0 + y, _color);

		e2 = err;
		if (e2 <= y) {
			err += ++y * 2 + 1;
			if (-x == y && e2 <= x)
				e2 = 0;
		}
		if (e2 > x)
			err += ++x * 2 + 1;
	}
	return 0;
}

/**************************************************************************/
/*!
	@brief	Draw a triangle of certain color
	@param	_x0			X coordinate of first point
	@param	_y0			Y coordinate of first point
	@param	_x1			X coordinate of second point
	@param	_y1			Y coordinate of second point
	@param	_x2			X coordinate of third point
	@param	_y2			Y coordinate of third point
	@param	_color		Color of triangle to draw
	@return	Status byte
	@note	Coordinates are counted from top left corner of the screen
			in every rotation mode
*/
/**************************************************************************/
uint8_t GeeGrow_SSD1306_128_32::drawTriangle(
	int16_t _x0,
	int16_t _y0,
	int16_t _x1,
	int16_t _y1,
	int16_t _x2,
	int16_t _y2,
	uint8_t _color
){
	// Check coordinates
	if ((_x0 < 0) || (_y0 < 0) || (_x1 < 0) || (_y1 < 0) || (_x2 < 0) || (_y2 < 0) ||
		(_x0 >= this->params.width) || (_x1 >= this->params.width) || (_x2 >= this->params.width) ||
		(_y0 >= this->params.height) || (_y1 >= this->params.height) || (_y2 >= this->params.height)
	){

		Serial.println(F("drawTriangle(): invalid coordinates"));
		return 1;
	}

	this->drawLine(_x0, _y0, _x1, _y1, _color);
	this->drawLine(_x0, _y0, _x2, _y2, _color);
	this->drawLine(_x1, _y1, _x2, _y2, _color);
	return 0;
}

/**************************************************************************/
/*!
	@brief	Draw a user's bitmap
	@param	_buf		Pointer to source data buffer
	@param	_x0			X coordinate of top left corner of bitmap
	@param	_y0			Y coordinate of top left corner of bitmap
	@param	_width		Width of bitmap
	@param	_height		Height of bitmap
	@param	_color		Main color of bitmap
	@return	Status byte
	@note	The smallest piece of bitmap is 1x8 pixels (1 byte)
*/
/**************************************************************************/
uint8_t GeeGrow_SSD1306_128_32::drawBitmap(
	uint8_t* _buf,
	int16_t _x0,
	int16_t _y0,
	int16_t _width,
	int16_t _height,
	uint8_t _color
){
	// Check coordinates
	if ((_x0 < 0) || (_y0 < 0) ||
		(_x0 + _width > this->params.width) || (_y0 + _height > this->params.height) ||
		(_height % 8 != 0)
	){

		Serial.println(F("drawBitmap(): invalid bitmap or coordinates"));
		return 1;
	}

	uint8_t bg_color = (_color == WHITE ? BLACK : WHITE);
	// rows of bytes
	for (uint8_t i = 0; i < _height/8; i++)
		// columns
		for (int j = 0; j < _width; j++) {
			uint8_t tmp =  *(_buf + i*_width + j);
			for (uint8_t k = 0; k < 8; k++)
				if (tmp & (1 << k))
					this->drawPixel(_x0 + j, _y0 + i*8 + k, _color);
				else
					this->drawPixel(_x0 + j, _y0 + i*8 + k, bg_color);
		}
	return 0;
}

/**************************************************************************/
/*!
	@brief	Print a symbol from attached libs
	@param	_char		Symbol to be printed
	@param	_x0			X coordinate of top left corner of symbol
	@param	_y0			Y coordinate of top left corner of symbol
	@param	_size		Size of symbol
	@param	_color  	Color of symbol
	@return	Status byte
	@note	Symbols have 5x8 resolution (if size == 1). If size is 2, then
			resolution is 10x16 and so on.
*/
/**************************************************************************/
uint8_t GeeGrow_SSD1306_128_32::printChar(
	char _char,
	int16_t _x0,
	int16_t _y0,
	uint8_t _size,
	uint8_t _color
){
	// Check coordinates
	if ((_x0 < 0) || (_y0 < 0)
		|| (_x0 + _size * FONT_WIDTH >= this->params.width)
		|| (_y0 + _size * FONT_HEIGHT >= this->params.height)
	){

		Serial.println(F("drawChar(): invalid coordinates"));
		return 1;
	}

	// Check symbol (what library to use)
	uint8_t t = (uint8_t)_char;
	uint8_t *tmp_buf;

	// NUMBERS_ASCII
	if ((t >= 48) && (t <= 57)) {
		if (this->libNumbersAscii == NULL){
			Serial.println(F("drawChar(): LIB_NUMBERS_ASCII not set"));
			return 1;
		}
		tmp_buf = this->libNumbersAscii->getBitMap(_char);
	}

	// LETTERS_ASCII
	else if (((t >= 65) && (t <= 90))
		||	 ((t >= 97) && (t <= 122))
	){

		if (this->libLettersAscii == NULL){
			Serial.println(F("drawChar(): LIB_LETTERS_ASCII not set"));
			return 1;
		}
		tmp_buf = this->libLettersAscii->getBitMap(_char);
	}

	// SYMBOLS_ASCII
	else if (((t >= 32) && (t <= 47))
		||  ((t >= 58) && (t <= 64))
		||  ((t >= 91) && (t <= 96))
		||  ((t >= 123) && (t <= 126))
	){

		if (this->libSymbolsAscii == NULL){
			Serial.println(F("drawChar(): LIB_SYMBOLS_ASCII not set"));
			return 1;
		}
		tmp_buf = this->libSymbolsAscii->getBitMap(_char);
	}

	// LETTERS_CYRILLIC
	else if ( (t >= 128) && (t <= 255) ) {
		if (this->libLettersCyrillic == NULL) {
			Serial.println(F("drawChar(): LIB_LETTERS_CYRILLIC not set"));
			return 1;
		} else {
			if ( ((t <= 191) && (this->encoding == ENCODING_UTF8))
			  || ((t >= 192) && (this->encoding == ENCODING_CP1251))
			)
				tmp_buf = this->libLettersCyrillic->getBitMap(_char, encoding);
			else {
				Serial.println(F("drawChar(): encoding error"));
				return 1;
			}
		}
	}

	// unknown
	else {
		Serial.println(F("drawChar(): unknown symbol"));
		return;
	}

	for (uint8_t i = 0; i < FONT_WIDTH; i++) {
		uint8_t tmp_char = pgm_read_byte_near(tmp_buf + i);
		for (uint8_t j = 0; j < FONT_HEIGHT; j++)
			if (tmp_char & (1 << j)){
				uint8_t t1 = this->fillRect(
					_x0 + i*_size,
					_y0 + j*_size,
					_size,
					_size,
					_color
				);
			}
	}
	return 0;
}

/**************************************************************************/
/*!
	@brief	Print a string
	@param	_str			String to be printed
	@param	_x0				X coordinate of top left corner of string
	@param	_y0				Y coordinate of top left corner of string
	@param	_interval		Number of pixels between symbols
	@param	_size			Size of symbols in string
	@param	_color  		Color of symbols in string
	@return	Status byte
	@note	Symbols have 5x8 resolution (if size == 1). If size is 2, then
			resolution is 10x16 and so on.
*/
/**************************************************************************/
uint8_t GeeGrow_SSD1306_128_32::printStr(
	String _str,
	int16_t _x0,
	int16_t _y0,
	uint8_t _interval,
	uint8_t _size,
	uint8_t _color
){
	uint16_t n = _str.length();
	uint8_t missed_bytes = 0;
	// Divide string to separate symbols
	for (uint16_t i = 0; i < n; i++) {
		uint8_t t = (uint8_t)*(_str.c_str() + i);
		if (t == 208 || t == 209) {		// Extra bytes from utf-8, don't need them
			missed_bytes++;
			continue;
		}
		uint8_t t0 = this->printChar(
			(char)t,
			_x0 + (i - missed_bytes)*_size*FONT_WIDTH + i*_interval,
			_y0,
			_size,
			_color
		);
	}
	return 0;
}

/**************************************************************************/
/*!
	@brief	Set encoding of cyrillic symbols
	@param	_encoding	Encoding value
	@note	Influences only cyrillic symbols
*/
/**************************************************************************/
void GeeGrow_SSD1306_128_32::setEncoding(uint8_t _encoding){
	if (this->libLettersCyrillic == NULL) {
		Serial.println(F("setEncoding(): LIB_LETTERS_CYRILLIC not set"));
		return;
	}
	this->encoding = _encoding;
}

/**************************************************************************/
/*!
	@brief	Get current encoding of cyrillic symbols
	@return	Current value of encoding
	@note	Influences only cyrillic symbols
*/
/**************************************************************************/
uint8_t GeeGrow_SSD1306_128_32::getEncoding(){
	if (this->libLettersCyrillic == NULL) {
		Serial.println(F("getEncoding(): LIB_LETTERS_CYRILLIC not set"));
		return -1;
	}
	return this->encoding;
}
