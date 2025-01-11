#include <TinyGL/window.h>
#include <glad/gles2.h>
#include <glfw/glfw3.h>
#include <TinyGL/log.h>
#include <stdlib.h>

struct TinyGL_PrivateWindowUserData
{
    int x;
    int y;
    int width;
    int height;
    bool fullscreen;
    void* userdata;
};


static void default_resize_callback(tiny_window_t *window, int width, int height)
{
    if (TinyGL_GetCurrentWindow() == window)
    {
        glViewport(0, 0, width, height);
    }
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
    tiny_window_t window = (tiny_window_t)glfwCreateWindow(width, height, title, NULL, NULL);
    glfwMakeContextCurrent((GLFWwindow*)window);
    if (gladLoadGLES2(glfwGetProcAddress) == 0)
    {
        TINYGL_LOG_ERROR("gladLoadGLLoader failed\n");
    }
    struct TinyGL_PrivateWindowUserData* data = malloc(sizeof(struct TinyGL_PrivateWindowUserData));
    glfwGetWindowPos((GLFWwindow*)window, &data->x, &data->y);
    glfwGetWindowSize((GLFWwindow*)window, &data->width, &data->height);
    data->fullscreen = false;
    data->userdata = NULL;
    glfwSetWindowUserPointer((GLFWwindow*)window, data);

    TinyGL_SetResizeCallback(window, default_resize_callback);
    return window;
}

/*********************************************************************************
 * @brief destroy a window
 * @param window window to destroy
 * @note null unsafe
 ********************************************************************************/
void TinyGL_DestroyWindow(tiny_window_t window)
{
    void* data = glfwGetWindowUserPointer((GLFWwindow*)window);
    if (data != NULL)
    {
        free(data);
    }
    glfwDestroyWindow((GLFWwindow*)window);
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
    glfwGetWindowSize((GLFWwindow*)window, width, height);
}

/*********************************************************************************
 * @brief destroy a window
 * @param window window to destroy
 * @note null unsafe
 ********************************************************************************/
bool TinyGL_WindowShouldClose(tiny_window_t window)
{
    return glfwWindowShouldClose((GLFWwindow*)window);
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
    glfwSetWindowSize((GLFWwindow*)window, width, height);
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
        struct TinyGL_PrivateWindowUserData* data = glfwGetWindowUserPointer((GLFWwindow*)window);
        glfwGetWindowPos((GLFWwindow*)window, &data->x, &data->y);
        glfwGetWindowSize((GLFWwindow*)window, &data->width, &data->height);
        GLFWmonitor* primary = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(primary);
        glfwSetWindowMonitor((GLFWwindow*)window, primary, 0, 0, mode->width, mode->height, mode->refreshRate);
        data->fullscreen = true;
    }
    else
    {
        struct TinyGL_PrivateWindowUserData* data = glfwGetWindowUserPointer((GLFWwindow*)window);
        glfwSetWindowMonitor((GLFWwindow*)window, NULL, data->x, data->y, data->width, data->height, GLFW_DONT_CARE);
        data->fullscreen = false;
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
    struct TinyGL_PrivateWindowUserData* data = glfwGetWindowUserPointer((GLFWwindow*)window);
    return data->fullscreen;
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

    glfwMakeContextCurrent((GLFWwindow*)window);
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
    glfwSwapBuffers((GLFWwindow*)window);
}

/*********************************************************************************
 * @brief poll events
 ********************************************************************************/
void TinyGL_PollEvents()
{
    glfwPollEvents();
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
 * @brief update a window, swap buffers and poll events
 * @param window window to update
 * @note null unsafe
 ********************************************************************************/
void TinyGL_UpdateWindow(tiny_window_t window)
{
    TinyGL_SwapBuffers(window);
    TinyGL_PollEvents();
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
    return glfwGetKey((GLFWwindow*)window, (int)key);
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
    return glfwGetMouseButton((GLFWwindow*)window, (int)button);
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
    glfwGetCursorPos((GLFWwindow*)window, &x, &y);
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
    glfwSetCursorPos((GLFWwindow*)window, (double)pos.x, (double)pos.y);
}

/*********************************************************************************
 * @brief set callback of window resize
 * @param window window to set callback
 * @param fn callback function
 * @return previous callback
 * @note window is null unsafe
 ********************************************************************************/
tiny_resize_func* TinyGL_SetResizeCallback(tiny_window_t window, tiny_resize_func* fn)
{
    return (tiny_resize_func*)glfwSetFramebufferSizeCallback((GLFWwindow*)window, (GLFWframebuffersizefun)fn);
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
    return (tiny_key_func*)glfwSetKeyCallback((GLFWwindow*)window, (GLFWkeyfun)fn);
}