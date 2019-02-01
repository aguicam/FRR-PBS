#version 330 core
layout (location = 0) in vec3 vert;

out vec3 w_pos;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    w_pos = vert;
    gl_Position =  projection * view * vec4(w_pos, 1.0);
}
