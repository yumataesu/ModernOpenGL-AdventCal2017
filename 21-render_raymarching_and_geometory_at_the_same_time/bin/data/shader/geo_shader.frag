#version 410

uniform mat4 view;
uniform mat4 viewMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 projection;
uniform int u_isLight;

in vec4 v_world;
in vec2 v_texcoord;
in vec4 v_normal;

layout (location = 0) out vec4 gPosition;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gAlbedo;


const float sphereSize = 1.0;

void main()
{
    gPosition = vec4(v_world.xyz, 1.0);
    gNormal = vec4(v_normal.xyz, 1.0);
    
    if(u_isLight == 1){
        gAlbedo = vec4(1.0, 1.0, 1.0, 1.0);
    } else {
        gAlbedo = vec4(0.8, 0.3, 0.3, 1.0);
    }
    
    
}
