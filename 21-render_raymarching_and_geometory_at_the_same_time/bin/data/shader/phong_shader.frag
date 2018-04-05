#version 410 core

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;
uniform vec3 u_lightPos;
uniform vec3 viewPos;

uniform float constant;
uniform float linear;
uniform float quadratic;

uniform int DebugMode;


in vec2 v_texcoord;

out vec4 color;

void main() {
    vec3 position = texture(gPosition, v_texcoord).xyz;
    vec3 normal = texture(gNormal, v_texcoord).xyz;
    vec3 albedo = texture(gAlbedo, v_texcoord).rgb;
    
    
    vec3 lighting  = vec3(0.0, 0.0, 0.0);
    
        float distance = length(u_lightPos - position);
        if(distance < 900) {
            //Ambient
            vec3 ambient = albedo;
            
            //Diffuse
            vec3 lightDir = normalize(u_lightPos - position);
            vec3 diffuse = max(dot(normal, lightDir), 0.0) * vec3(0.8, 0.8, 0.8);
            
            //Specular
            vec3 viewDir  = normalize(viewPos - position);
            vec3 halfwayDir = normalize(lightDir + viewDir);
            float spec = pow(max(dot(normal, halfwayDir), 0.0), 16.0);
            vec3 specular = vec3(1.0, 1.0, 1.0) * spec;
            
            //Attenuation
            float dist = length(u_lightPos - position) * 1.0;
            float attenuation = 1.0 + (0.1 * dist) + (0.01 * dist * dist);
            
            ambient /= attenuation;
            diffuse /= attenuation;
            specular /= attenuation;
            lighting += ambient + diffuse + specular;
        }
    
    color = vec4(lighting, 1.0);
    
}
