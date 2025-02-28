/*Copyright 2025 - HaruYou27

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/

#ifndef InputMethodEditor_HPP
#define InputMethodEditor_HPP

#include <ctype.h>

#include "pico/stdlib.h"

class InputMethodEditor
{
private:
    const uint COLIMN_PINS[4] = 
    {};
    const uint ROW_PINS[4] = 
    {};

    enum SleepDuration 
    {
        SCAN = 10,
        EMERGENCY = 2727,
    };

    const char keys[4][4] = 
    {
        {'7', '8', '9', '\b'},
        {'4', '5', '6', '\r'},
        {'1', '2', '3', '\e'},
        {'0', '.', '/', '\f'},
    };

    const char LETTERS[12][5] = 
    {
        {'.', ',', ':', '>', '<'},
        {'*', '+', '-', '/', '='},
        {'0', ' ', '_', '%', '|'},
        {'1', '(', ')', '[', ']'},
        {'2', 'a', 'b', 'c', '?'},
        {'3', 'd', 'e', 'f', '!'},
        {'4', 'g', 'h', 'i', '#'},
        {'5', 'j', 'k', 'l', '$'},
        {'6', 'm', 'n', 'o', '~'},
        {'7', 'p', 'q', 'r', 's'},
        {'8', 't', 'u', 'v', '&'},
        {'9', 'w', 'x', 'y', 'z'},
    };
    int press_count = 0;
    char current_key = 0;
    uint time_passed = 0;

    static InputMethodEditor *singleton;

    char scan_keys();
    char get_char();

    InputMethodEditor();    
public:
    void operator=(const InputMethodEditor &) = delete;
    InputMethodEditor(const InputMethodEditor &copy) = delete;
    static InputMethodEditor *get_singleton();

    bool letter_mode = false;
    bool upper_case = false;
    bool raw = false;
    bool can_sleep = false;

    uint keypad_init();
    char wait4input();
    void reset();
};

#endif