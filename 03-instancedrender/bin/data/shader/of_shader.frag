#version 410

in vec4 v_color;

out vec4 fragColor;

void main() {
    fragColor = vec4(vec3(1.0) - v_color.rgb, 1.0);
}
