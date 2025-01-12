#include <TinyGL/renderer.h>
#include <TinyGL/log.h>
#include <TinyGL/shader.h>
#include <TinyGL/buffer.h>
#include <TinyGL/vertex_array.h>
#include <glad/gles2.h>
#include <stdlib.h>

#include "shader/default_2d_vertex_shader.c"
#include "shader/default_2d_fragment_shader.c"
#include "shader/default_2d_texture_vertex_shader.c"
#include "shader/default_2d_texture_fragment_shader.c"

static GLuint TINYGL_DEFAULT_VERTEX_SHADER = 0;
static GLuint TINYGL_DEFAULT_FRAGMENT_SHADER = 0;
static GLuint TINYGL_DEFAULT_SHADER_PROGRAME = 0;
static GLuint TINYGL_DEFAULT_VERTEX_BUFFER = 0;
static GLuint TINYGL_DEFAULT_VERTEX_ARRAY = 0;
static GLuint TINYGL_DEFAULT_INDEX_BUFFER = 0;

static void TinyGL_InitDefaultShader()
{
    if (TINYGL_DEFAULT_VERTEX_SHADER == 0)
    {
        TINYGL_DEFAULT_VERTEX_SHADER = TinyGL_CreateShader(TINYGL_VERTEX_SHADER, (const char*)default_2d_vertex_shader_glsl, default_2d_vertex_shader_glsl_len);
        TINYGL_LOG_DEBUG("TINYGL_DEFAULT_VERTEX_SHADER: %u\n", TINYGL_DEFAULT_VERTEX_SHADER);
    }
    
    if (TINYGL_DEFAULT_FRAGMENT_SHADER == 0)
    {
        TINYGL_DEFAULT_FRAGMENT_SHADER = TinyGL_CreateShader(TINYGL_FRAGMENT_SHADER, (const char*)default_2d_fragment_shader_glsl, default_2d_fragment_shader_glsl_len);
        TINYGL_LOG_DEBUG("TINYGL_DEFAULT_FRAGMENT_SHADER: %u\n", TINYGL_DEFAULT_FRAGMENT_SHADER);
    }
    
    if (TINYGL_DEFAULT_SHADER_PROGRAME == 0)
    {
        TINYGL_DEFAULT_SHADER_PROGRAME = TinyGL_CreateShaderProgram(TINYGL_DEFAULT_VERTEX_SHADER, TINYGL_DEFAULT_FRAGMENT_SHADER);
        TINYGL_LOG_DEBUG("TINYGL_DEFAULT_SHADER_PROGRAME: %u\n", TINYGL_DEFAULT_SHADER_PROGRAME);
    }

    if (TINYGL_DEFAULT_VERTEX_BUFFER == 0)
    {
        TINYGL_DEFAULT_VERTEX_BUFFER = TinyGL_CreateBuffer();
        TINYGL_LOG_DEBUG("TINYGL_DEFAULT_VERTEX_BUFFER: %u\n", TINYGL_DEFAULT_VERTEX_BUFFER);
    }

    if (TINYGL_DEFAULT_VERTEX_ARRAY == 0)
    {
        TINYGL_DEFAULT_VERTEX_ARRAY = TinyGL_CreateVertexArray();
        TINYGL_LOG_DEBUG("TINYGL_DEFAULT_VERTEX_ARRAY: %u\n", TINYGL_DEFAULT_VERTEX_ARRAY);
        TinyGL_BindVertexArray(TINYGL_DEFAULT_VERTEX_ARRAY);
    }
    
    if (TINYGL_DEFAULT_INDEX_BUFFER == 0)
    {
        TINYGL_DEFAULT_INDEX_BUFFER = TinyGL_CreateBuffer();
        TINYGL_LOG_DEBUG("TINYGL_DEFAULT_INDEX_BUFFER: %u\n", TINYGL_DEFAULT_INDEX_BUFFER);
    }
}

/*********************************************************************************
 * @brief draw pixels
 * @param renderer renderer
 * @param n count of pixels
 * @param pixels position of pixels
 * @param colors color of pixels
 ********************************************************************************/
static void TinyGL_DefaultDrawPixels(unsigned int n, const tiny_pos_t* pixels, const tiny_color_t* colors)
{
    TinyGL_InitDefaultShader();
    const GLuint vsize = 6 * sizeof(GLfloat);
    const GLuint vbufsize = n * vsize;
    const GLuint ibufsize = n * sizeof(GLuint);
    GLfloat* vertices = malloc(vbufsize);
    GLuint* indices = malloc(n * sizeof(GLuint));
    for (GLuint i = 0; i < n; i++)
    {
        vertices[i*6] = (GLfloat)pixels[i].x;
        vertices[i*6 + 1] = (GLfloat)pixels[i].y;
        vertices[i*6 + 2] = (GLfloat)TINYGL_COLOR_GET_RED(colors[i]);
        vertices[i*6 + 3] = (GLfloat)TINYGL_COLOR_GET_GREEN(colors[i]);
        vertices[i*6 + 4] = (GLfloat)TINYGL_COLOR_GET_BLUE(colors[i]);
        vertices[i*6 + 5] = (GLfloat)TINYGL_COLOR_GET_ALPHA(colors[i]);

        indices[i] = i;
    }

    TinyGL_SetBufferData(TINYGL_ARRAY_BUFFER, TINYGL_DEFAULT_VERTEX_BUFFER, vbufsize, vertices, TINYGL_STREAM_DRAW);
    TinyGL_SetBufferData(TINYGL_ELEMENT_ARRAY_BUFFER, TINYGL_DEFAULT_INDEX_BUFFER, ibufsize, indices, TINYGL_STATIC_DRAW);

    TinyGL_VertexAttribPointer(TINYGL_DEFAULT_VERTEX_ARRAY, 0, 2, TINYGL_FLOAT, false, vsize, (void*)0);
    TinyGL_VertexAttribPointer(TINYGL_DEFAULT_VERTEX_ARRAY, 1, 4, TINYGL_FLOAT, false, vsize, (void*)(sizeof(float) * 2));

    GLfloat viewport[4];
    glGetFloatv(GL_VIEWPORT, viewport);
    GLint viewSize = glGetUniformLocation(TINYGL_DEFAULT_SHADER_PROGRAME, "viewSize");
    glUniform2f(viewSize, (GLfloat)viewport[2], (GLfloat)viewport[3]);

    glDrawElements(GL_POINTS, n, GL_UNSIGNED_INT, 0);
    free(vertices);
    free(indices);
}

/*********************************************************************************
 * @brief draw lines
 * @param renderer renderer
 * @param n count of pixels
 * @param pixels position of pixels
 * @param colors color of pixels
 ********************************************************************************/
static void TinyGL_DefaultDrawLines(unsigned int n, const tiny_pos_t* pixels, const tiny_color_t* colors)
{
    TinyGL_InitDefaultShader();
    const GLuint vsize = 6 * sizeof(GLfloat);
    const GLuint vbufsize = n * vsize;
    const GLuint ibufsize = n * sizeof(GLuint);
    GLfloat* vertices = malloc(vbufsize);
    GLuint* indices = malloc(n * sizeof(GLuint));
    for (GLuint i = 0; i < n; i++)
    {
        vertices[i*6] = (GLfloat)pixels[i].x;
        vertices[i*6 + 1] = (GLfloat)pixels[i].y;
        vertices[i*6 + 2] = (GLfloat)TINYGL_COLOR_GET_RED(colors[i]);
        vertices[i*6 + 3] = (GLfloat)TINYGL_COLOR_GET_GREEN(colors[i]);
        vertices[i*6 + 4] = (GLfloat)TINYGL_COLOR_GET_BLUE(colors[i]);
        vertices[i*6 + 5] = (GLfloat)TINYGL_COLOR_GET_ALPHA(colors[i]);

        indices[i] = i;
    }

    TinyGL_SetBufferData(TINYGL_ARRAY_BUFFER, TINYGL_DEFAULT_VERTEX_BUFFER, vbufsize, vertices, TINYGL_STREAM_DRAW);
    TinyGL_SetBufferData(TINYGL_ELEMENT_ARRAY_BUFFER, TINYGL_DEFAULT_INDEX_BUFFER, ibufsize, indices, TINYGL_STATIC_DRAW);

    TinyGL_VertexAttribPointer(TINYGL_DEFAULT_VERTEX_ARRAY, 0, 2, TINYGL_FLOAT, false, vsize, (void*)0);
    TinyGL_VertexAttribPointer(TINYGL_DEFAULT_VERTEX_ARRAY, 1, 4, TINYGL_FLOAT, false, vsize, (void*)(sizeof(float) * 2));

    GLfloat viewport[4];
    glGetFloatv(GL_VIEWPORT, viewport);
    GLint viewSize = glGetUniformLocation(TINYGL_DEFAULT_SHADER_PROGRAME, "viewSize");
    glUniform2f(viewSize, (GLfloat)viewport[2], (GLfloat)viewport[3]);

    glDrawElements(GL_LINES, n, GL_UNSIGNED_INT, 0);
    free(vertices);
    free(indices);
}

/*********************************************************************************
 * @brief draw triangles
 * @param renderer renderer
 * @param n count of pixels
 * @param pixels position of pixels
 * @param colors color of pixels
 ********************************************************************************/
static void TinyGL_DefaultDrawTriangles(unsigned int n, const tiny_pos_t* pixels, const tiny_color_t* colors)
{
    TinyGL_InitDefaultShader();
    const GLuint vsize = 6 * sizeof(GLfloat);
    const GLuint vbufsize = n * vsize;
    const GLuint ibufsize = n * sizeof(GLuint);
    GLfloat* vertices = malloc(vbufsize);
    GLuint* indices = malloc(n * sizeof(GLuint));
    for (GLuint i = 0; i < n; i++)
    {
        vertices[i*6] = (GLfloat)pixels[i].x;
        vertices[i*6 + 1] = (GLfloat)pixels[i].y;
        vertices[i*6 + 2] = (GLfloat)TINYGL_COLOR_GET_RED(colors[i]);
        vertices[i*6 + 3] = (GLfloat)TINYGL_COLOR_GET_GREEN(colors[i]);
        vertices[i*6 + 4] = (GLfloat)TINYGL_COLOR_GET_BLUE(colors[i]);
        vertices[i*6 + 5] = (GLfloat)TINYGL_COLOR_GET_ALPHA(colors[i]);

        indices[i] = i;
    }

    TinyGL_SetBufferData(TINYGL_ARRAY_BUFFER, TINYGL_DEFAULT_VERTEX_BUFFER, vbufsize, vertices, TINYGL_STREAM_DRAW);
    TinyGL_SetBufferData(TINYGL_ELEMENT_ARRAY_BUFFER, TINYGL_DEFAULT_INDEX_BUFFER, ibufsize, indices, TINYGL_STATIC_DRAW);

    TinyGL_VertexAttribPointer(TINYGL_DEFAULT_VERTEX_ARRAY, 0, 2, TINYGL_FLOAT, false, vsize, (void*)0);
    TinyGL_VertexAttribPointer(TINYGL_DEFAULT_VERTEX_ARRAY, 1, 4, TINYGL_FLOAT, false, vsize, (void*)(sizeof(float) * 2));

    GLfloat viewport[4];
    glGetFloatv(GL_VIEWPORT, viewport);
    GLint viewSize = glGetUniformLocation(TINYGL_DEFAULT_SHADER_PROGRAME, "viewSize");
    glUniform2f(viewSize, (GLfloat)viewport[2], (GLfloat)viewport[3]);

    glDrawElements(GL_TRIANGLES, n, GL_UNSIGNED_INT, 0);
    free(vertices);
    free(indices);
}

/*********************************************************************************
 * @brief create a renderer by dedefault 2D
 * @return created renderer 
 * @note use `TinyGL_DestroyRenderer` to release renderer
 ********************************************************************************/
tiny_renderer_t TinyGL_CreateDefault2DRenderer()
{
    return TinyGL_CreateRenderer(TinyGL_DefaultDrawPixels, TinyGL_DefaultDrawLines, TinyGL_DefaultDrawTriangles);
}