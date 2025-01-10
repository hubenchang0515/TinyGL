#include <TinyGL/window.h>
#include <glad/gl.h>
#include <glfw/glfw3.h>
#include <TinyGL/log.h>

/*********************************************************************************
 * @brief create a window
 * @param title title of window
 * @param width pixel width of window
 * @param height pixel height of window
 * @return created window
 * @note use TinyGL_DestroyWindow to release window
 ********************************************************************************/
tiny_window_t TinyGL_CreateWindow(const char* title, int width, int height)
{
    if (glfwInit() == GLFW_FALSE)
    {
        TINYGL_LOG_ERROR("glfwInit failed\n");
    }
    tiny_window_t window = (tiny_window_t)glfwCreateWindow(width, height, title, NULL, NULL);
    glfwMakeContextCurrent((GLFWwindow*)window);
    if (gladLoadGL(glfwGetProcAddress) == 0)
    {
        TINYGL_LOG_ERROR("gladLoadGLLoader failed\n");
    }
    return window;
}

/*********************************************************************************
 * @brief destroy a window
 * @param window window to destroy
 * @note null unsafe
 ********************************************************************************/
void TinyGL_DestroyWindow(tiny_window_t window)
{
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
    int width, height;
    TinyGL_GetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height);
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
    glClearDepth(0);
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
    return glfwGetKey((GLFWwindow*)window, key);
}