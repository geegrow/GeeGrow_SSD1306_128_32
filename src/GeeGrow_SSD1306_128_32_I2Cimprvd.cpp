/*!
 * @file GeeGrow_SSD1306_128_32_I2Cimprvd.cpp
 *
 * This is a library for the GeeGrow SSD1306 128x32 display, which uses improved
   I2C library I2CTransport, which provides more stable workability
 * https://www.geegrow.ru
 *
 * @section author Author
 * Written by Anton Pomazanov
 *
 * @section license License
 * BSD license, all text here must be included in any redistribution.
 *
 */

#include "GeeGrow_SSD1306_128_32_I2Cimprvd.h"

/**************************************************************************/
/*!
    @brief  Instantiate GeeGrow SSD1306 driver for 128x32 display with
			using I2CTransporter library
*/
/**************************************************************************/
GeeGrow_SSD1306_128_32_I2Cimprvd::GeeGrow_SSD1306_128_32_I2Cimprvd() : GeeGrow_SSD1306_128_32() {

}

/**************************************************************************/
/*!
    @brief  Refresh image on the screen (copy data from buffer to display RAM)
			using I2CTransport library
	@note   Send data by portions of 16 bytes. TX_BUFFER size is 32 bytes (Wire.h),
			but we can't make portions of 32 bytes, as every packet contains
			1 control byte, so packet size will be 33.
*/
/**************************************************************************/
void GeeGrow_SSD1306_128_32_I2Cimprvd::refresh(void) {
	this->ssd1306_command(SSD1306_COLUMNADDR);
	this->ssd1306_command(0);
	this->ssd1306_command(LCD_WIDTH - 1);
	this->ssd1306_command(SSD1306_PAGEADDR);
	this->ssd1306_command(0);
	this->ssd1306_command(3);

	for (uint16_t i = 0; i < (LCD_WIDTH/8 * LCD_HEIGHT); i += 16) {
		I2CTransport::writeBytes(
			I2C_ADDRESS,
			0x40,	// Next bytes are data
			16,
			this->buffer + i
		);
	}
}

/**************************************************************************/
/*!
    @brief  Send command via I2C using I2CTransport library
	@param  _cmd  Command byte
*/
/**************************************************************************/
void GeeGrow_SSD1306_128_32_I2Cimprvd::ssd1306_command(uint8_t c) {
	I2CTransport::writeByte(
		I2C_ADDRESS,
		0x00,	// Co = 0, D/C = 0
		c,
		false
	);
}
