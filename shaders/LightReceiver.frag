#version 330 core

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light
{
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // Attenuation values
    float constant;
    float linear;
    float quadratic;

    // Spotlight
    float cutOff;
    float outerCutOff;
};

out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;
in vec2 TexCoords;
  
uniform Material material;
uniform Light light;

uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;



void main()
{
    // ambient
    //vec3 ambient = light.ambient * material.ambient;
  	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    // diffuse 
    vec3 norm = normalize(Normal);
    //vec3 pointLightDir = normalize(light.position - FragPos);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * ( diff * vec3(texture(material.diffuse, TexCoords)) );
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * ( spec * vec3(texture(material.specular, TexCoords)) );  
       
    // Attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    // Spotlight
    float theta = dot(normalize(light.position - FragPos), lightDir);
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    diffuse *= intensity;
    specular *= intensity;
    ambient *= intensity;

    if(dot(Normal, lightDir) > 0.f)
    {
        // do lighting calculations
        vec3 result = (ambient + diffuse + specular) * objectColor;
        FragColor = vec4(result, 1.0);
    }
    else
    {
        vec3 result = (ambient) * objectColor;
        //FragColor = vec4(result, 1.0);
        FragColor = vec4(0.f, 0.f, 0.f, 1.f);
    }

} 
