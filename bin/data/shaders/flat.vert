
#version 330

in vec4 position;
layout (location=3) in vec2 texCoordIn;

uniform mat4 modelViewProjectionMatrix;

out vec2 texCoord;

void main()
{
    vec4 pos = modelViewProjectionMatrix * position;
    gl_Position = pos;

    texCoord = texCoordIn;
}
