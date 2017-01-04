
#version 150

uniform sampler2D src_tex_unit0;

uniform vec4 globalColor;
out vec4 fragColor;

void main() {
    vec4 c = globalColor;
    c.b = 0;
    c.g = 1;
    fragColor = c;
}
