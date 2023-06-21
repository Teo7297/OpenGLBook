#version 330 core

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};


struct DirectionalLight
{
    vec3 direction;

    vec3 ambientStrength;
    vec3 diffuseStrength;
    vec3 specularStrength;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;

    vec3 ambientStrength;
    vec3 diffuseStrength;
    vec3 specularStrength;

    // Attenuation values
    float constant;
    float linear;
    float quadratic;

    // Spotlight
    float cutOff;
    float outerCutOff;
};

struct PointLights
{
    //vec3 position;
    vec3[10] position;
    int amount;

    vec3 ambientStrength;
    vec3 diffuseStrength;
    vec3 specularStrength;

    // Attenuation values
    float constant;
    float linear;
    float quadratic;

    vec3 color;
};



out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;
in vec2 TexCoords;
  
uniform Material material;
uniform DirectionalLight directional_light;
uniform SpotLight spot_light;
uniform PointLights point_lights;

uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

vec3 norm;

vec3 computeDirectionalLight()
{
    // ambient
    vec3 ambient = directional_light.ambientStrength * vec3(texture(material.diffuse, TexCoords));
    
    // diffused
    vec3 lightDir = normalize(-directional_light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = directional_light.diffuseStrength * ( diff * vec3(texture(material.diffuse, TexCoords)) );
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = directional_light.specularStrength * ( spec * vec3(texture(material.specular, TexCoords)) );


    return (ambient + diffuse + specular);
    //return vec3(0);
}

vec3 computeSpotLight()
{
    // ambient
    vec3 ambient = spot_light.ambientStrength * vec3(texture(material.diffuse, TexCoords));
    
    // diffused
    vec3 lightDir = normalize(-spot_light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = spot_light.diffuseStrength * ( diff * vec3(texture(material.diffuse, TexCoords)) );
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spot_light.specularStrength * ( spec * vec3(texture(material.specular, TexCoords)) );

    // Attenuation
    float distance = length(spot_light.position - FragPos);
    float attenuation = 1.0 / (spot_light.constant + spot_light.linear * distance + spot_light.quadratic * (distance * distance));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    // Spotlight
    float theta = dot(normalize(spot_light.position - FragPos), lightDir);
    float epsilon = spot_light.cutOff - spot_light.outerCutOff;
    float intensity = clamp((theta - spot_light.outerCutOff) / epsilon, 0.0, 1.0);

    diffuse *= intensity;
    specular *= intensity;
    ambient *= intensity;

    //if(dot(Normal, lightDir) < 0.f)
    //{
    //    diffuse = vec3(0.f);
    //    specular = vec3(0.f);
    //}
    return (ambient + diffuse + specular);
    //return vec3(0);

}

vec3 computePointLights()
{
    vec3 result = vec3(0.f);

    int amount = point_lights.amount;

    for(int i = 0; i < point_lights.amount; i++)
    {
        vec3 pos = point_lights.position[i];
        //vec3 pos = point_lights.position;
        
        // ambient
        vec3 ambient = point_lights.ambientStrength * vec3(texture(material.diffuse, TexCoords));
    
        // diffused
        vec3 lightDir = normalize(pos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = point_lights.diffuseStrength * ( diff * vec3(texture(material.diffuse, TexCoords)) );
    
        // specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = point_lights.specularStrength * ( spec * vec3(texture(material.specular, TexCoords)) );

        // Attenuation
        float distance = length(pos - FragPos);
        float attenuation = 1.0 / (point_lights.constant + point_lights.linear * distance + point_lights.quadratic * (distance * distance));
        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;

        result += (ambient + diffuse + specular) * point_lights.color;
    } 
   return result;
}



void main()
{
    norm = normalize(Normal);
    vec3 result = (computeSpotLight() + computePointLights() + computeDirectionalLight());
    result.x = min(result.x, 1.f);   
    result.y = min(result.y, 1.f);   
    result.z = min(result.z, 1.f);  
    
    FragColor = vec4(result * objectColor, 1.f);

} 
