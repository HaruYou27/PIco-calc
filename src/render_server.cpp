#include "render_server.hpp"

RenderServer::RenderServer() {}

RenderServer *RenderServer::singleton = nullptr;

RenderServer *RenderServer::get_singleton()
{
    if (singleton == nullptr)
    {
        


        st7789_init(config, 320, 170);
        singleton = new RenderServer();
    }
    return singleton;
}

void RenderServer::screen_clear()
{
    st7789_fill(0);
}