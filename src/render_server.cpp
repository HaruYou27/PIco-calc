/*Copyright 2025 - HaruYou27

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/

#include "render_server.hpp"

using namespace std;

RenderServer::RenderServer() {}
RenderServer *RenderServer::singleton = nullptr;

RenderServer *RenderServer::get_singleton()
{
    if (singleton == nullptr)
    {
        screen0 = new SSD1306(16, 17, i2c0);
        screen1 = new SSD1306(26, 27, i2c1);
        singleton = new RenderServer();
    }
    return singleton;
}

void RenderServer::print_menu(const char *title, const char *menu[])
{
    screen0->print_line(title, 0, true);
    screen0->print_line(menu[0], 1, true);

    uint8_t index = 1;
    while (menu[index] != NULL || index < 19)
    {
        if (index > 8)
        {
            screen1->print_line(menu[index], ++index);
            continue;
        }
        screen0->print_line(menu[index], ++index);
    }
}

void RenderServer::print_line(const char *text, uint8_t line, bool invert)
{
    if (line > 9)
    {
        screen1->print_line(text, line, invert);
        return;
    }
    screen0->print_line(text, line, invert);
}

void RenderServer::clear_text()
{
    screen0->clear_text();
    screen1->clear_text();
}

void RenderServer::clear_screen()
{
    screen0->clear_screen();
    screen1->clear_screen();
}

// Return discard position.
void RenderServer::text_wrap(string &text)
{
    if (text.length() <= SSD1306::MAX_CHARACTER_PER_LINE)
    {
        return;
    }

    int row = ceil(static_cast<float>(text.length() / SSD1306::MAX_CHARACTER_PER_LINE));
    if (row > SSD1306::MAX_ROW*2)
    {
        row = SSD1306::MAX_ROW*2;
    }

    int index = 0;
    for (int index_row = 1; index_row <= row; index_row++)
    {
        index += SSD1306::MAX_CHARACTER_PER_LINE;
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