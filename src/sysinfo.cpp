/*Copyright 2025 - HaruYou27

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/

#include "sysinfo.hpp"

SystemMonitor::SystemMonitor()
{
    adc_init();
    adc_gpio_init(29);
    adc_set_temp_sensor_enabled(true);
}

SystemMonitor::~SystemMonitor() {}
SystemMonitor *SystemMonitor::singleton = nullptr;

SystemMonitor *SystemMonitor::get_singleton()
{
    if (singleton == nullptr)
    {
        singleton = new SystemMonitor();
    }
    return singleton;
}

float SystemMonitor::read_adc_volt(uint adc_pin)
{
    adc_select_input(adc_pin);
    return adc_read() * 3.3f / (1 << 12);
}

float SystemMonitor::read_temperature()
{
    return 27.0f - (read_adc_volt(4) - 0.706f) / 0.001721f ;
}

float SystemMonitor::read_voltage()
{
    return 10 * read_adc_volt(3);
}