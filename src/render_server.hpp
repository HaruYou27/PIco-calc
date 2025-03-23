/*Copyright 2025 - HaruYou27

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/

#ifndef RENDER_SERVER_HPP
#define RENDER_SERVER_HPP

#include <string>
#include <math.h>
#include <ctype.h>

#include "ssd1306_driver.hpp"

class RenderServer
{
private:
    static RenderServer *singleton;
    static constexpr int ROW_COUNT = 8;
    
    RenderServer();

    bool is_screen_on = false;
public:
    void operator=(const RenderServer &) = delete;
    RenderServer(const RenderServer &copy) = delete;
    static RenderServer *get_singleton();

    static SSD1306 *screen0;
    static SSD1306 *screen1;
    
    void clear_screen();

    void print_menu(const char* const *menu, size_t size);
    int print_line(const char *text, uint8_t line, bool invert = false);
    int print_line(const char *text, uint8_t line, const char *halt);

    int display_on();
    int display_off();

    static void text_wrap(std::string &text);
};

#endif