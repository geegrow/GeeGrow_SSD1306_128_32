/*!
 * @file GeeGrow_SSD1306_128_32_I2Cimprvd.h
 *
 * This is a library for the GeeGrow SSD1306 128x32 display, which uses improved
   I2C library I2CTransport, which allows to use SPI inside interrupt handlers.
 * https://www.geegrow.ru
 *
 * @section author Author
 * Written by Anton Pomazanov
 *
 * @section license License
 * BSD license, all text here must be included in any redistribution.
 *
 */

#include "GeeGrow_SSD1306_128_32.h"
#include <I2CTransport.h>

/**************************************************************************/
/*!
	@brief  Class that stores state and functions for interacting with SSD1306 display,
			using I2CTransport library
*/
/**************************************************************************/
class GeeGrow_SSD1306_128_32_I2Cimprvd : public GeeGrow_SSD1306_128_32 {
	public:
		GeeGrow_SSD1306_128_32_I2Cimprvd();
		~GeeGrow_SSD1306_128_32_I2Cimprvd(){}
		void refresh(void);

	private:
		void ssd1306_command(uint8_t c);
};
