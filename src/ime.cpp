/*Copyright 2025 - HaruYou27

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/


#include "ime.hpp"

InputMethodEditor::InputMethodEditor() {}
InputMethodEditor *InputMethodEditor::singleton = nullptr;

InputMethodEditor *InputMethodEditor::get_singleton()
{
    if (singleton == nullptr)
    {
        for (int index = 0; index < 4; index++)
        {
            gpio_init(PIN_COLUMNS[index]);
            gpio_init(PIN_ROWs[index]);
        
            gpio_set_dir(PIN_COLUMNS[index], false);
            gpio_set_dir(PIN_ROWs[index], true);
        
            gpio_put(PIN_COLUMNS[index], false);
        }

        singleton = new InputMethodEditor();
    }
    renderer = RenderServer::get_singleton();
    return singleton;
}

char InputMethodEditor::scan_keys(void)
{
    for (uint row = 0; row < 4; row++)
    {
        gpio_put(PIN_ROWs[row], true);
        sleep_ms(SleepDuration::SCAN);

        for (uint column; column < 4; column++)
        {
            if(gpio_get(column))
            {
                while (gpio_get(column))
                {
                    // Only return key value when the key is relased.
                    sleep_ms(SleepDuration::SCAN);
                }

                gpio_put(PIN_ROWs[row], false);
                return keys[row][column];
            }
        }
        gpio_put(PIN_ROWs[row], false);
    }
    return 0;
}

void InputMethodEditor::reset()
{
    current_key = 0;
    press_count = (letter_mode) ? 1 : 0;
    time_passed = 0;
}

char InputMethodEditor::get_char()
{
    if (press_count == 5)
    {
        press_count = 0;
    }

    char letter = LETTERS[current_key-45][press_count];
    return (upper_case) ? toupper(letter) : letter;
}

char InputMethodEditor::wait4input()
{
    char key = 0;
    while (key == 0)
    {
        key = scan_keys();
        
        if (time_passed > 30*1000 || (raw && key == '\b'))
        {
            // Emergency sleep !
            reset();
            renderer->display_off();
            gpio_put(PIN_ROWs[0], true);

            while (gpio_get(PIN_COLUMNS[3]))
            {
                sleep_ms(SleepDuration::EMERGENCY);
            }

            renderer->display_on();
            gpio_put(PIN_ROWs[0], false);
        }

        time_passed += 16;
    }

    if (raw || iscntrl(key))
    {
        reset();
        return key;
    }

    if (key == current_key)
    {
        ++press_count;
        return get_char();
    }
    current_key = key;
    reset();
    return '\r';
}