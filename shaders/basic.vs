#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;

void main()
{

    gl_Position = projection * view * model * vec4(pos, 1.0);
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    Normal = normalMatrix * aNormal;
    FragPos = vec3(model * vec4(pos, 1.0));
    TexCoord = aTexCoord;

}