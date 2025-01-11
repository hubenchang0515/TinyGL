#version 300 es

layout (location = 0) in vec2 inPos;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec2 inTextureCoord;
out vec4 vertexColor;
out vec2 textureCoord;
uniform vec2 viewSize;

void main()
{
    gl_PointSize = 1.0;
    gl_Position = vec4(inPos[0]/viewSize[0]*2.0 - 1.0, 1.0 - inPos[1]/viewSize[1]*2.0, 0.0, 1.0);
    vertexColor = inColor;
    textureCoord = inTextureCoord;
}
