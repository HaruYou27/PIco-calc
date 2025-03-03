#include "pico/stdlib.h"

int main()
{
    const uint PIN_COLUMNS[4] = {9, 10, 11, 12};
    const uint PIN_ROWs[4] = {8, 7, 6, 5};

    for (int index = 0; index < 4; index++)
        {
            uint column = PIN_COLUMNS[index];
            uint row = PIN_ROWs[index];

            gpio_init(column);
            gpio_init(row);
        
            gpio_set_dir(column, false);
            gpio_pull_down(column);
            gpio_set_dir(row, true);
        
            gpio_put(column, false);
            gpio_put(row, true);
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
            sleep_ms(4);

            for (int column; column < 4; column++)
            {
                if(gpio_get(column))
                {
                    while (gpio_get(column))
                    {
                        sleep_ms(4);
                    }
                    tick = !tick;
                    gpio_put(PICO_DEFAULT_LED_PIN, tick);
                    sleep_ms(1000);
                }
            }
            gpio_put(PIN_ROWs[row], false);
        }
    }
    gpio_put(PICO_DEFAULT_LED_PIN, false);
}