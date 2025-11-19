#version 330 core
out vec4 FragColor;

struct Light
{

    vec3 pos;
    vec3 color;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    sampler2D ambientTexture;
    sampler2D diffuseTexture;
    sampler2D specularTexture;

};

struct Material
{

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;

};

uniform Light light;
uniform Material material;

uniform vec3 viewPos;

uniform bool hasAttenuation;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

void main()
{

    vec3 ambient = light.ambient * material.ambient;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.pos - FragPos);
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    if (hasAttenuation)
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