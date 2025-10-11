#version 330 core

layout (location = 0) in vec3 pos;

out vec3 TexCoords;

uniform mat4 view;
uniform mat4 projection;

void main()
{

    vec4 position = projection * view * vec4(pos, 1.0);
    gl_Position = vec4(position.x, position.y, position.w, position.w);
    TexCoords = vec3(pos.x, pos.y, -pos.z);

}

