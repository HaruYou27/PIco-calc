/*Copyright 2025 - HaruYou27

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/

#include "ssd1306_driver.hpp"

#include "whattodo.h"
#include "discover.h"

int main()
{
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);
    gpio_put(25, true);

    SSD1306 *oled = new SSD1306(16, 17, i2c0);
    static constexpr uint32_t DELAY = 5000;

    bool tick = true;
    while (true)
    {
        tick = !tick;
        oled->print_overwrite("Konichiwa Sekai !", tick);
        sleep_ms(DELAY);
        oled->print_overwrite("Hello world !", tick);
        sleep_ms(DELAY);
        oled->print_overwrite("Raspberry pi pico", tick);
        sleep_ms(DELAY);
        oled->print_overwrite("HaruYou27", tick);
        sleep_ms(DELAY);
        oled->print_overwrite("Lorem ipsum dolor sit amet,\nconsectetur adipiscing elit, sed\ndo eiusmod tempor incididunt ut\nlabore et dolore magna aliqua.\nUt enim ad minim veniam, quis\nnostrud exercitation ullamco\nlaboris nisi ut aliquip ex ea\ncommodo consequat. Duis aute", tick);
        sleep_ms(DELAY);
        oled->draw_image_fullscreen(whattodo_data)
    }
}