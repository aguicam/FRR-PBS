#version 330

layout (location = 0) in vec3 vert;
layout (location = 1) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 view_inverse;

smooth out vec3 w_vert;
smooth out vec3 w_normal;
smooth out vec3 w_campos;

void main(void)  {
  w_vert = vec3(model* vec4(vert, 1));
  w_normal = normalize(normal);
  w_campos = view_inverse[3].xyz;
  gl_Position = projection * view * model * vec4(vert, 1);
}
