/*Copyright 2025 - HaruYou27

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/

#ifndef SSD1306_DRIVER_HPP
#define SSD1306_DRIVER_HPP

#include "pico/stdlib.h"
#include "hardware/i2c.h"

class SSD1306
{
private:
    static constexpr unsigned char FONT_MOONBENCH3x5MONO[96][3] = 
    {
    	{0x00,0x00,0x00}, //  
    	{0x00,0xb8,0x00}, // !
    	{0x18,0x00,0x18}, // "
    	{0x50,0xf8,0x50}, // #
    	{0xa0,0xf8,0xa8}, // $
    	{0x48,0x20,0x90}, // %
    	{0xf0,0xa8,0xd0}, // &
    	{0x00,0x18,0x00}, // '
    	{0x00,0x70,0x88}, // (
    	{0x88,0x70,0x00}, // )
    	{0x28,0x10,0x28}, // *
    	{0x20,0x70,0x20}, // +
    	{0xc0,0x00,0x00}, // ,
    	{0x20,0x20,0x20}, // -
    	{0x80,0x00,0x00}, // .
    	{0xc0,0x30,0x08}, // /
    	{0x70,0x88,0x70}, // 0
    	{0x88,0xf8,0x80}, // 1
    	{0xe8,0xa8,0xb8}, // 2
    	{0x88,0xa8,0xf8}, // 3
    	{0x38,0x20,0xf8}, // 4
    	{0xb8,0xa8,0xe8}, // 5
    	{0xf8,0xa8,0xe8}, // 6
    	{0x08,0xc8,0x38}, // 7
    	{0xf8,0xa8,0xf8}, // 8
    	{0x38,0x28,0xf8}, // 9
    	{0x00,0x50,0x00}, // :
    	{0x80,0x50,0x00}, // ;
    	{0x20,0x50,0x88}, // <
    	{0x50,0x50,0x50}, // =
    	{0x88,0x50,0x20}, // >
    	{0x08,0xa8,0x38}, // ?
    	{0xf8,0xa8,0xb8}, // @
    	{0xf8,0x28,0xf8}, // A
    	{0xf8,0xa8,0x70}, // B
    	{0xf8,0x88,0x88}, // C
    	{0xf8,0x88,0xf0}, // D
    	{0xf8,0xa8,0x88}, // E
    	{0xf8,0x28,0x08}, // F
    	{0xf8,0x88,0xc8}, // G
    	{0xf8,0x20,0xf8}, // H
    	{0x88,0xf8,0x88}, // I
    	{0xc0,0x88,0xf8}, // J
    	{0xf8,0x20,0xd8}, // K
    	{0xf8,0x80,0x80}, // L
    	{0xf8,0x18,0xf8}, // M
    	{0xf8,0x08,0xf8}, // N
    	{0xf8,0x88,0xf8}, // O
    	{0xf8,0x28,0x38}, // P
    	{0x78,0x48,0xf8}, // Q
    	{0xf8,0x28,0xd8}, // R
    	{0xb0,0xa8,0x68}, // S
    	{0x08,0xf8,0x08}, // T
    	{0xf8,0x80,0xf8}, // U
    	{0x78,0x80,0x78}, // V
    	{0xf8,0xc0,0xf8}, // W
    	{0xd8,0x20,0xd8}, // X
    	{0x18,0xe0,0x18}, // Y
    	{0xc8,0xa8,0x98}, // Z
    	{0xf8,0x88,0x00}, // [
    	{0x08,0x30,0xc0}, // "\"
    	{0x00,0x88,0xf8}, // ]
    	{0x00,0x10,0x08}, // ^
    	{0x00,0x80,0x80}, // _
    	{0x00,0x08,0x10}, // `
    	{0x00,0xe0,0x50}, // a
    	{0x00,0xf8,0xa0}, // b
    	{0x00,0xe0,0xa0}, // c
    	{0x00,0xc0,0xa0}, // d
    	{0x00,0x60,0xd0}, // e
    	{0x00,0xf0,0x48}, // f
    	{0x00,0xb0,0xa8}, // g
    	{0x00,0xf8,0x20}, // h
    	{0x00,0x00,0xd0}, // i
    	{0x00,0x80,0xd0}, // j
    	{0x00,0xf8,0x20}, // k
    	{0x00,0xf0,0x80}, // l
    	{0x00,0xe0,0x60}, // m
    	{0x00,0xe0,0x20}, // n
    	{0x00,0xe0,0xa0}, // o
    	{0x00,0xf0,0x50}, // p
    	{0x00,0x60,0x50}, // q
    	{0x00,0xe0,0x20}, // r
    	{0x00,0xa0,0xf0}, // s
    	{0x00,0x10,0xf8}, // t
    	{0x00,0xe0,0x80}, // u
    	{0x00,0x60,0x80}, // v
    	{0x00,0xe0,0xc0}, // w
    	{0x00,0xa0,0x40}, // x
    	{0x00,0x20,0xc0}, // y
    	{0x00,0xd0,0xb0}, // z
    	{0x00,0x20,0xf8}, // {
    	{0x00,0x00,0xd8}, // |
    	{0x00,0x88,0xf8}, // }
    	{0x00,0x10,0x20}, // ~
    	{0x00,0x00,0x00}
    };

    static constexpr uint8_t CONTROL_COMMAND = 0x00;
    static constexpr uint8_t CONTROL_DATA    = 0x40;

    static constexpr uint8_t SSD1306_SETCONTRAST = 0x81;
    static constexpr uint8_t SSD1306_DISPLAYALLON_RESUME = 0xA4;
    static constexpr uint8_t SSD1306_DISPLAYALLON = 0xA5;
    static constexpr uint8_t SSD1306_NORMALDISPLAY = 0xA6;
    static constexpr uint8_t SSD1306_INVERTDISPLAY = 0xA7;
    static constexpr uint8_t SSD1306_DISPLAYOFF = 0xAE;
    static constexpr uint8_t SSD1306_DISPLAYON = 0xAF;
    static constexpr uint8_t SSD1306_SETDISPLAYOFFSET = 0xD3;
    static constexpr uint8_t SSD1306_SETCOMPINS = 0xDA;
    static constexpr uint8_t SSD1306_SETVCOMDETECT = 0xDB;
    static constexpr uint8_t SSD1306_SETDISPLAYCLOCKDIV = 0xD5;
    static constexpr uint8_t SSD1306_SETPRECHARGE = 0xD9;
    static constexpr uint8_t SSD1306_SETMULTIPLEX = 0xA8;
    static constexpr uint8_t SSD1306_SETLOWCOLUMN = 0x00;
    static constexpr uint8_t SSD1306_SETHIGHCOLUMN = 0x10;
    static constexpr uint8_t SSD1306_SETSTARTLINE = 0x40;
    static constexpr uint8_t SSD1306_MEMORYMODE = 0x20;
    static constexpr uint8_t SSD1306_COLUMNADDR = 0x21;
    static constexpr uint8_t SSD1306_PAGEADDR   = 0x22;
    static constexpr uint8_t SSD1306_COMSCANINC = 0xC0;
    static constexpr uint8_t SSD1306_COMSCANDEC = 0xC8;
    static constexpr uint8_t SSD1306_SEGREMAP = 0xA0;
    static constexpr uint8_t SSD1306_CHARGEPUMP = 0x8D;
    static constexpr uint8_t SSD1306_SWITCHCAPVCC = 0x2;
    static constexpr uint8_t SSD1306_NOP = 0xE3;

    static constexpr uint8_t SSD1306_ADDRESS = 0x3C;
    static constexpr uint8_t SSD1306_PAGE_HEIGHT = 8;
    static constexpr uint8_t SCREEN_WIDTH = 128;
    static constexpr uint8_t SCREEN_HEIGHT = 64;
    static constexpr uint8_t BAUDRATE = 400000;

	static constexpr int FONT_WIDTH = 3;
	static constexpr uint8_t FONT_HEIGHT = 5;
	static constexpr uint8_t GLYPH_WIDTH = FONT_WIDTH + 1;
	static constexpr uint8_t GLYPH_HEIGHT = FONT_HEIGHT + 1;

    i2c_inst_t *i2c;
    uint8_t text_x = 0;
	uint8_t text_y = 0;

    ~SSD1306();

	int i2c_write(uint8_t* buffer, const int length);
    int send_command(uint8_t command);
	int send_data(uint8_t data);

	int set_write_position(uint8_t x, uint8_t y);
	void draw_blanks(int count, bool invert = false);
	void clear_text_until(int end_y, int end_x);
public:
    void operator=(const SSD1306 &) = delete;
    SSD1306(const SSD1306 &copy) = delete;
    SSD1306(const uint sda, const uint scl, i2c_inst_t *instance_i2c);

	static constexpr int MAX_CHARACTER_PER_ROW = SCREEN_WIDTH / (FONT_WIDTH+1);
	static constexpr int MAX_ROW = SCREEN_HEIGHT / (FONT_HEIGHT+1);

	int set_contrast(uint8_t value);
    
	void clear_screen();
	//void draw_image();

	void set_char_pos(uint8_t column, uint8_t line);
	void clear_text();
	void draw_char(char character, bool invert = false);

	void print_append(const char *text, bool invert = false);
	void print_overwrite(const char *text, bool invert = false);
	void print_line(const char *text, uint8_t line, bool invert = false);
};

#endif