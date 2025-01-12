#ifndef _TINYGL_WINDOW_H
#define _TINYGL_WINDOW_H

#include "base.h"
#include "key.h"
#include "button.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TinyGL_Window* tiny_window_t;

/*********************************************************************************
 * @brief window close callback
 * @param window the window that received the event
 ********************************************************************************/
typedef void (tiny_windowclose_func) (tiny_window_t window);

/*********************************************************************************
 * @brief window resize callback
 * @param window the window that received the event
 * @param width new width of window
 * @param height new height of window
 ********************************************************************************/
typedef void (tiny_windowresize_func) (tiny_window_t window, int width, int height);

/*********************************************************************************
 * @brief key callback
 * @param window the window that received the event
 * @param key the keyboard key that was pressed or released
 * @param scancode the system-specific scancode of the key
 * @param action `TINYGL_KEY_PRESS` or `TINYGL_KEY_RELEASE`
 * @param mods which modifier keys were held down
 ********************************************************************************/
typedef void (tiny_key_func) (tiny_window_t window, tiny_key_t key, int scancode, tiny_keystate_t action, tiny_key_t mods);

/*********************************************************************************
 * @brief mouse button callback
 * @param window the window that received the event
 * @param button the mouse button that was pressed or released
 * @param action `TINYGL_BUTTON_PRESS` or `TINYGL_BUTTON_RELEASE`
 * @param mods which modifier keys were held down
 ********************************************************************************/
typedef void (tiny_mousebutton_func) (tiny_window_t window, int button, tiny_buttonstate_t action, int mods);

/*********************************************************************************
 * @brief mouse cursor move callback
 * @param window the window that received the event
 * @param x x position of mouse cursor
 * @param y y position of mouse cursor
 ********************************************************************************/
typedef void (tiny_mousemove_func) (tiny_window_t window, float x, float y);

/*********************************************************************************
 * @brief mouse scroll callback
 * @param window the window that received the event
 * @param dx difference of x position
 * @param dy difference of y position
 ********************************************************************************/
typedef void (tiny_mousescroll_func) (tiny_window_t window, float dx, float dy);

/*********************************************************************************
 * @brief create a window
 * @param title title of window
 * @param width pixel width of window
 * @param height pixel height of window
 * @return created window
 * @note use `TinyGL_DestroyWindow` to release window
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
 * @note null unsafe, must be called after `TinyGL_PollEvent` or `TinyGL_WaitEvent`
 ********************************************************************************/
bool TinyGL_WindowShouldClose(tiny_window_t window);

/*********************************************************************************
 * @brief set the viewport size to the window size
 * @param window window to set viewport size
 * @note null unsafe
 ********************************************************************************/
void TinyGL_SetWindowViewSize(tiny_window_t window);

/*********************************************************************************
 * @brief set the window size
 * @param window window to set viewport size
 * @param width new width of window
 * @param height new height of window
 * @note null unsafe
 ********************************************************************************/
void TinyGL_SetWindowSize(tiny_window_t window, int width, int height);

/*********************************************************************************
 * @brief set the window size
 * @param window window to set viewport size
 * @param width new width of window
 * @param height new height of window
 * @note null unsafe
 ********************************************************************************/
void TinyGL_SetWindowFullScreen(tiny_window_t window, bool fullscreen);

/*********************************************************************************
 * @brief check whether the window is full screen
 * @param window window to check
 * @return whether the window is full screen
 * @note null unsafe
 ********************************************************************************/
bool TinyGL_IsWindowFullScreen(tiny_window_t window);

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
 * @brief clear a window
 * @param window window to clear
 * @note null unsafe
 ********************************************************************************/
void TinyGL_ClearWindow(tiny_window_t window);

/*********************************************************************************
 * @brief clear a window, swap buffers
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

/*********************************************************************************
 * @brief get mouse button state window
 * @param window window to get input
 * @param button mouse button to get state
 * @return `TINYGL_BUTTON_PRESS` or `TINYGL_BUTTON_RELEASE`
 * @note window is null unsafe
 ********************************************************************************/
tiny_buttonstate_t TinyGL_GetMouseButtonState(tiny_window_t window, tiny_button_t button);

/*********************************************************************************
 * @brief get mouse mouse cursor position of window
 * @param window window to get mouse cursor position
 * @return position of mouse cursor
 * @note window is null unsafe
 ********************************************************************************/
tiny_pos_t TinyGL_GetMousePos(tiny_window_t window);

/*********************************************************************************
 * @brief set mouse mouse cursor position of window
 * @param window window to set mouse cursor position
 * @param pos position to set
 * @note window is null unsafe
 ********************************************************************************/
void TinyGL_SetMousePos(tiny_window_t window, tiny_pos_t pos);

/*********************************************************************************
 * @brief set callback of window resize
 * @param window window to set callback
 * @param fn callback function
 * @return previous callback
 * @note window is null unsafe.
 * @note The default callback is set the viewport size to the window size. 
 * @note If you change the callback function, please set the viewport size yourself. 
 ********************************************************************************/
tiny_windowresize_func* TinyGL_SetResizeCallback(tiny_window_t window, tiny_windowresize_func* fn);

/*********************************************************************************
 * @brief set callback of keyboard input
 * @param window window to get input
 * @param fn callback function
 * @return previous callback
 * @note window is null unsafe
 ********************************************************************************/
tiny_key_func* TinyGL_SetKeyCallback(tiny_window_t window, tiny_key_func* fn);


#ifdef __cplusplus
}; // extern "C" {
#endif

#endif // _TINYGL_WINDOW_H