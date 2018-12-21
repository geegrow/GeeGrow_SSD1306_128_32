/*!
 * @file GeeGrow_SSD1306_128x32.h
 *
 * This is a library for the GeeGrow SSD1306 128x32 display
 * https://geegrow.ru
 *
 * @section author Author
 * Written by Anton Pomazanov
 *
 * @section license License
 * BSD license, all text here must be included in any redistribution.
 *
 */

#ifndef _GEEGROW_SSD1306_128x32_H_
#define _GEEGROW_SSD1306_128x32_H_

#include <Wire.h>
#include <GeeGrow_SSD1306_tools.h>
#include <libFonts/GeeGrow_SSD1306_libLettersAscii.h>
#include <libFonts/GeeGrow_SSD1306_libNumbersAscii.h>
#include <libFonts/GeeGrow_SSD1306_libSymbolsAscii.h>
#include <libFonts/GeeGrow_SSD1306_libLettersCyrillic.h>

/**************************************************************************/
/*!
    @brief    Class that stores state and functions for interacting with SSD1306
              display
*/
/**************************************************************************/
class GeeGrow_SSD1306_128x32 {
    public:
        GeeGrow_SSD1306_128x32();
        ~GeeGrow_SSD1306_128x32(){}
        void initialize();
        void attachLibs(uint8_t _libs);
        void refresh();
        void fillDisplay(uint8_t _color);
        void setBrightness(uint8_t _brightness);
        void setRotation(uint8_t _rotation);
        void startScrollRight(uint8_t _start, uint8_t _stop);
        void startScrollLeft(uint8_t _start, uint8_t _stop);
        void startScrollDiagRight(uint8_t _start, uint8_t _stop);
        void startScrollDiagLeft(uint8_t _start, uint8_t _stop);
        void stopScroll();
        int16_t getHeight();
        int16_t getWidth();
        uint8_t getRotation();
        uint8_t drawPixel(int16_t _x0, int16_t _y0, uint8_t _color);
        uint8_t drawLine(
            int16_t _x0,
            int16_t _y0,
            int16_t _x1,
            int16_t _y1,
            uint8_t _color
        );
        uint8_t drawRect(
            int16_t _x0,
            int16_t _y0,
            int16_t _width,
            int16_t _height,
            uint8_t _color
        );
        uint8_t fillRect(
            int16_t _x0,
            int16_t _y0,
            int16_t _width,
            int16_t _height,
            uint8_t _color
        );
        uint8_t drawCircle(int16_t _x0, int16_t _y0, int16_t _radius, uint8_t _color);
        uint8_t fillCircle(int16_t _x0, int16_t _y0, int16_t _radius, uint8_t _color);
        uint8_t drawTriangle(
            int16_t _x0,
            int16_t _y0,
            int16_t _x1,
            int16_t _y1,
            int16_t _x2,
            int16_t _y2,
            uint8_t _color
        );
        uint8_t drawBitmap(
            uint8_t* _map,
            int16_t _x0,
            int16_t _y0,
            int16_t _width,
            int16_t _height,
            uint8_t _color
        );
        uint8_t printChar(
            char _char,
            int16_t _x0,
            int16_t _y0,
            uint8_t _size,
            uint8_t _color
        );
        uint8_t printStr(
            String _str,
            int16_t _x0,
            int16_t _y0,
            uint8_t _interval,
            uint8_t _size,
            uint8_t _color
        );
        void setEncoding(uint8_t _encoding);
        uint8_t getEncoding();

    protected:
        void ssd1306_command(uint8_t _cmd);
        params_t params = 0;
        int8_t encoding = 0;
        GeeGrow_SSD1306_libNumbersAscii *libNumbersAscii = nullptr;
        GeeGrow_SSD1306_libLettersAscii *libLettersAscii = nullptr;
        GeeGrow_SSD1306_libSymbolsAscii *libSymbolsAscii = nullptr;
        GeeGrow_SSD1306_libLettersCyrillic *libLettersCyrillic = nullptr;
        uint8_t buffer[LCD_HEIGHT * LCD_WIDTH / 8];
};

#endif /* _GEEGROW_SSD1306_128x32_H_ */
