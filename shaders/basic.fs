#version 330 core
out vec4 FragColor;

struct Light
{

    vec3 pos;
    vec3 color;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    bool hasAttenuation;

};

struct Material
{

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    bool hasAmbientTexture;
    bool hasDiffuseTexture;
    bool hasSpecularTexture;

    sampler2D AmbientTexture;
    sampler2D DiffuseTexture;
    sampler2D SpecularTexture;

    float shininess;

};

uniform Light light;
uniform Material material;

uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

void main()
{

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.pos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    if (material.hasAmbientTexture)
    {
        ambient = light.ambient * vec3(texture(material.AmbientTexture, TexCoord));
    }
    else
    {
        ambient = light.ambient * material.ambient;
    }

    if (material.hasDiffuseTexture)
    {
        diffuse = light.diffuse * diff * vec3(texture(material.DiffuseTexture, TexCoord));
    }
    else
    {
        diffuse = light.diffuse * (diff * material.diffuse);
    }

    if (material.hasSpecularTexture)
    {
        specular = light.specular * spec * vec3(texture(material.SpecularTexture, TexCoord));
    }
    else
    {
        specular = light.specular * (spec * material.specular);
    }
    
    if (light.hasAttenuation)
    {

        float distance = length(light.pos - FragPos);

        float constant = 1.0f;
        float linear = 0.09f;
        float quadratic = 0.032f;

        float attenuation = 1.0f / (constant + linear * distance + quadratic * (distance * distance));

        ambient  *= attenuation;
        diffuse  *= attenuation;
        specular *= attenuation;

    }

    vec3 result = (ambient + diffuse + specular);
    FragColor = vec4(result, 1.0f);

}