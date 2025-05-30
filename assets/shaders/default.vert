#version 460 

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

in vec3 a_position;

void main()
{
    gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
}
