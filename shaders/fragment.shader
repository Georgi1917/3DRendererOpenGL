#version 330 core
in vec3 outColor;
out vec4 aColor;

uniform vec3 uColor;

void main()
{
    aColor = vec4(uColor, 1.0f);
}