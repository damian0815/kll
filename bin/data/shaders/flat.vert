
#version 150

in vec4 position;
uniform mat4 modelViewProjectionMatrix;

void main()
{
    vec4 pos = modelViewProjectionMatrix * position;
    gl_Position = pos;
}
