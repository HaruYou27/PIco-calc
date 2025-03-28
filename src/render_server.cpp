/*Copyright 2025 - HaruYou27

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/

#include "render_server.hpp"

using namespace std;

RenderServer::RenderServer()
{
    screen0 = new SSD1306(16, 17, i2c0);
    screen1 = new SSD1306(26, 27, i2c1);
}

RenderServer::~RenderServer() {}
RenderServer *RenderServer::singleton = nullptr;

RenderServer *RenderServer::get_singleton()
{
    if (singleton == nullptr)
    {
        
        singleton = new RenderServer();
    }
    return singleton;
}

int RenderServer::display_on()
{
    screen0->display_on();
    return screen1->display_on();
}

int RenderServer::display_off()
{
    screen0->display_off();
    return screen1->display_off();
}

uint RenderServer::get_contrast()
{
    return contrast;
}

int RenderServer::set_contrast(uint value)
{
    contrast = value;
    screen0->set_contrast(value);
    return screen1->set_contrast(value);
}

void RenderServer::print_menu(const char* const *menu, size_t size)
{
    print_line_inverted(menu[0], 0);
    for (uint index = 1; index < size; index++)
    {
        print_line(menu[index], index);
    }
}

int RenderServer::print_line(const char *text, uint line)
{
    if (line > SSD1306::ROW_COUNT)
    {
        return screen1->print_line(text, line - SSD1306::PAGE_SIZE);
    }
    return screen0->print_line(text, line);
}

int RenderServer::print_line_inverted(const char *text, uint line)
{
    if (line > SSD1306::ROW_COUNT)
    {
        return screen1->print_line_inverted(text, line - SSD1306::PAGE_SIZE);
    }
    return screen0->print_line_inverted(text, line);
}

void RenderServer::clear_screen()
{
    screen0->clear_screen();
    screen1->clear_screen();
}

// Return discard position.
void RenderServer::text_wrap(string &text)
{
    uint index = 0;
    while(true)
    {
        char character = text.at(index);

        if (isblank(character) || character == ':' || character == '.' || character == ',' || character == ';')
        {
            text[index] = '\n';
            continue;
        }

        if (isdigit(character) || ispunct(character))
        {
            text.insert(index, 1, '\n');
            continue;
        }

        while (isalpha(character))
        {
            character = text.at(--index);
        }
    }
}