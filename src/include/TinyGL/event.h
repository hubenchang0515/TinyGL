#ifndef _TINYGL_EVENT_H
#define _TINYGL_EVENT_H

#include "base.h"
#include "key.h"
#include "button.h"

// typedef struct TinyGL_Window* tiny_window_t;
#include "window.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum TinyGL_EventType tiny_eventtype_t;
typedef union TingGL_Event tiny_event_t;

enum TinyGL_EventType
{
    TINYGL_EVENT_TYPE_WINDOW_CLOSE = 1,
    TINYGL_EVENT_TYPE_WINDOW_RESIZE,
    TINYGL_EVENT_TYPE_KEY,
    TINYGL_EVENT_TYPE_MOUSE_BUTTON,
    TINYGL_EVENT_TYPE_MOUSE_MOVE,
    TINYGL_EVENT_TYPE_MOUSE_SCROLL,
};

typedef struct TinyGL_WindowCloseEvent tiny_windowcloseevent_t;
struct TinyGL_WindowCloseEvent
{
    tiny_eventtype_t type;
    tiny_window_t window;
};

typedef struct TinyGL_WindowResizeEvent tiny_windowresizeevent_t;
struct TinyGL_WindowResizeEvent
{
    tiny_eventtype_t type;
    tiny_window_t window;
    int width;
    int height;
};

typedef struct TinyGL_KeyEvent tiny_keyevent_t;
struct TinyGL_KeyEvent
{
    tiny_eventtype_t type;
    tiny_window_t window;
    int key;
    int scancode;
    int action;
    int mods;
};

typedef struct TinyGL_MouseButtonEvent tiny_mousebuttonevent_t;
struct TinyGL_MouseButtonEvent
{
    tiny_eventtype_t type;
    tiny_window_t window;
    int button;
    int action;
    int mods;
};

typedef struct TinyGL_MouseMoveEvent tiny_mousemoveevent_t;
struct TinyGL_MouseMoveEvent
{
    tiny_eventtype_t type;
    tiny_window_t window;
    double x;
    double y;
};

typedef struct TinyGL_MouseScrollEvent tiny_mousescrollevent_t;
struct TinyGL_MouseScrollEvent
{
    tiny_eventtype_t type;
    tiny_window_t window;
    double dx;
    double dy;
};

union TingGL_Event
{
    tiny_eventtype_t type;
    tiny_windowcloseevent_t windowCloseEvent;
    tiny_windowresizeevent_t windowResizeEvent;
    tiny_keyevent_t keyEvent;
    tiny_mousebuttonevent_t mouseButtonEvent;
    tiny_mousemoveevent_t mouseMoveEvent;
    tiny_mousescrollevent_t mouseScrollEvent;
};

/*********************************************************************************
 * @brief push a event to queue
 * @param event event to push
 ********************************************************************************/
void TinyGL_PushEvent(tiny_event_t* event);

/*********************************************************************************
 * @brief poll a event from queue
 * @param[out] event to store event
 * @return success or failed
 ********************************************************************************/
bool TinyGL_PollEvent(tiny_event_t* event);

/*********************************************************************************
 * @brief wait a event from queue
 * @param[out] event to store event
 * @return success or failed
 ********************************************************************************/
bool TinyGL_WaitEvent(tiny_event_t* event);

/*********************************************************************************
 * @brief check key event
 * @param event event to check
 * @param key expected key
 * @param mods expected key modifiers
 * @param action expected action, `TINYGL_KEY_RELEASE`, `TINYGL_KEY_PRESS` or `TINYGL_KEY_REPEAT`
 * @return Event meets expectations
 ********************************************************************************/
bool TinyGL_CheckKeyEvent(tiny_event_t* event, tiny_key_t key, int mods, tiny_keystate_t action);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _TINYGL_EVENT_H