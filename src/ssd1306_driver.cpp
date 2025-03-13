/*Copyright 2025 - HaruYou27

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/


#include "ssd1306_driver.hpp"

SSD1306::~SSD1306() {}

using namespace std;

void SSD1306::clear_screen()
{
	write_x = 0;
	write_y = 0;
	set_write_position(0, 0);
	
	static constexpr int BUFFER_SIZE = SCREEN_WIDTH*MAX_ROW+1;
	static constexpr uint8_t BUFFER[BUFFER_SIZE] = {CONTROL_DATA};
	i2c_write(BUFFER, BUFFER_SIZE);
	
	set_write_position(0, 0);
}

void SSD1306::fill_font_data(char character, uint8_t *buffer, int &index, bool invert)
{
	int idx = character - 32;
	for (int i = 0; i < FONT_WIDTH; i++)
	{
		uint8_t line = MoonBench4x8MONO[idx][i];
		if (invert)
		{
			line = 0xff - line;
		}
		buffer[index++] = line;
	}
}

void SSD1306::fill_blank(size_t size)
{
	uint8_t *buffer = new uint8_t[size] {CONTROL_DATA};
	
	i2c_write(buffer, size);
	delete[] buffer;
}

// Less i2c write than clear_screen().
void SSD1306::clear_text()
{
	set_write_position(0, 0);
	fill_blank(write_y / FONT_HEIGHT * SCREEN_WIDTH + write_x + 1);

	write_x = 0;
	write_y = 0;
	set_write_position(0, 0);
}

// Draw a single char at position.
void SSD1306::draw_char(char character, bool invert)
{
	size_t size = FONT_WIDTH+1;
	uint8_t buffer[size];
	buffer[0] = CONTROL_DATA;

	int index = 1;
	fill_font_data(character, buffer, index, invert);

	i2c_write(buffer, size);
	write_x += FONT_WIDTH;
}

void SSD1306::set_char_pos(uint8_t column, uint8_t line)
{
	write_x = column * (FONT_WIDTH);
	write_y = line * (FONT_HEIGHT);

	if (write_x >= SCREEN_WIDTH)
	{
		write_x = 0;
	}
	if (write_y >= SCREEN_HEIGHT)
	{
		write_y = 0;
	}
	set_write_position(write_x, write_y);
}

int SSD1306::set_contrast(uint8_t value)
{
	send_command(SSD1306_SETCONTRAST);
	return send_command(value);
}

int SSD1306::set_write_position(uint8_t x, uint8_t y)
{
	send_command(0x10 | static_cast<uint8_t>(x >> 4)); /* higher column address */
	send_command(x & 0x0F);          /* lower column address */
	return send_command(0xB0 + (y / FONT_HEIGHT));  /* row address */
}

int SSD1306::i2c_write(const uint8_t* buffer, int length)
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

void SSD1306::print_line(const char *text, uint8_t line, bool invert)
{
	set_char_pos(0, line);

	size_t size = SCREEN_WIDTH + 1;
	uint8_t *buffer = new uint8_t[size] {CONTROL_DATA};

	int index = 1;
	while (index < size || *text)
	{
		fill_font_data(*text, buffer, index, invert);
		++text;
	}
	
	if (invert)
	{
		fill(buffer + index, buffer + size, 0xff);
	}
	
	i2c_write(buffer, size);
	delete[] buffer;
}

// Overwrite on screen text. Less i2c write than clear_text() then print_append()
void SSD1306::print_overwrite(const char *text, bool invert, uint8_t start_x, uint8_t start_y)
{
	int end_x = write_x;
	int end_y = write_y;
	write_x = start_x;
	write_y = start_y;
	set_write_position(start_x, start_y);

	print_append(text, invert);

	end_y -= static_cast<int>(write_y);
	if (end_y < 0)
	{
		return;
	}

	end_y = end_y / FONT_HEIGHT -1;
	size_t size = SCREEN_WIDTH - write_x + 1; // First line.
	if (end_y > -1)
	{
		size += end_x; // Last line.
		if (end_y > 0)
		{
			// Anything in between.
			size += end_y * SCREEN_WIDTH;
		}
	}
	fill_blank(size);

	set_write_position(write_x, write_y);
}

void SSD1306::print_append(const char *text, bool invert)
{
	const char *begin = text;
	int count_line = 0;
	write_x = 0;
	while (*text)
	{
		if (*text == '\n')
		{
			++count_line;
			write_x = 0;
		}
		++text;
		++write_x;
	}

	text = begin;
	write_x *= FONT_WIDTH;
	write_y += count_line * FONT_HEIGHT;
	size_t size = write_x + count_line * SCREEN_WIDTH + 1;
	uint8_t *buffer = new uint8_t[size] {CONTROL_DATA};

	int index = 1;
	count_line = 1;
	while (*text)
	{
		if (*text == '\n')
		{
			count_line += SCREEN_WIDTH;
			index = count_line;
			++text;
			continue;
		}

		fill_font_data(*text, buffer, index, invert);
		++text;
	}

	i2c_write(buffer, size);
	delete[] buffer;
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
	send_command(SSD1306_SETSTARTLINE | 0x00);
	send_command(SSD1306_SEGREMAP | 0x01);
	send_command(SSD1306_COMSCANDEC);
	send_command(SSD1306_SETCOMPINS);
	send_command(0x12);
	set_contrast(0xff);
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

	clear_screen();
}