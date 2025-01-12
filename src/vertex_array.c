#include <TinyGL/vertex_array.h>
#include <glad/gles2.h>

static inline int TINYGL_DATA_TYPE_TO_GLES(tiny_datatype_t type)
{
    switch (type)
    {
    case TINYGL_BYTE: return GL_BYTE;
    case TINYGL_UBYTE: return GL_UNSIGNED_BYTE;
    case TINYGL_SHORT: return GL_SHORT;
    case TINYGL_USHORT: return GL_UNSIGNED_SHORT;
    case TINYGL_INT: return GL_INT;
    case TINYGL_UINT: return GL_UNSIGNED_INT;
    case TINYGL_FLOAT: return GL_FLOAT;
    }

    return 0;
}

/*********************************************************************************
 * @brief create a vertex array
 * @return created vertex array, 0 means failed
 * @note use `TinyGL_DestroyVertexArray` to release vertex array
 ********************************************************************************/
unsigned int TinyGL_CreateVertexArray()
{
    unsigned int vertexArray;
    glGenVertexArrays(1, &vertexArray);
    return vertexArray;
}

/*********************************************************************************
 * @brief destroy a vertex array
 * @param array vertex array to destroy
 ********************************************************************************/
void TinyGL_DestroyVertexArray(unsigned int array)
{
    glDeleteVertexArrays(1, &array);
}

/*********************************************************************************
 * @brief bind a vertex array
 * @param array vertex array to bind
 ********************************************************************************/
void TinyGL_BindVertexArray(unsigned int array)
{
    glBindVertexArray(array);
}

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
void TinyGL_VertexAttribPointer(unsigned int array, unsigned int index, int size, tiny_datatype_t type, bool normalized, int stride, const void* pointer)
{
    glBindVertexArray(array);
    glVertexAttribPointer(index, size, TINYGL_DATA_TYPE_TO_GLES(type), (GLboolean)normalized, stride, pointer);
    glEnableVertexAttribArray(index);   
}