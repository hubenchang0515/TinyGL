#include <TinyGL/shader.h>
#include <TinyGL/log.h>
#include <glad/gles2.h>

static inline int TINYGL_SHADER_TYPE_TO_GLES(tiny_shadertype_t type)
{
    switch (type)
    {
    case TINYGL_VERTEX_SHADER: return GL_VERTEX_SHADER;
    case TINYGL_FRAGMENT_SHADER: return GL_FRAGMENT_SHADER;
    }

    return 0;
}

/*********************************************************************************
 * @brief create a shader
 * @param type shader type, `TINYGL_VERTEX_SHADER` or `TINYGL_FRAGMENT_SHADER`
 * @param source shader source
 * @param len length of shader source
 * @return created shader, 0 means failed
 * @note use `TinyGL_DestroyShader` to release shader
 ********************************************************************************/
unsigned int TinyGL_CreateShader(tiny_shadertype_t type, const char* source, int len)
{
    unsigned int shader = glCreateShader(TINYGL_SHADER_TYPE_TO_GLES(type));
    glShaderSource(shader, 1, &source, &len);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char info[TINYGL_MSG_LEN];
        glGetShaderInfoLog(shader, TINYGL_MSG_LEN, NULL, info);
        TINYGL_LOG_ERROR("%s\n", info);

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

/*********************************************************************************
 * @brief destroy a shader
 * @param shader shader to destroy
 ********************************************************************************/
void TinyGL_DestroyShader(unsigned int shader)
{
    glDeleteShader(shader);
}

/*********************************************************************************
 * @brief create a shader program and use it
 * @param vertexShader vertex shader
 * @param fragmentShader fragment shader
 * @return created shader, 0 means failed
 * @note use `TinyGL_DestroyShaderProgram` to release shader program
 ********************************************************************************/
unsigned int TinyGL_CreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char info[TINYGL_MSG_LEN];
        glGetProgramInfoLog(program, TINYGL_MSG_LEN, NULL, info);
        TINYGL_LOG_ERROR("%s\n", info);

        glDeleteProgram(program);
        return 0;
    }

    glUseProgram(program);
    return program;
}

/*********************************************************************************
 * @brief destroy a shader program
 * @param program shader program to destroy
 ********************************************************************************/
void TinyGL_DestroyShaderProgram(unsigned int program)
{
    glDeleteProgram(program);
}

/*********************************************************************************
 * @brief use a shader program
 * @param program shader program to use
 * @note `TinyGL_CreateShaderProgram` will auto use
 ********************************************************************************/
void TinyGL_UseShaderProgram(unsigned int program)
{
    glUseProgram(program);
}