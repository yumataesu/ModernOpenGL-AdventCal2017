#version 410

in vec3 position;
in vec2 texcoord;
in vec3 normal;

out vec4 v_world;
out vec2 v_texcoord;
out vec4 v_normal;

void main() {
    v_texcoord = vec2(texcoord.x, 1.0 - texcoord.y);
    gl_Position = vec4(position, 1.0);
}
