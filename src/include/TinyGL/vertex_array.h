#ifndef _TINYGL_VERTEX_ARRAY_H
#define _TINYGL_VERTEX_ARRAY_H

#include "base.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************************
 * @brief create a vertex array
 * @return created vertex array, 0 means failed
 * @note use `TinyGL_DestroyVertexArray` to release vertex array
 ********************************************************************************/
unsigned int TinyGL_CreateVertexArray();

/*********************************************************************************
 * @brief destroy a vertex array
 * @param array vertex array to destroy
 ********************************************************************************/
void TinyGL_DestroyVertexArray(unsigned int array);

/*********************************************************************************
 * @brief bind a vertex array
 * @param array vertex array to bind
 ********************************************************************************/
void TinyGL_BindVertexArray(unsigned int array);

/*********************************************************************************
 * @brief define vertex attribute array in vertex array
 * @param array vertex array to define vertex attribute array
 * @param index index of vertex attribute in GLSL
 * @param size size of vertex attribute element, must be 1, 2, 3, 4
 * @param type type of vertex attribute element
 * @param normalized whether fixed-point data values should be normalized 
 * @param stride offset between consecutive vertex attributes
 * @param pointer offset of the first component of the first vertex attribute
 ********************************************************************************/
void TinyGL_VertexAttribPointer(unsigned int array, unsigned int index, int size, tiny_datatype_t type, bool normalized, int stride, const void* pointer);

#ifdef __cplusplus
}; // extern "C"
#endif


#endif // _TINYGL_VERTEX_ARRAY_H