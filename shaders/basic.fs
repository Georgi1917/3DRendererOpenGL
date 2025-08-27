#version 330 core
out vec4 FragColor;

uniform vec3 uColor;
uniform vec3 lColor;
uniform vec3 lPos;

in vec3 Normal;
in vec3 FragPos;

void main()
{

    float ambientStrenght = 0.1;
    vec3 ambient = lColor * ambientStrenght;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lColor;
    vec3 result = (ambient + diffuse) * uColor;

    FragColor = vec4(result, 1.0f);

}