#version 330

uniform mat4 uModelViewProjectionMat;
uniform mat4 uPrevModelViewProjectionMat;

smooth out vec4 vPosition;
smooth out vec4 vPrevPosition;

void main(void) {
    vPosition = uModelViewProjectionMat * gl_Vertex;
    vPrevPosition = uPrevModelViewProjectionMat * gl_Vertex;

    gl_Position = vPosition;
}
