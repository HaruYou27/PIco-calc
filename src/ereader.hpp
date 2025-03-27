/*Copyright 2025 - HaruYou27

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/

#ifndef E_READER_HPP
#define E_READER_HPP

#include "application.hpp"
#include "e_reader/book.h"

#include "pico/multicore.h"

class eReader : Application
{
private:
    void open_book(uint index);
    const char *draw_page_down(const char *book);
    const char *draw_page_up(const char *book, const char *begin);
    static void get_book_end();
public:
    static const char *read_line_down(const char *book);
    static const char *read_page_down(const char *book);
    static const char *read_line_up(const char *book, const char *begin);
    static const char *read_page_up(const char *book, const char *begin);

    virtual int main() override;
};
#endif
