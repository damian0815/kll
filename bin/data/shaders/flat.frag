
#version 330

uniform sampler2D src_tex_unit0;

uniform vec4 globalColor;

in vec2 texCoord;

out vec4 fragColor;

void main() {

    float w = 1;
    fragColor = vec4(w,w,w,globalColor.a);
}

