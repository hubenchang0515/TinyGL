#ifndef _BUTTON_H
#define _BUTTON_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum TinyGL_MouseButtonState tiny_buttonstate_t;
typedef enum TinyGL_MouseButton tiny_button_t;

enum TinyGL_MouseButtonState
{
    TINYGL_BUTTON_RELEASE = 0,
    TINYGL_BUTTON_PRESS = 1,
};

// https://www.glfw.org/docs/3.3/group__buttons.html
enum TinyGL_MouseButton
{
    TINYGL_BUTTON_1 = 0,
    TINYGL_BUTTON_2 = 1,
    TINYGL_BUTTON_3 = 2,
    TINYGL_BUTTON_4 = 3,
    TINYGL_BUTTON_5 = 4,
    TINYGL_BUTTON_6 = 5,
    TINYGL_BUTTON_7 = 6,
    TINYGL_BUTTON_8 = 7,
    TINYGL_BUTTON_LEFT = TINYGL_BUTTON_1,
    TINYGL_BUTTON_RIGHT = TINYGL_BUTTON_2,
    TINYGL_BUTTON_MIDDLE = TINYGL_BUTTON_3,
};

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _BUTTON_H