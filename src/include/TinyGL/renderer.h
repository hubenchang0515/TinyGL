#ifndef _TINYGL_RENDERER_H
#define _TINYGL_RENDERER_H

#include "base.h"
#include "color.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TinyGL_Renderer* tiny_renderer_t;

/*********************************************************************************
 * @brief draw pixels
 * @param n count of pixels
 * @param pixels position of pixels
 * @param colors color of pixels
 ********************************************************************************/
typedef void (tiny_drawpixels_func)(unsigned int n, const tiny_pos_t* pixels, const tiny_color_t* colors);

/*********************************************************************************
 * @brief draw lines
 * @param n count of pixels
 * @param pixels position of pixels
 * @param colors color of pixels
 ********************************************************************************/
typedef void (tiny_drawlines_func)(unsigned int n, const tiny_pos_t* pixels, const tiny_color_t* colors);

/*********************************************************************************
 * @brief draw triangles
 * @param n count of pixels
 * @param pixels position of pixels
 * @param colors color of pixels
 ********************************************************************************/
typedef void (tiny_drawtriangles_func)(unsigned int n, const tiny_pos_t* pixels, const tiny_color_t* colors);

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
                                        tiny_drawtriangles_func* drawTriangles);

/*********************************************************************************
 * @brief create a renderer by default 2D
 * @return created renderer 
 * @note use `TinyGL_DestroyRenderer` to release renderer
 ********************************************************************************/
tiny_renderer_t TinyGL_CreateDefault2DRenderer();

/*********************************************************************************
 * @brief destroy a renderer
 * @param renderer renderer to destroy
 * @note null unsafe
 ********************************************************************************/
void TinyGL_DestroyRenderer(tiny_renderer_t renderer);

/*********************************************************************************
 * @brief draw pixels
 * @param renderer renderer
 * @param n count of pixels
 * @param pixels position of pixels
 * @param colors color of pixels
 ********************************************************************************/
void TinyGL_DrawPixels(tiny_renderer_t renderer, unsigned int n, const tiny_pos_t* pixels, const tiny_color_t* colors);

/*********************************************************************************
 * @brief draw lines
 * @param renderer renderer
 * @param n count of pixels
 * @param pixels position of pixels
 * @param colors color of pixels
 ********************************************************************************/
void TinyGL_DrawLines(tiny_renderer_t renderer, unsigned int n, const tiny_pos_t* pixels, const tiny_color_t* colors);

/*********************************************************************************
 * @brief draw triangles
 * @param renderer renderer
 * @param n count of pixels
 * @param pixels position of pixels
 * @param colors color of pixels
 ********************************************************************************/
void TinyGL_DrawTriangles(tiny_renderer_t renderer, unsigned int n, const tiny_pos_t* pixels, const tiny_color_t* colors);

#ifdef __cplusplus
}; // extern "C" {
#endif

#endif // _TINYGL_RENDERER_H