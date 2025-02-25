/*Copyright 2025 - Dương Xuân Hiếu 2024604461

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/

#ifndef InputMethodEditor_HPP
#define InputMethodEditor_HPP

class InputMethodEditor
{
private:
    const char letter_m[12][5] = 
    {
        {'0', ' ', '_', '%', '>'},
        {'1', 'a', 'b', 'c', 'd'},
        {'2', 'e', 'f', 'g', 'h'},
        {'3', 'i', 'j', 'k', 'l'},
        {'4', 'm', 'n', 'o', 'p'},
        {'5', 'q', 'r', 's', 't'},
        {'6', 'u', 'v', 'w', 'x'},
        {'7', 'y', 'z', '!', '?'},
        {'8', '(', ')', '[', ']'},
        {'9', ' ', ' ', ' ', ' '},
        {'.', ',', ':', ' ', ' '},
        {'*', '+', '/', '-', '='},
    };
    
    bool upper_case = false;
    
public:
    char wait4input();
};

#endif