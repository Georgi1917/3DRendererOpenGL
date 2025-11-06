#version 330 core
out vec4 FragColor;

struct Light
{

    vec3 pos;
    vec3 color;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

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

uniform vec3 uColor;
uniform vec3 viewPos;

uniform bool hasTex;
uniform bool hasAttenuation;

uniform sampler2D Tex;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

void main()
{

    float ambientStrenght = 0.35;
    float specStrenght = 0.5;

    vec3 ambient = light.color * ambientStrenght;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.pos - FragPos);
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.color;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specStrenght * spec * light.color;

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

    if (hasTex)
    {

        vec3 result = (ambient + diffuse + specular);
        FragColor = texture(Tex, TexCoord) * vec4(result, 1.0f);

    }
    else
    {

        vec3 result = (ambient + diffuse + specular) * uColor;
        FragColor = vec4(result, 1.0f);

    }


}