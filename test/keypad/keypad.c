/*Copyright 2025 - HaruYou27

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/


#include "pico/stdlib.h"

int main()
{
    const uint PIN_COLUMNS[4] = {5, 6, 7, 8};
    const uint PIN_ROWs[4] = {13, 14, 15, 16};

    for (int index = 0; index < 4; index++)
        {
            uint column = PIN_COLUMNS[index];
            uint row = PIN_ROWs[index];

            gpio_init(column);
            gpio_init(row);
        
            gpio_set_dir(column, GPIO_IN);
            gpio_pull_down(column);
            gpio_set_dir(row, GPIO_OUT);
        
            //gpio_put(column, false);
            //gpio_put(row, true);
        }

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, true);

    bool tick = true;
    gpio_put(PICO_DEFAULT_LED_PIN, tick);

    while (true)
    {
        for (int row = 0; row < 4; row++)
        {
            gpio_put(PIN_ROWs[row], true);
            sleep_ms(1);

            for (int column = 0; column < 4; column++)
            {
                if(gpio_get(PIN_COLUMNS[column]))
                {
                    tick = !tick;
                    gpio_put(PICO_DEFAULT_LED_PIN, tick);
                    sleep_ms(300);
                }
            }
            gpio_put(PIN_ROWs[row], false);
        }
    }
    gpio_put(PICO_DEFAULT_LED_PIN, false);
    return 0;
}