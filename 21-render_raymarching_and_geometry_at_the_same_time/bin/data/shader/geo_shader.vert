#version 410

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform int isPolygon;

in vec3 position;
in vec2 texcoord;
in vec3 normal;

out vec4 v_world;
out vec2 v_texcoord;
out vec4 v_normal;

void main()
{
    v_texcoord = vec2(texcoord.x, texcoord.y);
    
    v_normal = transpose(inverse(modelViewMatrix)) * vec4(normal, 1.0);
    
    v_world = modelViewMatrix * vec4(position, 1.0);
    gl_Position = modelViewProjectionMatrix * vec4(position, 1.0);
}
