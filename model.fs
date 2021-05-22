#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


// position of colored fragment
in vec3 FragPos;
// normal vector (perpendicular to the vertex surface)
in vec3 Normal;
// texture coordinates of fragment
in vec2 TexCoords;


// position of the camera
uniform vec3 viewPos;
// ambient light color
uniform vec3 amb;
// point lights properties
uniform PointLight pointLights[40];
// material properties
uniform Material material;


// point light calculation funtion
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 100.0f);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

void main() {    
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // ambient calculation - ambient light color (we use grey) times texture color
    vec3 result = amb * vec3(texture(material.diffuse, TexCoords));

    // lights calculations
    for(int i = 0; i < 40; i++) {
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);  
    }    
    
    FragColor = vec4(result, 1.0);
}