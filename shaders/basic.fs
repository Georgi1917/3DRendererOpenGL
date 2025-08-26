#version 330 core
out vec4 FragColor;

uniform vec3 uColor;
uniform vec3 lColor;

void main()
{

    float ambientStrenght = 0.1;
    vec3 ambient = lColor * ambientStrenght;
    vec3 result = ambient * uColor;

    FragColor = vec4(result, 1.0f);

}