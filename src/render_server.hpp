#ifndef RENDER_SERVER_HPP
#define RENDER_SERVER_HPP

#include <string>

#include "st7789-library-for-pico/src/include/pico/st7789.h"

class RenderServer
{
private:
    static RenderServer *singleton;
    RenderServer();

    bool is_screen_on = false;
public:
    void operator=(const RenderServer &) = delete;
    RenderServer(const RenderServer &copy) = delete;
    static RenderServer *get_singleton();

    void print_raw(const std::string *text);
    void print_py(const std::string *text);
    
    void screen_fill();
    void screen_toggle();

    static std::string text_wrap();
};

#endif