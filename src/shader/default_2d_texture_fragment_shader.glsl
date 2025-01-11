#version 300 es

precision mediump float;
in vec4 vertexColor;
in vec2 textureCoord;
out vec4 fragmentColor;
uniform sampler2D inTexture;

void main()
{
    fragmentColor = texture(inTexture, textureCoord) * vertexColor/255.0;
}