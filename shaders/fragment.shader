#version 330 core
in vec3 outColor;
out vec4 aColor;

void main()
{
    aColor = vec4(outColor, 1.0f);
}