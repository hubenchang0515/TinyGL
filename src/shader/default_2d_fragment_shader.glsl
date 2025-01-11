#version 300 es

precision mediump float;
in vec4 vertexColor;
out vec4 fragmentColor;

void main()
{
      fragmentColor = vertexColor/255.0;
}