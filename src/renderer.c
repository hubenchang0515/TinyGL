#include <TinyGL/renderer.h>
#include <TinyGL/log.h>
#include <TinyGL/color.h>
#include <stdlib.h>

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
 * @note use `TinyGL_DestroyRenderer` to release renderer
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
