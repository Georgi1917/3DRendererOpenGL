#version 330 core
out vec4 FragColor;

uniform vec3 uColor;
uniform vec3 lColor;
uniform vec3 lPos;
uniform vec3 viewPos;
uniform bool hasTex;
uniform sampler2D Tex;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

void main()
{

    float ambientStrenght = 0.3;
    float specStrenght = 0.5;

    vec3 ambient = lColor * ambientStrenght;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lColor;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specStrenght * spec * lColor;

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