#version 420 core
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 vertex_texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 varying_position;
out vec3 varying_normal;
out vec2 varying_texcoord;

void main(void)
{
	varying_texcoord = vertex_texcoord;

	gl_Position = projection * view * model * vec4(vertex_position, 1.0);
}