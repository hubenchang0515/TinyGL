#ifndef _TINYGL_COLOR_H
#define _TINYGL_COLOR_H

#include "base.h"

typedef uint32_t tiny_color_t; // ARGB

#define TINYGL_COLOR_RGBA(R, G, B, A) ((tiny_color_t)((((tiny_color_t)(R)) << 16) | (((tiny_color_t)(G)) << 8) | ((tiny_color_t)(B)) | (((tiny_color_t)(A)) << 24)))
#define TINYGL_COLOR_ARGB(A, R, G, B) TINYGL_COLOR_RGBA(R, G, B, A)
#define TINYGL_COLOR_RGB(R, G, B) TINYGL_COLOR_RGBA(R, G, B, 0xff)
#define TINYGL_COLOR_GRAY(GRAY) TINYGL_COLOR_RGB(GRAY, GRAY, GRAY)

#define TINYGL_COLOR_GET_ALPHA(COLOR) ((((tiny_color_t)(COLOR)) >> 24) & 0xff)
#define TINYGL_COLOR_GET_RED(COLOR) ((((tiny_color_t)(COLOR)) >> 16) & 0xff)
#define TINYGL_COLOR_GET_GREEN(COLOR) ((((tiny_color_t)(COLOR)) >> 8) & 0xff)
#define TINYGL_COLOR_GET_BLUE(COLOR) ((((tiny_color_t)(COLOR))) & 0xff)

#define T

#endif // _TINYGL_COLOR_H