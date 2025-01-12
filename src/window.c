#include <TinyGL/window.h>
#include <TinyGL/event.h>
#include <glad/gles2.h>
#include <glfw/glfw3.h>
#include <TinyGL/log.h>
#include <stdlib.h>

struct TinyGL_Window
{
    GLFWwindow* window;

    bool fullscreen;
    int x;          // before fullscreen
    int y;          // before fullscreen
    int width;      // before fullscreen
    int height;     // before fullscreen

    tiny_windowclose_func* closeCallback;
    tiny_windowresize_func* resizeCallback;
    tiny_key_func* keyCallback;
    tiny_mousebutton_func* mouseButtonCallback;
    tiny_mousemove_func* mouseMoveCallback;
    tiny_mousescroll_func* mouseScrollCallback;
    // TODO: 补充其他回调
};

static void private_windowclose_func(GLFWwindow* window)
{
    TINYGL_LOG_DEBUG("[WINDOW CLOSE] window:%p\n", window);

    tiny_window_t w = glfwGetWindowUserPointer(window);
    if (w->closeCallback)
        w->closeCallback(w);

    tiny_event_t event;
    event.type = TINYGL_EVENT_TYPE_WINDOW_CLOSE;
    event.windowCloseEvent.window = w;
    TinyGL_PushEvent(&event);
}

static void private_windowresize_callback(GLFWwindow* window, int width, int height)
{
    TINYGL_LOG_DEBUG("[WINDOW RESIZE] window:%p width:%d height:%d\n", window, width, height);
    if (glfwGetCurrentContext() == window)
    {
        glViewport(0, 0, width, height);
    }

    tiny_window_t w = glfwGetWindowUserPointer(window);
    if (w->resizeCallback)
        w->resizeCallback(w, width, height);

    tiny_event_t event;
    event.type = TINYGL_EVENT_TYPE_WINDOW_RESIZE;
    event.windowResizeEvent.window = w;
    event.windowResizeEvent.width = width;
    event.windowResizeEvent.height = height;
    TinyGL_PushEvent(&event);
}

static void private_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    TINYGL_LOG_DEBUG("[KEY] window:%p key:%d scancode:%d action:%d mods:%d\n", window, key, scancode, action, mods);

    tiny_window_t w = glfwGetWindowUserPointer(window);
    if (w->keyCallback)
        w->keyCallback(w, (tiny_key_t)key, scancode, action, mods);

    tiny_event_t event;
    event.type = TINYGL_EVENT_TYPE_KEY;
    event.keyEvent.window = w;
    event.keyEvent.key = key;
    event.keyEvent.scancode = scancode;
    event.keyEvent.action = action;
    event.keyEvent.mods = mods;
    TinyGL_PushEvent(&event);
}

static void private_mousebutton_callback(GLFWwindow* window, int button, int action, int mods)
{
    TINYGL_LOG_DEBUG("[MOUSE BUTTON] window:%p button:%d action:%d mods:%d\n", window, button, action, mods);

    tiny_window_t w = glfwGetWindowUserPointer(window);
    if (w->mouseButtonCallback)
        w->mouseButtonCallback(w, (tiny_button_t)button, action, mods);

    tiny_event_t event;
    event.type = TINYGL_EVENT_TYPE_MOUSE_BUTTON;
    event.mouseButtonEvent.window = w;
    event.mouseButtonEvent.button = button;
    event.mouseButtonEvent.action = action;
    event.mouseButtonEvent.mods = mods;
    TinyGL_PushEvent(&event);
}

static void private_mousemove_callback(GLFWwindow* window, double x, double y)
{
    TINYGL_LOG_DEBUG("[MOUSE MOVE] window:%p x:%f y:%f\n", window, x, y);

    tiny_window_t w = glfwGetWindowUserPointer(window);
    if (w->mouseMoveCallback)
        w->mouseMoveCallback(w, (float)x, (float)y);
    
    tiny_event_t event;
    event.type = TINYGL_EVENT_TYPE_MOUSE_MOVE;
    event.mouseMoveEvent.window = w;
    event.mouseMoveEvent.x = x;
    event.mouseMoveEvent.y = y;
    TinyGL_PushEvent(&event);
}

static void private_mousescroll_callback(GLFWwindow* window, double dx, double dy)
{
    TINYGL_LOG_DEBUG("[MOUSE SCROLL] window:%p dx:%f dy:%f\n", window, dx, dy);

    tiny_window_t w = glfwGetWindowUserPointer(window);
    if (w->mouseScrollCallback)
        w->mouseScrollCallback(w, (float)dx, (float)dy);

    tiny_event_t event;
    event.type = TINYGL_EVENT_TYPE_MOUSE_MOVE;
    event.mouseScrollEvent.window = w;
    event.mouseScrollEvent.dx = dx;
    event.mouseScrollEvent.dy = dy;
    TinyGL_PushEvent(&event);
}

/*********************************************************************************
 * @brief create a window
 * @param title title of window
 * @param width pixel width of window
 * @param height pixel height of window
 * @return created window
 * @note use `TinyGL_DestroyWindow` to release window
 ********************************************************************************/
tiny_window_t TinyGL_CreateWindow(const char* title, int width, int height)
{
    if (glfwInit() == GLFW_FALSE)
    {
        TINYGL_LOG_ERROR("glfwInit failed\n");
    }

    tiny_window_t window = malloc(sizeof(struct TinyGL_Window));
    window->window = glfwCreateWindow(width, height, title, NULL, NULL);
    window->fullscreen = false;
    window->closeCallback = NULL;
    window->resizeCallback = NULL;
    window->keyCallback = NULL;
    window->mouseButtonCallback = NULL;
    window->mouseMoveCallback = NULL;
    window->mouseScrollCallback = NULL;
    glfwGetWindowPos(window->window, &window->x, &window->y);
    glfwGetWindowSize(window->window, &window->width, &window->height);
    glfwSetWindowUserPointer(window->window, window);

    glfwMakeContextCurrent(window->window);
    if (gladLoadGLES2(glfwGetProcAddress) == 0)
    {
        TINYGL_LOG_ERROR("gladLoadGLLoader failed\n");
    }

    glfwSetWindowCloseCallback(window->window, private_windowclose_func);
    glfwSetFramebufferSizeCallback(window->window, private_windowresize_callback);
    glfwSetKeyCallback(window->window, private_key_callback);
    glfwSetMouseButtonCallback(window->window, private_mousebutton_callback);
    glfwSetCursorPosCallback(window->window, private_mousemove_callback);
    glfwSetScrollCallback(window->window, private_mousescroll_callback);
    return window;
}

/*********************************************************************************
 * @brief destroy a window
 * @param window window to destroy
 * @note null unsafe
 ********************************************************************************/
void TinyGL_DestroyWindow(tiny_window_t window)
{
    glfwDestroyWindow(window->window);
    free(window);
}

/*********************************************************************************
 * @brief get window size
 * @param window window to get size
 * @param[out] width return width if window if not null
 * @param[out] height return height of window if not null
 * @note window is null unsafe
 ********************************************************************************/
void TinyGL_GetWindowSize(tiny_window_t window, int* width, int* height)
{
    glfwGetWindowSize(window->window, width, height);
}

/*********************************************************************************
 * @brief destroy a window
 * @param window window to destroy
 * @note null unsafe, must be called after `TinyGL_PollEvent` or `TinyGL_WaitEvent`
 ********************************************************************************/
bool TinyGL_WindowShouldClose(tiny_window_t window)
{
    return glfwWindowShouldClose(window->window);
}

/*********************************************************************************
 * @brief set the viewport size to the window size
 * @param window window to set viewport size
 * @note null unsafe
 ********************************************************************************/
void TinyGL_SetWindowViewSize(tiny_window_t window)
{
    int width, height;
    TinyGL_GetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height);
}

/*********************************************************************************
 * @brief set the window size
 * @param window window to set viewport size
 * @param width new width of window
 * @param height new height of window
 * @note null unsafe
 ********************************************************************************/
void TinyGL_SetWindowSize(tiny_window_t window, int width, int height)
{
    glfwSetWindowSize(window->window, width, height);
}

/*********************************************************************************
 * @brief set the window size
 * @param window window to set viewport size
 * @param width new width of window
 * @param height new height of window
 * @note null unsafe
 ********************************************************************************/
void TinyGL_SetWindowFullScreen(tiny_window_t window, bool fullscreen)
{
    if (fullscreen)
    {
        struct TinyGL_PrivateWindowUserData* data = glfwGetWindowUserPointer(window->window);
        glfwGetWindowPos(window->window, &window->x, &window->y);
        glfwGetWindowSize(window->window, &window->width, &window->height);
        GLFWmonitor* primary = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(primary);
        glfwSetWindowMonitor(window->window, primary, 0, 0, mode->width, mode->height, mode->refreshRate);
        window->fullscreen = true;
    }
    else
    {
        glfwSetWindowMonitor(window->window, NULL, window->x, window->y, window->width, window->height, GLFW_DONT_CARE);
        window->fullscreen = false;
    }
    
}

/*********************************************************************************
 * @brief check whether the window is full screen
 * @param window window to check
 * @return whether the window is full screen
 * @note null unsafe
 ********************************************************************************/
bool TinyGL_IsWindowFullScreen(tiny_window_t window)
{
    return window->fullscreen;
}

/*********************************************************************************
 * @brief get current window 
 * @return current window
 ********************************************************************************/
tiny_window_t TinyGL_GetCurrentWindow()
{
    return (tiny_window_t)glfwGetCurrentContext();
}

/*********************************************************************************
 * @brief set current window 
 * @param window window to set
 * @return previous window
 * @note this function usually does NOT need to be called manually
 ********************************************************************************/
tiny_window_t TinyGL_SetCurrentWindow(tiny_window_t window)
{
    tiny_window_t prev = TinyGL_GetCurrentWindow();
    if (window == prev)
    {
        return prev;
    }

    glfwMakeContextCurrent(window->window);
    TinyGL_SetWindowViewSize(window);
    return prev;
}

/*********************************************************************************
 * @brief swap buffers
 * @param window window to swap buffers
 * @note null unsafe
 ********************************************************************************/
void TinyGL_SwapBuffers(tiny_window_t window)
{
    glfwSwapBuffers(window->window);
}

/*********************************************************************************
 * @brief clear a window
 * @param window window to clear
 * @note null unsafe
 ********************************************************************************/
void TinyGL_ClearWindow(tiny_window_t window)
{
    TinyGL_SetCurrentWindow(window);
    glClearColor(0, 0, 0, 0xff);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/*********************************************************************************
 * @brief update a window, swap buffers
 * @param window window to update
 * @note null unsafe
 ********************************************************************************/
void TinyGL_UpdateWindow(tiny_window_t window)
{
    TinyGL_SwapBuffers(window);
}

/*********************************************************************************
 * @brief get key state window
 * @param window window to get input
 * @param key key to get state
 * @return `TINYGL_KEY_PRESS` or `TINYGL_KEY_RELEASE`
 * @note window is null unsafe
 ********************************************************************************/
tiny_keystate_t TinyGL_GetKeyState(tiny_window_t window, tiny_key_t key)
{
    return glfwGetKey(window->window, (int)key);
}

/*********************************************************************************
 * @brief get mouse button state window
 * @param window window to get input
 * @param button mouse button to get state
 * @return `TINYGL_BUTTON_PRESS` or `TINYGL_BUTTON_RELEASE`
 * @note window is null unsafe
 ********************************************************************************/
tiny_buttonstate_t TinyGL_GetMouseButtonState(tiny_window_t window, tiny_button_t button)
{
    return glfwGetMouseButton(window->window, (int)button);
}

/*********************************************************************************
 * @brief get mouse mouse cursor position of window
 * @param window window to get mouse cursor position
 * @return position of mouse cursor
 * @note window is null unsafe
 ********************************************************************************/
tiny_pos_t TinyGL_GetMousePos(tiny_window_t window)
{
    double x, y;
    glfwGetCursorPos(window->window, &x, &y);
    return (tiny_pos_t){(int)x, (int)y};
}

/*********************************************************************************
 * @brief set mouse mouse cursor position of window
 * @param window window to set mouse cursor position
 * @param pos position to set
 * @note window is null unsafe
 ********************************************************************************/
void TinyGL_SetMousePos(tiny_window_t window, tiny_pos_t pos)
{
    glfwSetCursorPos(window->window, (double)pos.x, (double)pos.y);
}

/*********************************************************************************
 * @brief set callback of window resize
 * @param window window to set callback
 * @param fn callback function
 * @return previous callback
 * @note window is null unsafe
 ********************************************************************************/
tiny_windowresize_func* TinyGL_SetResizeCallback(tiny_window_t window, tiny_windowresize_func* fn)
{
    tiny_windowresize_func* prev = window->resizeCallback;
    window->resizeCallback = fn;
    return prev;
}

/*********************************************************************************
 * @brief set callback of keyboard input
 * @param window window to get input
 * @param fn callback function
 * @return previous callback
 * @note window is null unsafe
 ********************************************************************************/
tiny_key_func* TinyGL_SetKeyCallback(tiny_window_t window, tiny_key_func* fn)
{
    return (tiny_key_func*)glfwSetKeyCallback(window->window, (GLFWkeyfun)fn);
}