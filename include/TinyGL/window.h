#ifndef _TINYGL_WINDOW_H
#define _TINYGL_WINDOW_H

#include "base.h"
#include "key.h"

typedef void* tiny_window_t;

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************************
 * @brief create a window
 * @param title title of window
 * @param width pixel width of window
 * @param height pixel height of window
 * @return created window
 * @note use TinyGL_DestroyWindow to release window
 ********************************************************************************/
tiny_window_t TinyGL_CreateWindow(const char* title, int width, int height);

/*********************************************************************************
 * @brief destroy a window
 * @param window window to destroy
 * @note null unsafe
 ********************************************************************************/
void TinyGL_DestroyWindow(tiny_window_t window);

/*********************************************************************************
 * @brief get window size
 * @param window window to get size
 * @param[out] width return width if window if not null
 * @param[out] height return height of window if not null
 * @note window is null unsafe
 ********************************************************************************/
void TinyGL_GetWindowSize(tiny_window_t window, int* width, int* height);

/*********************************************************************************
 * @brief destroy a window
 * @param window window to destroy
 * @note null unsafe
 ********************************************************************************/
bool TinyGL_WindowShouldClose(tiny_window_t window);

/*********************************************************************************
 * @brief get current window 
 * @return current window
 ********************************************************************************/
tiny_window_t TinyGL_GetCurrentWindow();

/*********************************************************************************
 * @brief set current window 
 * @param window window to set
 * @return previous window
 * @note this function usually does NOT need to be called manually
 ********************************************************************************/
tiny_window_t TinyGL_SetCurrentWindow(tiny_window_t window);

/*********************************************************************************
 * @brief swap buffers
 * @param window window to swap buffers
 * @note null unsafe
 ********************************************************************************/
void TinyGL_SwapBuffers(tiny_window_t window);

/*********************************************************************************
 * @brief poll events
 ********************************************************************************/
void TinyGL_PollEvents();

/*********************************************************************************
 * @brief clear a window
 * @param window window to clear
 * @note null unsafe
 ********************************************************************************/
void TinyGL_ClearWindow(tiny_window_t window);

/*********************************************************************************
 * @brief clear a window, swap buffers and poll events
 * @param window window to clear
 * @note null unsafe
 ********************************************************************************/
void TinyGL_UpdateWindow(tiny_window_t window);

/*********************************************************************************
 * @brief get key state window
 * @param window window to get input
 * @param key key to get state
 * @return `TINYGL_KEY_PRESS` or `TINYGL_KEY_RELEASE`
 * @note window is null unsafe
 ********************************************************************************/
tiny_keystate_t TinyGL_GetKeyState(tiny_window_t window, tiny_key_t key);

#ifdef __cplusplus
}; // extern "C" {
#endif

#endif // _TINYGL_WINDOW_H