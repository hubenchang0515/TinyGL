#include <TinyGL/loop.h>
#include <TinyGL/base.h>

#ifdef __wasm
    #include <emscripten.h>
#else
    static bool _loop = false;
#endif // __wasm



/*********************************************************************************
 * @brief set main loop and run it
 * @param func function to loop
 * @param userdata userdata passed to func
 * @note use `TinyGL_StopLoop` to stop
 ********************************************************************************/
void TinyGL_SetLoop(tiny_loop_func* func, void* userdata)
{
#ifdef __wasm
    emscripten_set_main_loop_arg(func, userdata, 0, true);
#else
    _loop = true;
    while (_loop)
    {
        func(userdata);
    }
#endif
}

/*********************************************************************************
 * @brief stop main loop
 ********************************************************************************/
void TinyGL_StopLoop(void)
{
#ifdef __wasm
    emscripten_cancel_main_loop();
#else
    _loop = false;
#endif
}