#version 410

uniform mat4 modelViewProjectionMatrix;

layout(location = 0) in vec3 particle_vert;
layout(location = 1) in vec4 color;
layout(location = 4) in vec3 pos;

out vec4 v_color;

void main()
{
    
    
    if(gl_InstanceID > 5000) {
        v_color = color;
    } else {
        v_color = vec4(1.0, 0.0, 0.0, 0.0);
    }
    
    mat4 matrix = mat4(1.0, 0.0, 0.0, 0.0,
                       0.0, 1.0, 0.0, 0.0,
                       0.0, 0.0, 1.0, 0.0,
                       pos.x, pos.y, pos.z, 1.0);
    
    gl_Position = modelViewProjectionMatrix * matrix * vec4(particle_vert, 1.0);
}
