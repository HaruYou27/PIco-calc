/*Copyright 2025 - HaruYou27

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/

#include "ereader.hpp"

// Return pointer at new line character or before exceed line width.
const char *eReader::get_line_end(const char *book)
{
    uint width = 0;
    const char *begin = book;
    while (*book && width < SSD1306::SCREEN_WIDTH)
    {
		switch (*book)
		{
			case '\n':
                if (begin == book)
                {
                    ++book;
                    continue;
                }
				return book;
			case ' ':
                width += 2;
                ++book;
			    continue;
		}
		if (!isgraph(*book))
		{
			++book;
			continue;
		}

		int character = *book - 33;
        width += strnlen((char*) MoonBench5x8Variable[character], MoonBench5x8Variable_width) + 1;
		++book;
    }
    while (isalpha(*book))
    {
        --book;
    }
    
    return book;
}


// Return pointer at new line character or before exceed line width.
const char *eReader::get_line_begin(const char *book, const char *begin)
{
    uint width = 0;
    const char *end = book;
    while (begin != book && width < SSD1306::SCREEN_WIDTH)
    {
		switch (*book)
		{
			case '\n':
                if (end == book)
                {
                    --book;
                    continue;
                }
				return book;
			case ' ':
                width += 2;
                --book;
			    continue;
		}
		if (!isgraph(*book))
		{
			--book;
			continue;
		}

		int character = *book - 33;
        width += strnlen((char*) MoonBench5x8Variable[character], MoonBench5x8Variable_width) + 1;
		--book;
    }
    while (isalpha(*book))
    {
        --book;
    }
    
    return book;
}

// Return a pointer at the end of page.
const char *eReader::draw_book(const char *book)
{
    for (uint line = 0; line < SSD1306::ROW_COUNT*2; line++)
    {
        const char *halt = get_line_end(book);
        if (halt == book)
        {
            return book;
        }
        renderer->print_line(book, line, halt);
        book = halt;
    }
    return book;
}

void eReader::get_book_size()
{
    uint index = multicore_fifo_pop_blocking();
    multicore_fifo_push_blocking(strlen(BOOK_DATA[index]));
}

void eReader::open_book(uint index)
{
    multicore_launch_core1(get_book_size);
    multicore_fifo_push_blocking(index);

    const char *begin = BOOK_DATA[index];
    const char *line = begin;
    const char *page_end = draw_book(begin);
    const char *end = begin;
    while (true)
    {
        switch (ime->wait4input())
        {
            case '\e':
                return multicore_reset_core1();
            case '1':
                if (end == begin)
                {
                    end += multicore_fifo_pop_blocking();
                }
                break;
            case '2':
                line = get_line_end(line);
                page_end = draw_book(line);
                break;
            case '3':
                page_end = draw_book(page_end);
                break;
            case '7':
                page_end = draw_book(begin);
                break;
            case '8':
                break;
            case '9':
                break;
        }
    }
}

int eReader::main()
{
    while (true)
    {
        uint index = open_menu(BOOK_TITLE, BOOKS);
        if (index >= BOOKS)
        {
            return 0;
        }
        open_book(index);
    }
}