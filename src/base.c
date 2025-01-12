#include <TinyGL/base.h>

#if defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)

#ifdef __cplusplus
extern "C" {
#endif

TINYGL_EXPORT uint32_t NvOptimusEnablement = 1;
TINYGL_EXPORT int AmdPowerXpressRequestHighPerformance = 1;

#ifdef __cplusplus
}
#endif

#endif

#ifdef __wasm
    #include <emscripten.h>
#else
    static bool private_looping = false;
#endif // __wasm



/*********************************************************************************
 * @brief set main loop and run it
 * @param func function to loop
 * @param userdata userdata passed to func
 * @note Can only be called in the main thread, use `TinyGL_StopLoop` to stop
 ********************************************************************************/
void TinyGL_SetMainLoop(tiny_loop_func* func, void* userdata)
{
#ifdef __wasm
    emscripten_set_main_loop_arg(func, userdata, 0, true);
#else
    private_looping = true;
    while (private_looping)
    {
        func(userdata);
    }
#endif
}

/*********************************************************************************
 * @brief stop main loop
 * @note Can only be called in the main thread
 ********************************************************************************/
void TinyGL_StopMainLoop(void)
{
#ifdef __wasm
    emscripten_cancel_main_loop();
#else
    private_looping = false;
#endif
}