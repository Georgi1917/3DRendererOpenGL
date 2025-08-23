#version 330 core
out vec4 aColor;

uniform vec3 uColor;
uniform vec3 lColor;

void main()
{
    aColor = vec4(lColor * uColor, 1.0f);
}