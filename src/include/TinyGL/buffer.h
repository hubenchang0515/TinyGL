#ifndef _TINYGL_BUFFER_H
#define _TINYGL_BUFFER_H

#include "base.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum TinyGL_BufferType tiny_buffertype_t;
typedef enum TinyGL_BufferUsage tiny_bufferusage_t;

enum TinyGL_BufferType
{
    TINYGL_ARRAY_BUFFER = 1,
    TINYGL_ELEMENT_ARRAY_BUFFER,
};

enum TinyGL_BufferUsage
{
    TINYGL_STREAM_DRAW = 1,
    // TINYGL_STREAM_READ,
    // TINYGL_STREAM_COPY,
    TINYGL_STATIC_DRAW,
    // TINYGL_STATIC_READ,
    // TINYGL_STATIC_COPY,
    TINYGL_DYNAMIC_DRAW,
    // TINYGL_DYNAMIC_READ,
    // TINYGL_DYNAMIC_COPY,
};

/*********************************************************************************
 * @brief create a buffer
 * @param type buffer type, `TINYGL_VERTEX_SHADER` or `TINYGL_FRAGMENT_SHADER`
 * @return created buffer, 0 means failed
 * @note use `TinyGL_DestroyBuffer` to release buffer
 ********************************************************************************/
unsigned int TinyGL_CreateBuffer();

/*********************************************************************************
 * @brief destroy a buffer
 * @param buffer buffer to destroy
 ********************************************************************************/
void TinyGL_DestroyBuffer(unsigned int buffer);

/*********************************************************************************
 * @brief bind a buffer
 * @param type buffer type, `TINYGL_ARRAY_BUFFER` or `TINYGL_FRAGMENT_SHADER`
 * @param buffer buffer to bind
 ********************************************************************************/
void TinyGL_BindBuffer(unsigned int type, unsigned int buffer);

/*********************************************************************************
 * @brief set buffer data
 * @param type buffer type, `TINYGL_ARRAY_BUFFER` or `TINYGL_FRAGMENT_SHADER`
 * @param buffer buffer to set data
 * @param size size of data
 * @param data data to set
 * @param usage usage of data, `TINYGL_STREAM_DRAW`, `TINYGL_STATIC_DRAW` or `TINYGL_DYNAMIC_DRAW`
 ********************************************************************************/
void TinyGL_SetBufferData(unsigned int type, unsigned int buffer, uintptr_t size, const void* data, tiny_bufferusage_t usage);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _TINYGL_BUFFER_H