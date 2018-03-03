#version 410

uniform mat4 modelViewProjectionMatrix;

layout(location = 0) in vec3 particle_vert;
layout(location = 1) in vec3 pos;
layout(location = 2) in vec4 color;

out vec4 v_color;

void main()
{
    v_color = color;
    
    mat4 matrix = mat4(1.0, 0.0, 0.0, 0.0,
                       0.0, 1.0, 0.0, 0.0,
                       0.0, 0.0, 1.0, 0.0,
                       pos.x, pos.y, pos.z, 1.0);
    
    gl_Position = modelViewProjectionMatrix * matrix * vec4(particle_vert, 1.0);
}
