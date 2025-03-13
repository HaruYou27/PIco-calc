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
static constexpr unsigned char MoonBench4x8MONO[96][4] = {
	{0x00,0x00,0x00,0x00}, //  
	{0x00,0x5e,0x00,0x00}, // !
	{0x06,0x00,0x06,0x00}, // "
	{0x24,0x7e,0x24,0x00}, // #
	{0x2c,0x76,0x34,0x00}, // $
	{0x62,0x18,0x46,0x00}, // %
	{0x7c,0x52,0x6c,0x00}, // &
	{0x00,0x06,0x00,0x00}, // '
	{0x00,0x3c,0x42,0x00}, // (
	{0x42,0x3c,0x00,0x00}, // )
	{0x0a,0x04,0x0a,0x00}, // *
	{0x08,0x1c,0x08,0x00}, // +
	{0x00,0x60,0x00,0x00}, // ,
	{0x08,0x08,0x08,0x00}, // -
	{0x00,0x40,0x00,0x00}, // .
	{0x60,0x18,0x06,0x00}, // /
	{0x3c,0x42,0x3c,0x00}, // 0
	{0x44,0x7e,0x40,0x00}, // 1
	{0x72,0x4a,0x4c,0x00}, // 2
	{0x42,0x4a,0x34,0x00}, // 3
	{0x0e,0x08,0x7e,0x00}, // 4
	{0x46,0x4a,0x32,0x00}, // 5
	{0x7e,0x4a,0x7a,0x00}, // 6
	{0x02,0x72,0x0e,0x00}, // 7
	{0x76,0x4a,0x76,0x00}, // 8
	{0x4e,0x4a,0x7e,0x00}, // 9
	{0x00,0x24,0x00,0x00}, // :
	{0x40,0x28,0x00,0x00}, // ;
	{0x18,0x24,0x42,0x00}, // <
	{0x24,0x24,0x24,0x00}, // =
	{0x42,0x24,0x18,0x00}, // >
	{0x06,0x52,0x0e,0x00}, // ?
	{0x3c,0x4a,0x4c,0x00}, // @
	{0x7c,0x0a,0x7c,0x00}, // A
	{0x7e,0x4a,0x34,0x00}, // B
	{0x7e,0x42,0x66,0x00}, // C
	{0x7e,0x42,0x3c,0x00}, // D
	{0x7e,0x4a,0x42,0x00}, // E
	{0x7e,0x0a,0x02,0x00}, // F
	{0x7e,0x42,0x7a,0x00}, // G
	{0x7e,0x08,0x7e,0x00}, // H
	{0x42,0x7e,0x42,0x00}, // I
	{0x30,0x40,0x3e,0x00}, // J
	{0x7e,0x08,0x76,0x00}, // K
	{0x7e,0x40,0x40,0x00}, // L
	{0x7e,0x06,0x7e,0x00}, // M
	{0x7e,0x02,0x7e,0x00}, // N
	{0x7e,0x42,0x7e,0x00}, // O
	{0x7e,0x0a,0x06,0x00}, // P
	{0x1e,0x22,0x7e,0x00}, // Q
	{0x7e,0x0a,0x74,0x00}, // R
	{0x66,0x4a,0x72,0x00}, // S
	{0x02,0x7e,0x02,0x00}, // T
	{0x7e,0x40,0x7e,0x00}, // U
	{0x3e,0x40,0x3e,0x00}, // V
	{0x7e,0x60,0x7e,0x00}, // W
	{0x76,0x08,0x76,0x00}, // X
	{0x06,0x78,0x06,0x00}, // Y
	{0x72,0x4a,0x46,0x00}, // Z
	{0x7f,0x41,0x00,0x00}, // [
	{0x06,0x18,0x60,0x00}, // "\"
	{0x00,0x41,0x7f,0x00}, // ]
	{0x00,0x04,0x02,0x04}, // ^
	{0x00,0x40,0x40,0x40}, // _
	{0x00,0x02,0x04,0x00}, // `
	{0x00,0x70,0x54,0x7c}, // a
	{0x00,0x7c,0x48,0x30}, // b
	{0x00,0x38,0x44,0x00}, // c
	{0x00,0x30,0x48,0x7c}, // d
	{0x00,0x38,0x54,0x48}, // e
	{0x00,0x78,0x14,0x04}, // f
	{0x00,0x58,0x54,0x7c}, // g
	{0x00,0x7e,0x08,0x70}, // h
	{0x00,0x00,0x74,0x00}, // i
	{0x00,0x20,0x40,0x34}, // j
	{0x00,0x7c,0x10,0x68}, // k
	{0x00,0x7c,0x40,0x00}, // l
	{0x00,0x7c,0x0c,0x7c}, // m
	{0x00,0x7c,0x04,0x78}, // n
	{0x00,0x7c,0x44,0x7c}, // o
	{0x00,0x7c,0x14,0x08}, // p
	{0x00,0x08,0x14,0x7c}, // q
	{0x00,0x7c,0x04,0x08}, // r
	{0x00,0x58,0x54,0x34}, // s
	{0x00,0x08,0x7c,0x08}, // t
	{0x00,0x7c,0x40,0x7c}, // u
	{0x00,0x3c,0x40,0x3c}, // v
	{0x00,0x7c,0x60,0x7c}, // w
	{0x00,0x6c,0x10,0x6c}, // x
	{0x00,0x5c,0x50,0x7c}, // y
	{0x00,0x64,0x54,0x4c}, // z
	{0x00,0x08,0x7f,0x41}, // {
	{0x00,0x00,0x7f,0x00}, // |
	{0x00,0x41,0x7f,0x08}, // }
	{0x00,0x02,0x04,0x06}, // ~
	{0x00,0x00,0x00,0x00}
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
    static constexpr uint8_t SCREEN_WIDTH = 128;
    static constexpr uint8_t SCREEN_HEIGHT = 64;
    static constexpr uint8_t BAUDRATE = 4000000;

	static constexpr uint8_t FONT_WIDTH = 4;
	static constexpr uint8_t FONT_HEIGHT = 8;

    i2c_inst_t *i2c;
    uint8_t text_x = 0;
	uint8_t text_y = 0;

	static constexpr int BUFFER_SIZE = FONT_HEIGHT * SCREEN_WIDTH + 1;
	uint8_t buffer[BUFFER_SIZE] = {0};

    ~SSD1306();

	int i2c_write(uint8_t* buffer, const int length);
    int send_command(uint8_t command);
	int send_data(uint8_t data);

	int set_write_position(uint8_t x, uint8_t y);
	void print_append_blanks(bool invert = false);
public:
    void operator=(const SSD1306 &) = delete;
    SSD1306(const SSD1306 &copy) = delete;
    SSD1306(const uint sda, const uint scl, i2c_inst_t *instance_i2c);

	static constexpr int MAX_CHARACTER_PER_ROW = SCREEN_WIDTH / (FONT_WIDTH);
	static constexpr int MAX_ROW = SCREEN_HEIGHT / (FONT_HEIGHT);

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