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
        singleton = new InputMethodEditor();
    }
    return singleton;
}

uint InputMethodEditor::keypad_init(void)
{
    for (int index = 0; index < 4; index++)
    {
        gpio_init(COLIMN_PINS[index]);
        gpio_init(ROW_PINS[index]);

        gpio_set_dir(COLIMN_PINS[index], false);
        gpio_set_dir(ROW_PINS[index], true);

        gpio_put(COLIMN_PINS[index], false);
        gpio_put(ROW_PINS[index], true);
    }
}

char InputMethodEditor::scan_keys(void)
{
    for (int row = 0; row < 4; row++)
    {
        gpio_put(ROW_PINS[row], true);
        sleep_ms(SleepDuration::SCAN);

        for (int column; column < 4; column++)
        {
            if(gpio_get(column))
            {
                while (gpio_get(column))
                {
                    // Only return key value when the key is relased.
                    sleep_ms(SleepDuration::SCAN);
                }

                gpio_put(ROW_PINS[row], false);
                return keys[row][column];
            }
        }
        gpio_put(ROW_PINS[row], false);
    }
    return 0;
}

void InputMethodEditor::reset()
{
    current_key = 0;
    press_count = 0;
    time_passed = 0;
}

char InputMethodEditor::get_char()
{
    if (press_count == 5)
    {
        press_count = 0;
    }

    char letter = LETTERS[current_key-46][press_count];
    return (upper_case) ? toupper(letter) : letter;
}

char InputMethodEditor::wait4input()
{
    char key = 0;
    while (key == 0)
    {
        key = scan_keys();
        
        if (time_passed > 300000 || (raw && can_sleep && key == '\b'))
        {
            // Emergency sleep !
            reset();
            renderer->toggle_display(false);
            gpio_put(ROW_PINS[0], true);

            while (gpio_get(COLIMN_PINS[3]))
            {
                sleep_ms(SleepDuration::EMERGENCY);
            }

            renderer->toggle_display(true);
            gpio_put(ROW_PINS[0], false);
        }

        time_passed += 40;
    }

    if (raw || iscntrl(key))
    {
        reset();
        return key;
    }

    if (letter_mode && current_key == 0)
    {
        ++press_count;
    }
    if (key == current_key)
    {
        ++press_count;
        return get_char();
    }
    current_key = key;
    press_count = 0;
    return get_char();
}