#ifndef _TINYGL_LOOP_H
#define _TINYGL_LOOP_H

typedef void (tiny_loop_func)(void* userdata);

/*********************************************************************************
 * @brief set main loop and run it
 * @param func function to loop
 * @param userdata userdata passed to func
 * @note use `TinyGL_StopLoop` to stop
 ********************************************************************************/
void TinyGL_SetLoop(tiny_loop_func* func, void* userdata);

/*********************************************************************************
 * @brief stop main loop
 ********************************************************************************/
void TinyGL_StopLoop(void);

#endif // _TINYGL_LOOP_H