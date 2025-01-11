#include <TinyGL/buffer.h>
#include <TinyGL/log.h>
#include <glad/gles2.h>

static inline unsigned int TINYGL_BUFFER_TYPE_TO_GLES(tiny_buffertype_t type)
{
    switch (type)
    {
    case TINYGL_ARRAY_BUFFER: return GL_ARRAY_BUFFER;
    case TINYGL_ELEMENT_ARRAY_BUFFER: return GL_ELEMENT_ARRAY_BUFFER;
    }

    return 0;
}

static inline unsigned int TINYGL_BUFFER_USAGE_TO_GLES(tiny_bufferusage_t usage)
{
    switch (usage)
    {
    case TINYGL_STREAM_DRAW: return GL_STREAM_DRAW;
    case TINYGL_STATIC_DRAW: return GL_STATIC_DRAW;
    case TINYGL_DYNAMIC_DRAW: return GL_DYNAMIC_DRAW;
    }

    return 0;
}

/*********************************************************************************
 * @brief create a buffer
 * @return created buffer, 0 means failed
 * @note use `TinyGL_DestroyBuffer` to release buffer
 ********************************************************************************/
unsigned int TinyGL_CreateBuffer()
{
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    return buffer;
}

/*********************************************************************************
 * @brief destroy a buffer
 * @param buffer buffer to destroy
 ********************************************************************************/
void TinyGL_DestroyBuffer(unsigned int buffer)
{
    glDeleteBuffers(1, &buffer);
}

/*********************************************************************************
 * @brief bind a buffer
 * @param type buffer type, `TINYGL_ARRAY_BUFFER` or `TINYGL_FRAGMENT_SHADER`
 * @param buffer buffer to bind
 ********************************************************************************/
void TinyGL_BindBuffer(unsigned int type, unsigned int buffer)
{
    glBindBuffer(TINYGL_BUFFER_TYPE_TO_GLES(type), buffer);
}

/*********************************************************************************
 * @brief set buffer data
 * @param type buffer type, `TINYGL_ARRAY_BUFFER` or `TINYGL_FRAGMENT_SHADER`
 * @param buffer buffer to set data
 * @param size size of data
 * @param data data to set
 * @param usage usage of data, `TINYGL_STREAM_DRAW`, `TINYGL_STATIC_DRAW` or `TINYGL_DYNAMIC_DRAW`
 ********************************************************************************/
void TinyGL_SetBufferData(unsigned int type, unsigned int buffer, uintptr_t size, const void* data, tiny_bufferusage_t usage)
{
    glBindBuffer(TINYGL_BUFFER_TYPE_TO_GLES(type), buffer);
    glBufferData(TINYGL_BUFFER_TYPE_TO_GLES(type), size, data, TINYGL_BUFFER_USAGE_TO_GLES(usage));
}