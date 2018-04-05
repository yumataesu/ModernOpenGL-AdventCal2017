#version 400 core

uniform mat4 modelViewProjectionMatrix;

layout (location = 0) in vec3 in_position;
layout (location = 3) in float in_lifetime;
layout (location = 4) in vec3 in_color;

out vec3 v_color;
out float v_lifetime;

void main() {
    gl_Position = modelViewProjectionMatrix * vec4(in_position, 1.0);
    v_color = in_color;
    v_lifetime = in_lifetime;
    gl_PointSize = 1.0;
}
