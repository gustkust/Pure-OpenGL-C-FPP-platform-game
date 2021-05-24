#version 330 core

out vec4 FragColor;


// position of colored fragment
in vec3 FragPos;
// normal vector (perpendicular to the vertex surface)
in vec3 Normal;
// texture coordinates of fragment
in vec2 TexCoords;

// light sources positions
uniform vec3 position[40];
// position of the camera
uniform vec3 viewPos;
// ambient light color
uniform vec3 amb;
uniform sampler2D value;


void main() {    
    // properties
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // ambient calculation - ambient light color (we use grey) times texture color
    vec3 result = amb * vec3(texture(value, TexCoords));

    // lights calculations
    for(int i = 0; i < 40; i++) {
        vec3 baseDiffuse = vec3(1.0f, 1.0f, 1.0f);
        vec3 baseSpecular = vec3(1.0f, 1.0f, 1.0f);

        vec3 lightDir = normalize(position[i] - FragPos);
        // diffuse shading
        float diff = max(dot(normal, lightDir), 0.0);
        // specular shading
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 40.0f);
        // attenuation
        float distance = length(position[i] - FragPos);
        float attenuation = 1.0 / (1.0f + 0.018f * distance + 0.001f * (distance * distance));    
        // combine results
        vec3 diffuse = baseDiffuse * diff * vec3(texture(value, TexCoords));
        vec3 specular = baseSpecular * spec * vec3(texture(value, TexCoords));
        diffuse *= attenuation;
        specular *= attenuation;

        result += diffuse + specular;
    }    
    
    FragColor = vec4(result, 1.0);
}