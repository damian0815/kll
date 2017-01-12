#version 330

smooth in vec4 vPosition;
smooth in vec4 vPrevPosition;

out vec2 oVelocity;

void main() {
    vec2 a = (vPosition.xy / vPosition.w) * 0.5 + 0.5;
    vec2 b = (vPrevPosition.xy / vPosition.w) * 0.5 + 0.5;
    oVelocity = a - b;
}
