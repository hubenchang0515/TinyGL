#ifndef _TINYGL_COMMON_H
#define _TINYGL_COMMON_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
    #define TINYGL_EXPORT __declspec(dllexport)
    #define TINYGL_IMPORT __declspec(dllimport)
#else
    #define TINYGL_EXPORT
    #define TINYGL_IMPORT
#endif // _MSC_VER

#ifdef TINYGL_BUILD_LIB
    #define TINYGL_API TINYGL_EXPORT
#else
    #define TINYGL_API TINYGL_IMPORT
#endif

#define TINYGL_MSG_LEN 1024

typedef struct TinyGL_Position tiny_pos_t;
typedef struct TinyGL_FloatPosition tiny_fpos_t;

struct TinyGL_Position
{
    int x;
    int y;
};

struct TinyGL_FloatPosition
{
    float x;
    float y;
};

typedef enum TinyGL_DataType tiny_datatype_t;

enum TinyGL_DataType
{
    TINYGL_BYTE = 1,
    TINYGL_UBYTE,
    TINYGL_SHORT,
    TINYGL_USHORT,
    TINYGL_INT,
    TINYGL_UINT,
    TINYGL_FLOAT,
    // TINYGL_DOUBLE,
    // TINYGL_FIXED,
};

typedef void (tiny_loop_func)(void* userdata);

/*********************************************************************************
 * @brief set main loop and run it
 * @param func function to loop
 * @param userdata userdata passed to func
 * @note Can only be called in the main thread, use `TinyGL_StopLoop` to stop
 ********************************************************************************/
void TinyGL_SetMainLoop(tiny_loop_func* func, void* userdata);

/*********************************************************************************
 * @brief stop main loop
 * @note Can only be called in the main thread
 ********************************************************************************/
void TinyGL_StopMainLoop(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _TINYGL_COMMON_H