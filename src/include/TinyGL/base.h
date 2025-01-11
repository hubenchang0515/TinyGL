#ifndef _TINYGL_COMMON_H
#define _TINYGL_COMMON_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define TINYGL_MSG_LEN 1024

typedef struct TinyGL_Position tiny_pos_t;

struct TinyGL_Position
{
    int x;
    int y;
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

#endif // _TINYGL_COMMON_H