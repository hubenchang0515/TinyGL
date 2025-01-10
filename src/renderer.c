#include <TinyGL/renderer.h>
#include <TinyGL/log.h>
#include <TinyGL/color.h>
#include <glad/gles2.h>
#include <stdlib.h>

static const char* TINYGL_DEFAULT_VERTEX_SHADER_SOURCE = 
    "#version 300 es\n"
    "layout (location = 0) in vec2 inPos;\n"
    "layout (location = 1) in vec4 inColor;\n"
    "uniform vec2 viewSize;\n"
    "out vec4 vertexColor;\n"
    "void main()\n"
    "{\n"
    "   gl_PointSize = 1.0;\n"
    "   gl_Position = vec4(inPos[0]/viewSize[0]*2.0 - 1.0, 1.0 - inPos[1]/viewSize[1]*2.0, 1.0, 1.0);\n"
    "   vertexColor = inColor;\n"
    "}\n";

static const char* TINYGL_DEFAULT_FRAGMENT_SHADER_SOURCE = 
    "#version 300 es\n"
    "precision mediump float;\n"
    "in vec4 vertexColor;\n"
    "out vec4 fragmentColor;\n"
    "void main()\n"
    "{\n"
    "   fragmentColor = vertexColor/255.0;\n"
    "}\n";


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
        TINYGL_DEFAULT_VERTEX_SHADER = glCreateShader(GL_VERTEX_SHADER);
        TINYGL_LOG_DEBUG("TINYGL_DEFAULT_VERTEX_SHADER: %u\n", TINYGL_DEFAULT_VERTEX_SHADER);
        glShaderSource(TINYGL_DEFAULT_VERTEX_SHADER, 1, &TINYGL_DEFAULT_VERTEX_SHADER_SOURCE, NULL);
        glCompileShader(TINYGL_DEFAULT_VERTEX_SHADER);

        int success;
        glGetShaderiv(TINYGL_DEFAULT_VERTEX_SHADER, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char info[1024];
            glGetShaderInfoLog(TINYGL_DEFAULT_VERTEX_SHADER, 1024, NULL, info);
            TINYGL_LOG_ERROR("%s\n", info);
        }
    }
    
    if (TINYGL_DEFAULT_FRAGMENT_SHADER == 0)
    {
        TINYGL_DEFAULT_FRAGMENT_SHADER = glCreateShader(GL_FRAGMENT_SHADER);
        TINYGL_LOG_DEBUG("TINYGL_DEFAULT_FRAGMENT_SHADER: %u\n", TINYGL_DEFAULT_FRAGMENT_SHADER);
        glShaderSource(TINYGL_DEFAULT_FRAGMENT_SHADER, 1, &TINYGL_DEFAULT_FRAGMENT_SHADER_SOURCE, NULL);
        glCompileShader(TINYGL_DEFAULT_FRAGMENT_SHADER);

        int success;
        glGetShaderiv(TINYGL_DEFAULT_FRAGMENT_SHADER, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char info[1024];
            glGetShaderInfoLog(TINYGL_DEFAULT_FRAGMENT_SHADER, 1024, NULL, info);
            TINYGL_LOG_ERROR("%s\n", info);
        }
    }
    
    if (TINYGL_DEFAULT_SHADER_PROGRAME == 0)
    {
        TINYGL_DEFAULT_SHADER_PROGRAME = glCreateProgram();
        TINYGL_LOG_DEBUG("TINYGL_DEFAULT_SHADER_PROGRAME: %u\n", TINYGL_DEFAULT_SHADER_PROGRAME);
        glAttachShader(TINYGL_DEFAULT_SHADER_PROGRAME, TINYGL_DEFAULT_VERTEX_SHADER);
        glAttachShader(TINYGL_DEFAULT_SHADER_PROGRAME, TINYGL_DEFAULT_FRAGMENT_SHADER);
        glLinkProgram(TINYGL_DEFAULT_SHADER_PROGRAME);

        int success;
        glGetProgramiv(TINYGL_DEFAULT_SHADER_PROGRAME, GL_LINK_STATUS, &success);
        if (!success) {
            char info[1024];
            glGetProgramInfoLog(TINYGL_DEFAULT_SHADER_PROGRAME, 1024, NULL, info);
            TINYGL_LOG_ERROR("%s\n", info);
        }
        glUseProgram(TINYGL_DEFAULT_SHADER_PROGRAME);
    }

    if (TINYGL_DEFAULT_VERTEX_BUFFER == 0)
    {
        glGenBuffers(1, &TINYGL_DEFAULT_VERTEX_BUFFER);
        TINYGL_LOG_DEBUG("TINYGL_DEFAULT_VERTEX_BUFFER: %u\n", TINYGL_DEFAULT_VERTEX_BUFFER);
        glBindBuffer(GL_ARRAY_BUFFER, TINYGL_DEFAULT_VERTEX_BUFFER);
    }

    if (TINYGL_DEFAULT_VERTEX_ARRAY == 0)
    {
        glGenVertexArrays(1, &TINYGL_DEFAULT_VERTEX_ARRAY);
        TINYGL_LOG_DEBUG("TINYGL_DEFAULT_VERTEX_ARRAY: %u\n", TINYGL_DEFAULT_VERTEX_ARRAY);
        glBindVertexArray(TINYGL_DEFAULT_VERTEX_ARRAY);
    }
    
    if (TINYGL_DEFAULT_INDEX_BUFFER == 0)
    {
        glGenBuffers(1, &TINYGL_DEFAULT_INDEX_BUFFER);
        TINYGL_LOG_DEBUG("TINYGL_DEFAULT_INDEX_BUFFER: %u\n", TINYGL_DEFAULT_INDEX_BUFFER);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, TINYGL_DEFAULT_INDEX_BUFFER);
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

    glBufferData(GL_ARRAY_BUFFER, vbufsize, vertices, GL_STREAM_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibufsize, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, false, vsize, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, false, vsize, (void*)(sizeof(float) * 2));
    glEnableVertexAttribArray(1);

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

    glBufferData(GL_ARRAY_BUFFER, vbufsize, vertices, GL_STREAM_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibufsize, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, false, vsize, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, false, vsize, (void*)(sizeof(float) * 2));
    glEnableVertexAttribArray(1);

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

    glBufferData(GL_ARRAY_BUFFER, vbufsize, vertices, GL_STREAM_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibufsize, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, false, vsize, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, false, vsize, (void*)(sizeof(float) * 2));
    glEnableVertexAttribArray(1);

    GLfloat viewport[4];
    glGetFloatv(GL_VIEWPORT, viewport);
    GLint viewSize = glGetUniformLocation(TINYGL_DEFAULT_SHADER_PROGRAME, "viewSize");
    glUniform2f(viewSize, (GLfloat)viewport[2], (GLfloat)viewport[3]);

    glDrawElements(GL_TRIANGLES, n, GL_UNSIGNED_INT, 0);
    free(vertices);
    free(indices);
}

struct TinyGL_Renderer
{
    tiny_drawpixels_func* drawPixels;
    tiny_drawlines_func* drawLines;
    tiny_drawtriangles_func* drawTriangles;
};

/*********************************************************************************
 * @brief create a renderer
 * @param drawPixel function to draw pixel
 * @param drawLine function to draw line
 * @param drawTriangle function to draw triangle
 * @return created renderer
 * @note use `TinyGL_DestroyRenderer` to release window
 ********************************************************************************/
tiny_renderer_t TinyGL_CreateRenderer(tiny_drawpixels_func* drawPixels, 
                                        tiny_drawlines_func* drawLines, 
                                        tiny_drawtriangles_func* drawTriangles)
{
    tiny_renderer_t renderer = malloc(sizeof(struct TinyGL_Renderer));
    renderer->drawPixels = drawPixels;
    renderer->drawLines = drawLines;
    renderer->drawTriangles = drawTriangles;
    return renderer;
}

/*********************************************************************************
 * @brief create a renderer by dedefault
 * @return created renderer 
 * @note use `TinyGL_DestroyRenderer` to release window
 ********************************************************************************/
tiny_renderer_t TinyGL_CreateDefaultRenderer()
{
    return TinyGL_CreateRenderer(TinyGL_DefaultDrawPixels, TinyGL_DefaultDrawLines, TinyGL_DefaultDrawTriangles);
}

/*********************************************************************************
 * @brief destroy a renderer
 * @param renderer renderer to destroy
 * @note null unsafe
 ********************************************************************************/
void TinyGL_DestroyRenderer(tiny_renderer_t renderer)
{
    free(renderer);
}

/*********************************************************************************
 * @brief draw pixels
 * @param renderer renderer
 * @param n count of pixels
 * @param pixels position of pixels
 * @param colors color of pixels
 ********************************************************************************/
void TinyGL_DrawPixels(tiny_renderer_t renderer, unsigned int n, const tiny_pos_t* pixels, const tiny_color_t* colors)
{
    renderer->drawPixels(n, pixels, colors);
}

/*********************************************************************************
 * @brief draw lines
 * @param renderer renderer
 * @param n count of pixels
 * @param pixels position of pixels
 * @param colors color of pixels
 ********************************************************************************/
void TinyGL_DrawLines(tiny_renderer_t renderer, unsigned int n, const tiny_pos_t* pixels, const tiny_color_t* colors)
{
    renderer->drawLines(n, pixels, colors);
}

/*********************************************************************************
 * @brief draw triangles
 * @param renderer renderer
 * @param n count of pixels
 * @param pixels position of pixels
 * @param colors color of pixels
 ********************************************************************************/
void TinyGL_DrawTriangles(tiny_renderer_t renderer, unsigned int n, const tiny_pos_t* pixels, const tiny_color_t* colors)
{
    renderer->drawTriangles(n, pixels, colors);
}
