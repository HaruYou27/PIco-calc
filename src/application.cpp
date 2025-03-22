/*Copyright 2025 - HaruYou27

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/

#include "application.hpp"

using namespace std;

Application::Application(size_t menu_size)
{
    renderer = RenderServer::get_singleton();
    ime = InputMethodEditor::get_singleton();
}

uint Application::page2index()
{
    return page * SSD1306::ROW_COUNT*2;
}

uint Application::line2index()
{
    return line + page2index();
}

uint Application::open_menu(const char* const *menu, size_t menu_size)
{
    size_t page_end = menu_size / SSD1306::ROW_COUNT*2;
    size_t line_end = menu_size - page_end * SSD1306::ROW_COUNT*2 - 1;
    
    renderer->print_menu(menu, menu_size);
    ime->raw = true;
    ime->can_sleep = true;

    while (true)
    {
        switch (ime->wait4input())
        {
            case '1':
                line = 0;
                page = page_end;
                renderer->print_menu(menu + page2index(), menu_size);
                break;
            case '2':
                set_line((line == 15 || (page == page_end && line == line_end)) ? 0 : line + 1, menu);
                break;
            case '3':
                if (page == page_end)
                {
                    break;
                }
                ++page;
                line = 0;
                renderer->print_menu(menu + page2index(), menu_size);
                break;
            case '4':
                if (line >= 8)
                {
                    set_line(line - 8, menu);
                }
                break;
            case '5':
                return line2index();
            case '6':
                if (line < 8)
                {
                    set_line((page == page_end) ? min(line + 8, line_end) : line + 8, menu);
                }
                break;
            case '7':
                page = 0;
                line = 0;
                renderer->print_menu(menu, menu_size);
                break;
            case '8':
                if (!line)
                {
                    set_line((page == page_end) ? line_end : 15, menu);
                    break;
                }
                set_line(line - 1, menu);
                break;
            case '9':
                if (!page)
                {
                    break;
                }
                --page;
                line = 0;
                renderer->print_menu(menu + page2index(), menu_size);
                break;
        }
    }
}   

void Application::set_line(uint8_t value, const char* const *menu)
{
    renderer->print_line(menu[line], line);
    renderer->print_line(menu[value], value, true);

    line = value;
}

uint8_t Application::get_line()
{
    return line;
}