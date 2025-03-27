/*Copyright 2025 - HaruYou27

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/

#include "ssd1306_driver.hpp"

SSD1306::~SSD1306() {}

using namespace std;

int SSD1306::clear_screen()
{
	set_page(0);
	
	uint8_t *buffer = new uint8_t[MAX_BUFFER_SIZE] {CONTROL_DATA};
	int error = i2c_write(buffer, MAX_BUFFER_SIZE);
	delete[] buffer;
	return error;
}

int SSD1306::draw_image_fullscreen(const uint8_t *data, int width, int pages)
{
	if (width == SCREEN_WIDTH)
	{
		size_t size = width * pages;

		i2c_write(&CONTROL_DATA, 1, true);
		return i2c_write(data, size);
	}

	uint8_t *buffer = new uint8_t[MAX_BUFFER_SIZE] {CONTROL_DATA};
	uint8_t *begin = buffer;
	int offset = (SCREEN_WIDTH - width) / 2 + 1;
	for (int page = 1; page <= pages; page++)
	{
		uint8_t *end = buffer + SCREEN_WIDTH;
		buffer += offset;

		memcpy(buffer, data, width);
		data += width;
		buffer = end;
	}
	int error = i2c_write(begin, MAX_BUFFER_SIZE);
	delete[] begin;
	return error;
}

int SSD1306::display_on()
{
	static constexpr uint8_t buffer[2] =
	{
		CONTROL_COMMAND,
		DISPLAY_ON
	};
	return i2c_write(buffer, 2);
}

int SSD1306::display_off()
{
	static constexpr uint8_t buffer[2] =
	{
		CONTROL_COMMAND,
		DISPLAY_OFF
	};
	return i2c_write(buffer, 2);
}

int SSD1306::set_contrast(uint8_t value)
{
	uint8_t buffer[3] = 
	{
		CONTROL_COMMAND,
		SET_CONTRAST,
		value,
	};
	return i2c_write(buffer, 3);
}

int SSD1306::set_page(uint8_t page)
{
	uint8_t buffer[4] = 
	{
		CONTROL_COMMAND,
		0x10 | 0, // higher column address
		0 & 0x0F, // lower column address
		static_cast<uint8_t>(0xB0 + page), // row address
	};
	return i2c_write(buffer, 4);
}
// Return number of bytes written, or PICO_ERROR_GENERIC if address not acknowledged, no device present.
int SSD1306::i2c_write(const uint8_t* buffer, int length, bool nostop)
{
	return i2c_write_blocking(i2c, SLAVE_ADDRESS, buffer, length, nostop);
}

// Same as draw_char but invert the font color.
void SSD1306::draw_char_inverted(uint8_t *buffer, char character)
{
	if (isblank(character))
	{
		fill(buffer, buffer + 4, 0xff);
		return;
	}
	const uint8_t *font_data = MoonBench[character - 33];
	for (int i = 0; i < MoonBench_width; i++)
	{
		*buffer = 0xff - font_data[i];
		++buffer;
	}
	*buffer = 0xff;
}

// Copy font data to buffer.
void SSD1306::draw_char(uint8_t *buffer, char character)
{
	if (isblank(character))
	{
		return;
	}
	memcpy(buffer,  MoonBench[character - 33], MoonBench_width);
}

// Clear the screen then print text.
int SSD1306::print(const char *text, const char *halt)
{
	set_page(0);
	size_t size = MAX_BUFFER_SIZE;
	uint8_t *buffer = new uint8_t[size] {CONTROL_DATA};

	uint index_page = SCREEN_WIDTH + 1;
	for (uint index = 1; index < size && text < halt; index += 4)
	{
		if (*text == '\n')
		{
			index = index_page;
			index_page += SCREEN_WIDTH;
			++text;
			continue;
		}
		if (!isprint(*text))
		{
			++text;
			continue;
		}
		draw_char(buffer + index, *text);
		++text;
	}

	int error = i2c_write(buffer, size);
	delete[] buffer;
	return error;
}

// Same as print_line() but invert the font color.
int SSD1306::print_line_inverted(const char *text, uint line)
{
	size_t size = SCREEN_WIDTH + 1;
	uint8_t *buffer = new uint8_t[size] {CONTROL_DATA};

	for (uint index = 1; index < size && isprint(*text); index += 4)
	{
		draw_char_inverted(buffer + index, *text);
		++text;
	}

	int error = i2c_write(buffer, size);
	delete[] buffer;
	return error;
}

// Print and overwrite a specific line. Stop at line end or null terminator.
int SSD1306::print_line(const char *text, uint line)
{
	set_page(line);
	size_t size = SCREEN_WIDTH + 1;
	uint8_t *buffer = new uint8_t[size] {CONTROL_DATA};

	for (uint index = 1; index < size && isprint(*text); index += 4)
	{
		draw_char(buffer + index, *text);
		++text;
	}

	int error = i2c_write(buffer, size);
	delete[] buffer;
	return error;
}

SSD1306::SSD1306(uint sda, uint scl, i2c_inst_t *instance_i2c)
{
    i2c = instance_i2c;
    i2c_init(i2c, BAUDRATE);
	gpio_set_function(sda, GPIO_FUNC_I2C);
	gpio_set_function(scl, GPIO_FUNC_I2C);
	gpio_pull_up(sda);
	gpio_pull_up(scl);

	// init sequence based on https://github.com/adafruit/Adafruit_SSD1306
	static constexpr uint8_t buffer[] = {
		CONTROL_COMMAND,
		DISPLAY_OFF,
		SET_DISPLAY_CLOCK_DIV, 0x80,
		SET_MULTIPLEX, 0x3F,
		SET_DISPLAY_OFFSET, 0,
		SETSTARTLINE | 0,
		CHARGEPUMP, 0x14,
		SEGREMAP | 0x01,
		COMSCANDEC,
		SET_COM_PINS, 0x12,
		SET_PRECHARGE, 0xF1,
		SETVCOMDETECT, 0x40,
		DISPLAY_ALL_ON_RESUME,
		NORMAL_DISPLAY,
		SET_MEMORY_MODE,
		0, // Vertical addressing mode
		2, // column address = 2
		0x10,
		0x40, // display start line = 0
		0xB0, // page start = 0
		DISPLAY_ON
	};
	i2c_write(buffer, 28);
}