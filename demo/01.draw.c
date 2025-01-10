#include <TinyGL/TinyGL.h>

void drawPixels(tiny_renderer_t renderer)
{
    tiny_pos_t pixels[] = {
        {100, 100},
        {200, 100},
        {300, 100},
    };

    tiny_color_t colors[] = {
        TINYGL_COLOR_RGB(0xff, 0, 0),
        TINYGL_COLOR_RGB(0, 0xff, 0),
        TINYGL_COLOR_RGB(0, 0, 0xff),
    };

    TinyGL_DrawPixels(renderer, 3, pixels, colors);
}

void drawLines(tiny_renderer_t renderer)
{
    tiny_pos_t pixels[] = {
        {100, 200},
        {200, 200},

        {300, 200},
        {400, 200},
    };

    tiny_color_t colors[] = {
        TINYGL_COLOR_RGB(0xff, 0, 0),
        TINYGL_COLOR_RGB(0, 0xff, 0),

        TINYGL_COLOR_RGB(0, 0xff, 0),
        TINYGL_COLOR_RGB(0, 0, 0xff),
    };

    TinyGL_DrawLines(renderer, 4, pixels, colors);
}

void drawTriangles(tiny_renderer_t renderer)
{
    tiny_pos_t pixels[] = {
        {150, 300},
        {100, 400},
        {200, 400},

        {350, 300},
        {300, 400},
        {400, 400},
    };

    tiny_color_t colors[] = {
        TINYGL_COLOR_RGB(0xff, 0, 0),
        TINYGL_COLOR_RGB(0, 0xff, 0),
        TINYGL_COLOR_RGB(0, 0, 0xff),

        TINYGL_COLOR_RGB(0xff, 0xff, 0),
        TINYGL_COLOR_RGB(0, 0xff, 0xff),
        TINYGL_COLOR_RGB(0xff, 0, 0xff),
    };

    TinyGL_DrawTriangles(renderer, 6, pixels, colors);
}

int main()
{
    tiny_window_t window = TinyGL_CreateWindow("TinyGL", 640, 640);
    tiny_renderer_t renderer = TinyGL_CreateDefaultRenderer();

    while (!TinyGL_WindowShouldClose(window))
    {
        if (TinyGL_GetKeyState(window, TINYGL_KEY_ESCAPE) == TINYGL_KEY_PRESS)
        {
            break;;
        }
        TinyGL_ClearWindow(window);
        drawPixels(renderer);
        drawLines(renderer);
        drawTriangles(renderer);
        TinyGL_UpdateWindow(window);
    }

    TinyGL_DestroyRenderer(renderer);
    TinyGL_DestroyWindow(window);
    return 0;
}