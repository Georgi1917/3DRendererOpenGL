#version 330 core
out vec4 aColor;

uniform vec3 uColor;

void main()
{
    aColor = vec4(uColor, 1.0f);
}