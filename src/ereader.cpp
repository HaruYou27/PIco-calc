/*Copyright 2025 - HaruYou27

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/

#include "ereader.hpp"

// Increment the pointer, stop after new line character or null terminator.
const char *eReader::read_line_down(const char *book)
{
    while (*book && *book != '\n')
    {
		++book;
    }
    return ++book;
}

// read_line_down() * 8
const char *eReader::read_page_down(const char *book)
{
    for (uint line = 0; line < SSD1306::ROW_COUNT && *book; line++)
    {
        book = read_line_down(book);
    }
    return book;
}

// Decrement the pointer, stop after new line character or begin pointer.
const char *eReader::read_line_up(const char *book, const char *begin)
{
    while (book > begin && *book != '\n')
    {
        --book;
    }
    return ++book;
}

// read_line_up() * 8
const char *eReader::read_page_up(const char *book, const char *begin)
{
    for (uint line = 0; line < SSD1306::ROW_COUNT && begin < book; line++)
    {
        book = read_line_up(book, begin);
    }
    return book;
}

const char *eReader::draw_page_up(const char *book, const char *begin)
{
    const char *start = read_page_up(book, begin);
    renderer->screen0->print(start, book);

    book = start;
    start = read_page_up(book, begin);
    renderer->screen1->print(start, book);
    return start;
}

void eReader::get_book_end()
{
    const char *book = BOOK_DATA[multicore_fifo_pop_blocking()];
    multicore_fifo_push_blocking(strlen(book));
}

// Return a pointer at the end of page.
const char *eReader::draw_page_down(const char *book)
{
    const char *end = read_page_down(book);
    renderer->screen0->print(book, end);

    book = end;
    end = read_page_down(book);
    renderer->screen1->print(book, end);
    return end;
}

void eReader::open_book(uint index)
{
    multicore_launch_core1(get_book_end);
    multicore_fifo_push_blocking(index);

    const char *begin = BOOK_DATA[index];
    const char *book = draw_page_down(begin);
    const char *end = nullptr;
    
    while (true)
    {
        switch (ime->wait4input())
        {
            case '\e':
                return multicore_reset_core1();
            case '1':
                if (end == nullptr)
                {
                    end = begin + multicore_fifo_pop_blocking();
                }
                if (book == end)
                {
                    continue;
                }
                book = end;
                draw_page_up(end, begin);
                continue;
            case '2':
                if (book == end)
                {
                    continue;
                }
                book = read_line_down(book);
                draw_page_down(book);
                continue;
            case '3':
                if (book == end)
                {
                    continue;
                }
                book = read_page_down(book);
                continue;
            case '7':
                if (book == begin)
                {
                    continue;
                }
                book = begin;
                draw_page_down(begin);
                continue;
            case '8':
                if (book == begin)
                {
                    continue;
                }
                book = read_line_up(book, begin);
                draw_page_up(book, begin);
                continue;
            case '9':
                if (book == begin)
                {
                    continue;
                }
                book = draw_page_up(book, begin);
                continue;
            default:
                continue;
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