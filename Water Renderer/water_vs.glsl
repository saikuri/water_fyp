#version 420 core
layout(location = 0) in vec3 vertex_position;

uniform mat4 

void main(void)
{
	gl_Position = vec4(vertex_position, 1.0);
}