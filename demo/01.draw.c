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

struct Userdata
{
    tiny_window_t window;
    tiny_renderer_t renderer;
};

void keycallback(tiny_window_t window, tiny_key_t key, int scancode, tiny_keystate_t action, tiny_key_t mods)
{
    TINYGL_LOG_INFO("%d\n", key);
}

void loop(struct Userdata* args)
{
    TinyGL_ClearWindow(args->window);
    drawPixels(args->renderer);
    drawLines(args->renderer);
    drawTriangles(args->renderer);
    TinyGL_UpdateWindow(args->window);
    TinyGL_GetMousePos(args->window);

    if (TinyGL_WindowShouldClose(args->window))
        TinyGL_StopLoop();

    if (TinyGL_GetKeyState(args->window, TINYGL_KEY_F11) == TINYGL_KEY_PRESS)
        TinyGL_SetWindowFullScreen(args->window, !TinyGL_IsWindowFullScreen(args->window));
}

int main()
{
    tiny_window_t window = TinyGL_CreateWindow("TinyGL", 640, 640);
    tiny_renderer_t renderer = TinyGL_CreateDefault2DRenderer();
    TinyGL_SetKeyCallback(window, keycallback);

    struct Userdata args = {window, renderer};

    TinyGL_SetLoop((tiny_loop_func*)loop, (void*)&args);

    TinyGL_DestroyRenderer(renderer);
    TinyGL_DestroyWindow(window);
    return 0;
}