#version 410

uniform float u_time;
uniform vec2 u_resolution;
uniform mat4 view;
uniform mat4 viewMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat4 projection;
uniform vec3 u_camUp;
uniform float u_far;
uniform float u_near;
uniform float u_radius;

uniform float u_fov;
uniform vec3 u_camPos;

in vec4 v_world;
in vec2 v_texcoord;
in vec4 v_normal;

layout (location = 0) out vec4 gPosition;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gAlbedo;

#define PI 3.14159265359
#define DEG2RAD (PI/180.0)

const float sphereSize = 1.0;


const vec3 lightDir = vec3(-0.577, 0.577, 0.577);

vec3 trans(vec3 p){
    return mod(p, 4.0) - 2.0;
}

float distanceFunc(vec3 p){
    return length(trans(p)) - u_radius;
}

vec3 getNormal(vec3 p){
    float d = 0.0001;
    return normalize(vec3(
                          distanceFunc(p + vec3(  d, 0.0, 0.0)) - distanceFunc(p + vec3( -d, 0.0, 0.0)),
                          distanceFunc(p + vec3(0.0,   d, 0.0)) - distanceFunc(p + vec3(0.0,  -d, 0.0)),
                          distanceFunc(p + vec3(0.0, 0.0,   d)) - distanceFunc(p + vec3(0.0, 0.0,  -d))
                          ));
}

float compute_depth(vec4 clippos)
{
    return ((clippos.z / clippos.w) + 1.0) * 0.5;
}



void main()
{
    
    vec2 p = (gl_FragCoord.xy * 2.0 - u_resolution) / min(u_resolution.x, u_resolution.y);
    p.y = -p.y;
    
    // camera
    vec3 cPos = u_camPos;
    //cPos = vec3(0.0, 0.0, 42.0);
    //vec3 cDir = -view[2].xyz;
    vec3 cDir = -normalize(u_camPos);
    //vec3 cUp  = modelViewMatrix[1].xyz;
    vec3 cUp = u_camUp;
    vec3 cSide = cross(cDir, cUp);
    float targetDepth = 1.0 / tan(70 * 0.5 * DEG2RAD);

    
    vec3 ray = normalize(cSide * p.x + cUp * p.y + cDir * targetDepth);
    
    // marching loop
    float distance = 0.0;
    float rLen = 0.0;
    vec3  rPos = cPos;
    for(int i = 0; i < 64; i++){
        distance = distanceFunc(rPos);
        rLen += distance;
        rPos = cPos + ray * rLen;
    }
    

    vec3 normal = mat3(modelViewMatrix) * getNormal(rPos);
    
    
    // hit check
    gNormal = vec4(0.1, 1.0, 1.0, 1.0);
    if(abs(distance) < 0.01)
    {
        
        vec4 world = modelViewMatrix * vec4(rPos, 1.0);
        gPosition = vec4(world.xyz, 1.0);
        gNormal = vec4(normal.rgb, 1.0);
        gAlbedo = vec4(0.3, 0.9, 0.6, 1.0);
        
        
        float d = compute_depth((modelViewProjectionMatrix * vec4(rPos, 1.0)));

        float zc = (modelViewProjectionMatrix * vec4(rPos, 1.0)).z;
        float wc = (modelViewProjectionMatrix* vec4(rPos, 1.0)).w;
        gl_FragDepth = d;

    } else {
        gPosition = vec4(0.0, 0.0, 0.0, 1.0);
        gNormal = vec4(vec3(0.0), 1.0);
        gAlbedo = vec4(0.0, 0.0, 0.0, 1.0);
        gl_FragDepth = 1.0;
    }
}
