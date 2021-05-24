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
uniform vec3 ambient;
uniform sampler2D value;


void main() {    
    // normalized normal vector (if not normalized already)
    vec3 normal = normalize(Normal);
    // view direction vector (from camera position to pixel/fragment position)
    vec3 viewDirection = normalize(viewPos - FragPos);
    
    // ambient calculation - ambient light color (we use grey) times texture color
    vec3 result = ambient * vec3(texture(value, TexCoords));

    // lights calculations
    for(int i = 0; i < 40; i++) {
        // base diffuse and specular light power (color)
        vec3 baseDiffusePower = vec3(1.0f, 1.0f, 1.0f);
        vec3 baseSpecularPower = vec3(1.0f, 1.0f, 1.0f);

        // light direction (from light source to target)
        vec3 lightDirection = normalize(position[i] - FragPos);
        // diffuse lighting power calculations - dot product between lightDirection and normal (perpendicular to the surface) vectors (the greater the angle the darker it is)
        // max because with angle > 90 it is/could be negative
        float diffusePower = max(dot(normal, lightDirection), 0.0);

        // reflect direction (from target to source)
        vec3 reflectDirection = reflect(-lightDirection, normal);
        // specilar lighting power is dot product between viewDirection and reflectDiretion to the power of shining (around 30-40 is optimal)
        float specularPower = pow(max(dot(viewDirection, reflectDirection), 0.0), 40.0f);

        // calculatining distance from the light source and attentuation (how less of a light should there be in a given distance from the source)
        float distance = length(position[i] - FragPos);
        // attentuation from formula (and parameter values from the table)
        float attenuation = 1.0 / (1.0f + 0.018f * distance + 0.001f * (distance * distance));
        
        // combining results - base power (color) times power (calculated dot product) times attentuation (> 1) times original color
        vec3 diffuse = baseDiffusePower * diffusePower * attenuation * vec3(texture(value, TexCoords));
        vec3 specular = baseSpecularPower * specularPower * attenuation * vec3(texture(value, TexCoords));

        // summing results
        result += diffuse + specular;
    }    
    
    FragColor = vec4(result, 1.0);
}