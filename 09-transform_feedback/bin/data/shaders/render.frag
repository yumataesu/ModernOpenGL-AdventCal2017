#version 400 core

uniform float u_time;

in vec3 v_color;
in float v_lifetime;

out vec4 outputColor;


void main() {
    
    outputColor = vec4(v_color, 1.0);
}
