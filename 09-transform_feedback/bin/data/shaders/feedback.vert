#version 400 core

uniform float u_time;
uniform float u_rand;

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_accel;
layout(location = 2) in vec3 in_velocity;
layout(location = 3) in float in_lifetime;
layout(location = 4) in vec3 in_color;

out vec3 v_position;
out vec3 v_accel;
out vec3 v_velocity;
out float v_lifetime;
out vec3 v_color;


void main() {
    vec3 position = in_position;
    vec3 accel = in_accel;
    vec3 velocity = in_velocity;
    float lifetime = in_lifetime;
    vec3 color = in_color;
    
    accel = normalize(vec3(140.0 * cos(u_time * 3.0), 5.0*sin(u_time), 90.0 * cos(u_time * 5.0)) - position);
    velocity += accel;
    position += velocity;
    //position.y += 1.3;
    
    if(lifetime < 0) {
        accel = vec3(0, 0, 0);
        position = vec3(20 * sin(u_time) * u_rand, 0, 20 * cos(u_time*2) * u_rand);
        velocity.xyz = normalize(velocity);
        lifetime = 100 * u_rand;
        color = vec3(0.5 + 0.5 * sin(u_time), 0.5 + 0.5 * cos(u_time), 0.0);
        
    }
    
    lifetime -= 0.1;
    
    v_position = position;
    v_accel = accel;
    v_velocity = velocity;
    v_lifetime = lifetime;
    v_color = color;
}
