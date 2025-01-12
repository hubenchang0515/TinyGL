#ifndef _TINYGL_SHADER_H
#define _TINYGL_SHADER_H

#include "base.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum TinyGL_ShaderType tiny_shadertype_t;

enum TinyGL_ShaderType
{
    TINYGL_VERTEX_SHADER = 1,
    // TINYGL_GEOMETRY_SHADER,
    TINYGL_FRAGMENT_SHADER,
};


/*********************************************************************************
 * @brief create a shader
 * @param type shader type, `TINYGL_VERTEX_SHADER` or `TINYGL_FRAGMENT_SHADER`
 * @param source shader source
 * @param len length of shader source
 * @return created shader, 0 means failed
 * @note use `TinyGL_DestroyShader` to release shader
 ********************************************************************************/
unsigned int TinyGL_CreateShader(tiny_shadertype_t type, const char* source, int len);

/*********************************************************************************
 * @brief destroy a shader
 * @param shader shader to destroy
 ********************************************************************************/
void TinyGL_DestroyShader(unsigned int shader);

/*********************************************************************************
 * @brief create a shader program
 * @param vertexShader vertex shader
 * @param fragmentShader fragment shader
 * @return created shader, 0 means failed
 * @note use `TinyGL_DestroyShaderProgram` to release shader program
 ********************************************************************************/
unsigned int TinyGL_CreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);

/*********************************************************************************
 * @brief destroy a shader program
 * @param program shader program to destroy
 ********************************************************************************/
void TinyGL_DestroyShaderProgram(unsigned int program);

/*********************************************************************************
 * @brief use a shader program
 * @param program shader program to use
 * @note `TinyGL_CreateShaderProgram` will auto use
 ********************************************************************************/
void TinyGL_UseShaderProgram(unsigned int program);

#ifdef __cplusplus
}; // extern "C"
#endif

#endif // _TINYGL_SHADER_H