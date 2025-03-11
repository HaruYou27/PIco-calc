/*Copyright 2025 - HaruYou27

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/


#include "ssd1306_driver.hpp"

SSD1306::~SSD1306() {}

using namespace std;

void SSD1306::clear_screen()
{
	for (uint8_t y = 0; y < SCREEN_HEIGHT; y += SSD1306_PAGE_HEIGHT)
	{
		for (uint8_t x = 0; x < SCREEN_WIDTH; x++)
		{
			set_write_position(x, y);
			send_data(0);
		}
	}
}

// Minimize i2c write.
void SSD1306::clear_text()
{
	uint8_t end_x = text_x / (FONT_WIDTH+1);
	uint8_t end_y = text_y;
	uint8_t row = text_y / (FONT_HEIGHT+1);
	text_x = 0;
	text_y = 0;

	if (row-- == 0)
	{
		return;
	}

	for (uint8_t y = 0; y < row; y++)
	{
		for (int x = 0; x < MAX_CHARACTER_PER_ROW; x++)
		{
			draw_char(' ');
		}
		draw_char('\n');
	}

	for (uint8_t x = 0; x < end_x; x++)
	{
		draw_char(' ');
	}

	text_x = 0;
	text_y = 0;
}

void SSD1306::draw_char(char character)
{
	if (character == '\n')
	{
		text_x = 0;
		text_y = (text_y >= SCREEN_HEIGHT-1-FONT_HEIGHT) ? SCREEN_HEIGHT : text_y + FONT_HEIGHT + 1;
		return;
	}

	for (uint8_t index = 0; index < FONT_WIDTH; index++)
	{
		set_write_position(text_x++, text_y);
		send_data(FONT_MOONBENCH3x5MONO[character-32][index]);
	}
	if (++text_x >= SCREEN_WIDTH)
	{
		text_x = SCREEN_WIDTH;
	}
}

int SSD1306::send_data(uint8_t data)
{
	uint8_t buffer[2];
	buffer[0] = CONTROL_DATA;
	buffer[1] = data;
	return i2c_write(buffer, 2);
}

void SSD1306::set_char_pos(uint8_t x, uint8_t y)
{
	text_x = x * (FONT_WIDTH+1);
	text_y = y * (FONT_HEIGHT+1);
	if (text_x > SCREEN_WIDTH)
	{
		text_x = SCREEN_WIDTH;
	}
	if (text_y > SCREEN_HEIGHT)
	{
		text_y = SCREEN_HEIGHT;
	}
}

int SSD1306::set_contrast(uint8_t value)
{
	send_command(SSD1306_SETCONTRAST);
	return send_command(value);
}

int SSD1306::set_write_position(uint8_t x, uint8_t y)
{
	send_command(0x10 | (uint8_t)(x >> 4)); /* higher column address */
	send_command(x & 0x0F);          /* lower column address */
	return send_command(0xB0 + (y / SSD1306_PAGE_HEIGHT));  /* row address */
}

int SSD1306::i2c_write(uint8_t* buffer, int length)
{
	return i2c_write_blocking(i2c, SSD1306_ADDRESS, buffer, length, false);
}

int SSD1306::send_command(uint8_t command)
{
	uint8_t buffer[2];
	buffer[0] = CONTROL_COMMAND;
	buffer[1] = command;
	return i2c_write(buffer, 2);
}

int SSD1306::print_text(std::string &text)
{
	for (auto &character : text)
	{
		draw_char(character);
	}
}

SSD1306::SSD1306(uint sda, uint scl, i2c_inst_t *instance_i2c)
{
    i2c = instance_i2c;
    i2c_init(i2c, BAUDRATE);
	gpio_set_function(sda, GPIO_FUNC_I2C);
	gpio_set_function(scl, GPIO_FUNC_I2C);
	gpio_pull_up(sda);
	gpio_pull_up(scl);

	/* init sequence */
	send_command(SSD1306_DISPLAYOFF);
	send_command(SSD1306_SETMULTIPLEX);
	send_command(0x3F);
	send_command(SSD1306_SETDISPLAYOFFSET);
	send_command(0);
	send_command(SSD1306_SETSTARTLINE | 0x00);
	send_command(SSD1306_SEGREMAP | 0x01);
	send_command(SSD1306_COMSCANDEC);
	send_command(SSD1306_SETCOMPINS);
	send_command(0x12);
	set_contrast(127);
	send_command(SSD1306_DISPLAYALLON_RESUME);
	send_command(SSD1306_NORMALDISPLAY);
	send_command(SSD1306_SETDISPLAYCLOCKDIV);
	send_command(0x80);
	send_command(SSD1306_CHARGEPUMP);
	send_command(0x14);
	send_command(SSD1306_MEMORYMODE);
	send_command(0x00);  // vertical addressing mode
	send_command(0x02);  /* column address = 2 */
	send_command(0x10);
	send_command(0x40);  /* display start line = 0 */
	send_command(0xB0);  /* page start = 0 */
	send_command(SSD1306_DISPLAYON);

	set_write_position(0, 0);
}