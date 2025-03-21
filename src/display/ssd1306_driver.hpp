/*Copyright 2025 - HaruYou27

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/

#ifndef SSD1306_DRIVER_HPP
#define SSD1306_DRIVER_HPP

#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include <ctype.h>
#include <string.h>
#include <algorithm>

#include "font/MoonBench5x8Variable.h"

class SSD1306
{
private:	
	enum HEADER 
	{
		CONTROL_COMMAND = 0x00,
		CONTROL_DATA    = 0x40,
	};
	enum COMMAND
	{
		SET_CONTRAST = 0x81,
		SET_MEMORY_MODE = 0x20,
		DISPLAY_ALL_ON_RESUME = 0xA4,
		DISPLAY_ALL_ON = 0xA5,
		NORMAL_DISPLAY = 0xA6,
		INVERT_DISPLAY = 0xA7,
		DISPLAY_OFF = 0xAE,
		DISPLAY_ON = 0xAF,
		SET_DISPLAY_OFFSET = 0xD3,
		SET_COM_PINS = 0xDA,
		SETVCOMDETECT = 0xDB,
		SET_DISPLAY_CLOCK_DIV = 0xD5,
		SET_PRECHARGE = 0xD9,
		SET_MULTIPLEX = 0xA8,
		SETLOWCOLUMN = 0x00,
		SETHIGHCOLUMN = 0x10,
		SETSTARTLINE = 0x40,
		COLUMNADDR = 0x21,
		PAGEADDR   = 0x22,
		COMSCANINC = 0xC0,
		COMSCANDEC = 0xC8,
		SEGREMAP = 0xA0,
		CHARGEPUMP = 0x8D,
		SWITCHCAPVCC = 0x2,
		NOP = 0xE3,
	};
	enum SPECIFICATION
	{
		SLAVE_ADDRESS = 0x3C,
		SCREEN_WIDTH = 128,
		SCREEN_HEIGHT = 64,
		PAGE_SIZE = 8,
		MAX_BUFFER_SIZE = SCREEN_WIDTH * SCREEN_HEIGHT / PAGE_SIZE + 1,
		BAUDRATE = 100 * 1000,
	};
    i2c_inst_t *i2c;

    ~SSD1306();

	int set_write_position(uint8_t x, uint8_t y);
	int print_text(const char *text, size_t size, bool invert);
public:
	static constexpr int ROW_COUNT = SCREEN_HEIGHT / PAGE_SIZE;
    void operator=(const SSD1306 &) = delete;
    SSD1306(const SSD1306 &copy) = delete;
    SSD1306(const uint sda, const uint scl, i2c_inst_t *instance_i2c);

	int set_contrast(uint8_t value);
	int display_on();
	int display_off();
    
	int clear_screen();
	int i2c_write(const uint8_t* buffer, const int length);

	int print_overwrite(const char *text, bool invert = false);
	int print_line(const char *text, int line, bool invert = false);

	int draw_image_fullscreen(const uint8_t *data, int width, int page, bool invert = false);
};

#endif
