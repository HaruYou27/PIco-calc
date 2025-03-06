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