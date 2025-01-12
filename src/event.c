#include <TinyGL/event.h>
#include <TinyGL/log.h>
#include <glfw/glfw3.h>

#ifndef TINYGL_MAX_EVENTS
#define TINYGL_MAX_EVENTS 1024
#endif // TINYGL_MAX_EVENTS

tiny_event_t private_events[TINYGL_MAX_EVENTS];
size_t private_events_head = 0;
size_t private_events_tail = 0;

/*********************************************************************************
 * @brief push a event to queue
 * @param event event to push
 ********************************************************************************/
void TinyGL_PushEvent(tiny_event_t* event)
{
    private_events[private_events_tail] = *event;
    private_events_tail = (private_events_tail + 1) % TINYGL_MAX_EVENTS;

    // overflow
    if (private_events_tail == private_events_head)
    {
        private_events_head = (private_events_head + 1) % TINYGL_MAX_EVENTS;
        TINYGL_LOG_WARNING("events queue overflow\n");
    }
}

/*********************************************************************************
 * @brief poll a event from queue
 * @param[out] event to store event
 * @return `false` if there is no event, otherwise `true`
 ********************************************************************************/
bool TinyGL_PollEvent(tiny_event_t* event)
{
    glfwPollEvents();
    // empty
    if (private_events_head == private_events_tail)
    {
        return false;
    }

    *event = private_events[private_events_head];
    private_events_head = (private_events_head + 1) % TINYGL_MAX_EVENTS;
    return true;
}

/*********************************************************************************
 * @brief wait a event from queue
 * @param[out] event to store event
 * @return `false` if failed, otherwise `true`
 * @note block and wait when there is no event
 ********************************************************************************/
bool TinyGL_WaitEvent(tiny_event_t* event)
{
    glfwWaitEvents();
    // empty
    if (private_events_head == private_events_tail)
    {
        return false;
    }

    *event = private_events[private_events_head];
    private_events_head = (private_events_head + 1) % TINYGL_MAX_EVENTS;
    return true;
}

/*********************************************************************************
 * @brief check key event
 * @param event event to check
 * @param key expected key
 * @param mods expected key modifiers
 * @param action expected action, `TINYGL_KEY_RELEASE`, `TINYGL_KEY_PRESS` or `TINYGL_KEY_REPEAT`
 * @return Event meets expectations
 ********************************************************************************/
bool TinyGL_CheckKeyEvent(tiny_event_t* event, tiny_key_t key, int mods, tiny_keystate_t action)
{
    return event->type == TINYGL_EVENT_TYPE_KEY && 
            event->keyEvent.key == key && 
            event->keyEvent.mods == mods && 
            event->keyEvent.action == action;
}