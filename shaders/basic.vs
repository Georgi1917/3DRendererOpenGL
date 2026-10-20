#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 tangent;
layout (location = 3) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;
out mat3 TBN;

void main()
{

    gl_Position = projection * view * model * vec4(pos, 1.0);
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    Normal = normalMatrix * aNormal;
    FragPos = vec3(model * vec4(pos, 1.0));
    TexCoord = aTexCoord;

    vec3 T = normalize(normalMatrix * tangent);
    vec3 N = normalize(normalMatrix * aNormal);
    vec3 B = cross(N, T);
    TBN = mat3(T, B, N);

}